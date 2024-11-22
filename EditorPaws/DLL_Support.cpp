#include "DLL_Support.h"
#include "../BoofWoof/Core/Logic/LogicSystem.h"
#include "../BoofWoof/Core/Windows/WindowManager.h"

// Global Variables
HHOOK hHook = NULL;
UINT WM_FILE_CHANGED;

const std::wstring WATCHED_DIRECTORY = L"..\\ScriptWoof\\x64\\Debug";

std::atomic<bool> wasPreviouslyUnfocused(false); // Track window focus state
std::atomic<bool> checkDirectoryOnce(false); // Check directory only once per focus regain

bool monitoringThread;
bool DLL_has_changed;
std::thread monitorThread; // Thread for directory monitoring

MSG msg;

void DLL_Support_Init() {
    // Register a custom message
    WM_FILE_CHANGED = RegisterWindowMessageW(L"WM_FILE_CHANGED");

    // Set the hook
    SetCustomHook();

    monitoringThread = false;
	DLL_has_changed = false;
}

void DLL_Support_Update() {
    if (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void DLL_Support_Unload() {
    // Clean up
    UnhookWindowsHookEx(hHook);
}

// Custom hook procedure
LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        MSG* msg = (MSG*)lParam;

        if (msg->message == WM_FILE_CHANGED) {
            MessageBoxW(NULL, L"File change detected!", L"Notification", MB_OK);
            std::cout << "File change detected!" << std::endl;
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

bool CopyAndOverwriteDLL(const std::wstring& sourcePath, const std::wstring& destPath) {
    // Attempt to copy the DLL file and overwrite the existing one
    if (CopyFileW(sourcePath.c_str(), destPath.c_str(), FALSE)) {
        std::cout << "Successfully copied and overwritten the DLL!" << std::endl;
        return true;
    }
    else {
        std::cerr << "Failed to copy the DLL. Error: " << GetLastError() << std::endl;
        return false;
    }
}

bool IsDLLInUse(const std::wstring& dllPath) {
    HANDLE hFile = CreateFileW(
        dllPath.c_str(),
        GENERIC_WRITE,              // Test if the file can be opened for writing
        FILE_SHARE_READ,            // Allow shared reading but no writing or deleting
        NULL,                       // Default security attributes
        OPEN_EXISTING,              // Only check if the file exists
        FILE_ATTRIBUTE_NORMAL,      // Normal file attributes
        NULL                        // No template file
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        if (error == ERROR_SHARING_VIOLATION) {
            std::wcout << L"File is locked for changes: " << dllPath << std::endl;
            return true; // File is locked for changes
        }
        else if (error == ERROR_FILE_NOT_FOUND) {
            std::wcerr << L"File not found: " << dllPath << std::endl;
        }
        else {
            std::wcerr << L"Failed to open file. Error: " << error << std::endl;
        }
    }
    // Successfully opened the file, which means it's not in use
    CloseHandle(hFile);
    return false; // DLL is not in use
}
/*
void StartFocusChecker() {
    // Launch focus checker in a separate thread
    std::thread focusThread(FocusChecker);
    focusThread.detach(); // Detach to allow independent execution
}
*/


void FocusChecker(GLFWwindow* window, int focused) {
    
        if (focused) {
            if (wasPreviouslyUnfocused.exchange(false)) {
                std::cout << "Window regained focus.\n";
                monitoringThread = false;
                if (monitorThread.joinable()) {
                    monitorThread.join();
                }
				if (DLL_has_changed) {
					ChangeDLL();
					DLL_has_changed = false;
				}
				else {
					std::cout << "DLL has not changed.\n";
				}
            }
            
        }
        else {
            if (!wasPreviouslyUnfocused.exchange(true)) {
                std::cout << "Window lost focus 2.\n";
				monitoringThread = true;
                monitorThread = std::thread(MonitorDirectory); // Trigger directory monitoring
            }
        }


        // Sleep to avoid excessive CPU usage
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
 }

// Function to monitor directory changes
void MonitorDirectory() {
    std::cout << "Checking directory for changes...\n";

    HANDLE hDir = CreateFileW(
        WATCHED_DIRECTORY.c_str(),
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
        NULL
    );

    if (hDir == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open directory for monitoring." << std::endl;
        return;
    }
    else {
        std::cout << "Directory monitoring started." << std::endl;
    }

    char buffer[1024];
    DWORD bytesReturned;
    OVERLAPPED overlapped = { 0 };
    HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!hEvent) {
        std::cerr << "Failed to create event." << std::endl;
        CloseHandle(hDir);
        return;
    }

    overlapped.hEvent = hEvent;

    while (monitoringThread) {
        if (ReadDirectoryChangesW(
            hDir,
            buffer,
            sizeof(buffer),
            TRUE, // Watch subdirectories
            FILE_NOTIFY_CHANGE_LAST_WRITE | // Detect file modifications
            FILE_NOTIFY_CHANGE_FILE_NAME,   // Detect file name changes
            &bytesReturned,
            &overlapped,
            NULL)) {
            DWORD waitStatus = WaitForSingleObject(hEvent, 5000); // 5-second timeout

            if (waitStatus == WAIT_OBJECT_0) {
                ResetEvent(hEvent);

                if (bytesReturned == 0) {
                    std::cout << "No changes detected." << std::endl;
                    continue;
                }

                FILE_NOTIFY_INFORMATION* fni = (FILE_NOTIFY_INFORMATION*)buffer;
                do {
                    std::cout << "Checking for changes..." << std::endl;
                    std::wstring fileName(fni->FileName, fni->FileNameLength / sizeof(WCHAR));
                    if (fileName == L"ScriptWoof.dll") { // Replace with your DLL name
                        PostThreadMessage(GetCurrentThreadId(), WM_FILE_CHANGED, 0, 0);
                        std::cout << "File change detected!" << std::endl;

						DLL_has_changed = true;
                    }
                    else {
                        //std::cerr << "Not the file we are looking for." << std::endl;
                    }

                    fni = fni->NextEntryOffset ? (FILE_NOTIFY_INFORMATION*)((BYTE*)fni + fni->NextEntryOffset) : NULL;
                } while (fni);
            }
            else if (waitStatus == WAIT_TIMEOUT) {
                //std::cout << "No changes detected within the timeout period." << std::endl;
				// Just continue monitoring if timeout
            }
            else {
                std::cerr << "Error waiting for directory changes: " << GetLastError() << std::endl;
                break;
            }
        }
        else {
            std::cerr << "Failed to read directory changes." << std::endl;
            break;
        }
    }

    CloseHandle(hEvent);
    CloseHandle(hDir);
    std::cout << "Directory monitoring stopped." << std::endl;
}

void ChangeDLL() {
    // Save current scene to temp file

                        // Clear current scene

    if (IsDLLInUse(DLL_COPY_DIRECTORY)) {
        std::cout << "DLL is being used by another process. Unloading the DLL..." << std::endl;
        if (hGetProcIDDLL != nullptr) {
            FreeLibrary(hGetProcIDDLL);
            std::cout << "DLL unloaded." << std::endl;
        }
        else {
            std::cerr << "Unable to Free." << std::endl;
            return;
        }
    }
    if (CopyAndOverwriteDLL(DLL_MAIN_DIRECTORY, DLL_COPY_DIRECTORY)) {
        std::cout << "DLL copied and overwritten successfully!" << std::endl;
        hGetProcIDDLL = LoadLibraryW(DLL_COPY_DIRECTORY.c_str());
        // Load Temp Scene
    }
    else {
        std::cerr << "Failed to copy and overwrite the DLL." << std::endl;
    }
}

// Set up the hook
void SetCustomHook() {
    hHook = SetWindowsHookEx(WH_GETMESSAGE, HookProc, NULL, GetCurrentThreadId());
    if (!hHook) {
        MessageBoxW(NULL, L"Failed to set hook.", L"Error", MB_OK);
    }
}