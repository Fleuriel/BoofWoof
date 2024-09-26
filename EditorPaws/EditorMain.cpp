

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ImGuiEditor.h"

#include "../BoofWoof/Core/EngineCore.h"

#include <iostream>

EngineCore* g_Core = nullptr;

int main()
{

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif

	//for use with debugging, change the value to the location of the mem leak per the crt debug info from the console
	// refer to stack frame and see where it all went wrong
	//_crtBreakAlloc = 372;

	g_Core = new EngineCore();
	g_Core->OnInit();
	g_ImGuiEditor.ImGuiInit(g_Window);

	// Check glfwInit
	//if (!glfwInit())
	//{
	//	return -1;
	//}

	//g_ImGuiEditor.ImGuiInit();

	while (!glfwWindowShouldClose(g_Window->GetGLFWWindow()))
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		g_Core->OnUpdate();
		g_ImGuiEditor.ImGuiUpdate();
		g_ImGuiEditor.ImGuiRender();
	}

	g_ImGuiEditor.ImGuiEnd();
	g_Core->OnShutdown();

	delete g_Core;

	return 0;
}