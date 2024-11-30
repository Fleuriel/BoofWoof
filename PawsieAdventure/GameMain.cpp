#define _CRTDBG_MAP_ALLOC
#pragma warning(disable : 4005)
#include <stdlib.h>
#include <crtdbg.h>
#include "../BoofWoof/Core/EngineCore.h"
#include "Level Manager/LevelManager.h"
#include "GSM/GameStateMachine.h"
#include "Game Levels/Splashscreen.h"
#include "Game Levels/MainMenu.h"
#include "Game Levels/Cutscene.h"
#include "Game Levels/StartingRoom.h"
#include "Game Levels/TimeRush.h"
#include "Game Levels/MainHall.h"

EngineCore* g_Core = nullptr;

void InitializeLevels()
{
    g_Window->toggleFullScreen();
    // Register your levels here
    g_LevelManager.RegisterLevel("Splashscreen", new Splashscreen());
    g_LevelManager.RegisterLevel("MainMenu", new MainMenu());
    g_LevelManager.RegisterLevel("Cutscene", new Cutscene());
    g_LevelManager.RegisterLevel("StartingRoom", new StartingRoom());
    g_LevelManager.RegisterLevel("TimeRush", new TimeRush());
    g_LevelManager.RegisterLevel("MainHall", new MainHall());

    // Set the initial level
    g_LevelManager.Initialize("Splashscreen");
    g_LevelManager.SetNextLevel("Splashscreen");
    g_LevelManager.SetPreviousLevel("Splashscreen");
}

int RunGame()
{
#if defined(DEBUG) || defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif

    // Uncomment and set the allocation number if debugging memory leaks
    //_crtBreakAlloc = 372;

    g_Core = new EngineCore();
    g_Core->OnInit();

    InitializeLevels();
    UpdateGSM();

    // Main game loop
    while (!glfwWindowShouldClose(g_Window->GetGLFWWindow()))
    {
        // Uncomment if the core update logic is required
        // g_Core->OnUpdate();
    }

    g_Core->OnShutdown();

    delete g_Core;

    return 0;
}

#ifdef _DEBUG
// Use `main` in debug mode
int main()
{
    return RunGame();
}
#else
#include <windows.h>
// Use `WinMain` in release mode
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;
    return RunGame();
}
#endif