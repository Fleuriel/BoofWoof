#pragma once

#include "../Core/ECS/Coordinator.h"
#include <iostream>
#include "../Utilities/Components/GraphicsComponent.h"
#include "Windows/WindowManager.h"
#include "Graphics/GraphicsSystem.h"
#include "AssetManager/AssetManager.h"
#include "../Utilities/Components/RenderTest.hpp"

#include <GLFW/glfw3.h>

class EngineCore 
{
public:
	void OnInit();
	void OnUpdate();
	void OnShutdown();
};

extern EngineCore* gCore;