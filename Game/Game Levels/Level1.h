#pragma once

#include "Level Manager/Level.h"
#include "ECS/Coordinator.hpp"
#include "../Systems/CameraController/CameraController.h"
#include "../Systems/BoneCatcher/BoneCatcher.h"
#include "../Systems/RopeBreaker/RopeBreaker.h"

Entity playerEnt{}, RopeEnt{};
CameraController* cameraController = nullptr;
RopeBreaker* ropeBreaker = nullptr;

class Level1 : public Level
{
	void LoadLevel()
	{
		g_SceneManager.LoadScene("../BoofWoof/Assets/Scenes/CorgiVSRope.json");		

		std::vector<Entity> entities = g_Coordinator.GetAliveEntitiesSet();

		for (auto entity : entities)
		{
			if (g_Coordinator.HaveComponent<MetadataComponent>(entity))
			{
				if (g_Coordinator.GetComponent<MetadataComponent>(entity).GetName() == "Player")
				{
					playerEnt = entity;					
				}

				if (g_Coordinator.GetComponent<MetadataComponent>(entity).GetName() == "Rope")
				{
					RopeEnt = entity;
					break;
				}
			}
		}
	}

	void InitLevel()
	{
		if (playerEnt != Entity{})
		{
			// Ensure player entity is valid
			cameraController = new CameraController(playerEnt);

			if (RopeEnt != Entity{}) 
			{
				ropeBreaker = new RopeBreaker(playerEnt, RopeEnt);
			}
		}
	}

	void UpdateLevel(double deltaTime)
	{
		cameraController->Update(static_cast<float>(deltaTime));


		if (ropeBreaker)
		{
			ropeBreaker->OnUpdate(deltaTime);
		}
		

		if (g_Input.GetKeyState(GLFW_KEY_TAB) >= 1)
		{
			cameraController->ToggleCameraMode();
		}		

		// Space to go back mainmenu
		if (g_Input.GetKeyState(GLFW_KEY_ESCAPE) >= 1)
		{
			g_LevelManager.SetNextLevel("MainMenu");
		}

	}

	void FreeLevel()
	{
		if (cameraController)
		{
			delete cameraController;
			cameraController = nullptr;
		}

		if (ropeBreaker) 
		{
			delete ropeBreaker;
			ropeBreaker = nullptr;
		}
	}

	void UnloadLevel()
	{
		g_Coordinator.ResetEntities();
	}
};