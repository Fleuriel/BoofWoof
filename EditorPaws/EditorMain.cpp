#define _CRTDBG_MAP_ALLOC
#include "ECS/pch.h"
#include <stdlib.h>
#include <crtdbg.h>
#include "ImGuiEditor.h"
#include "../BoofWoof/Core/EngineCore.h"
#include "DLL_Support.h"

EngineCore* g_Core = nullptr;

int main()
{

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif

	//for use with debugging, change the value to the location of the mem leak per the crt debug info from the console
	// refer to stack frame and see where it all went wrong
	//_crtBreakAlloc = 20649858;

	DLL_Support_Init();

    // Start the directory monitoring in a separate thread
    //std::thread monitorThread(MonitorDirectory);

	

    MSG msg;
    
	g_Core = new EngineCore();
	g_Core->OnInit();
	g_ImGuiEditor.ImGuiInit(g_Window);

	
	glfwSetWindowFocusCallback(g_Window->GetGLFWWindow(), FocusChecker);
	//StartFocusChecker();

	while (!glfwWindowShouldClose(g_Window->GetGLFWWindow()))
	{
		glfwPollEvents();
		DLL_Support_Update();
		g_Core->OnUpdate();
		g_ImGuiEditor.ImGuiUpdate();
		g_ImGuiEditor.ImGuiRender();
	}

	g_ImGuiEditor.ImGuiEnd();
	g_Core->OnShutdown();

	delete g_Core;

    
	// Clean up
	//monitorThread.detach();
	DLL_Support_Unload();
    
	return 0;
}


