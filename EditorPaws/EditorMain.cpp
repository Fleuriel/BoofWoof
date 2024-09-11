

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ImGuiEditor.h"
#include <glfw3.h>

GLFWwindow* win;

int main()
{

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif

	//for use with debugging, change the value to the location of the mem leak per the crt debug info from the console
	// refer to stack frame and see where it all went wrong
	//_crtBreakAlloc = 372;

	g_ImGuiEditor.ImGuiInit();

	while (!glfwWindowShouldClose(win))
	{
		g_ImGuiEditor.ImGuiUpdate();
		g_ImGuiEditor.ImGuiRender();
	}

	g_ImGuiEditor.ImGuiEnd();

	return 0;
}