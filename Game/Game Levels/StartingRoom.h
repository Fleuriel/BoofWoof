#pragma once
#include "Level Manager/Level.h"
#include "ECS/Coordinator.hpp"
#include "../Systems/CameraController/CameraController.h"
#include "../Systems/BoneCatcher/BoneCatcher.h"
#include "../Systems/RopeBreaker/RopeBreaker.h"
#include "../Systems/ChangeText/ChangeText.h"
#include "../Systems/Checklist/Checklist.h"

class StartingRoom : public Level
{
	Entity playerEnt{};
	CameraController* cameraController = nullptr;

	void LoadLevel()
	{
		g_SceneManager.LoadScene("../BoofWoof/Assets/Scenes/StartingRoom2.json");		
		g_Audio.PlayBGM("../BoofWoof/Assets/Audio/BedRoomMusic.wav");	

		g_ChangeText.OnInitialize();

		std::vector<Entity> entities = g_Coordinator.GetAliveEntitiesSet();

		for (auto entity : entities)
		{
			if (g_Coordinator.HaveComponent<MetadataComponent>(entity))
			{
				if (g_Coordinator.GetComponent<MetadataComponent>(entity).GetName() == "Player")
				{
					playerEnt = entity;		
					break;
				}
			}
		}

		g_Window->HideMouseCursor();
	}

	void InitLevel()
	{
		// Ensure player entity is valid
		cameraController = new CameraController(playerEnt);
	}

	bool teb_last = false;

	void UpdateLevel(double deltaTime)
	{
		cameraController->Update(static_cast<float>(deltaTime));

		if (!g_ChangeText.shutted) 
		{
			g_ChangeText.OnUpdate(deltaTime);
		}

		if (!g_Checklist.shutted)
		{
			g_Checklist.OnUpdate(deltaTime);
		}

		if (g_Input.GetKeyState(GLFW_KEY_TAB) >= 1)
		{
			if (!teb_last)
			{
				teb_last = true;
				cameraController->ToggleCameraMode();
			}
		}
		else
		{
			teb_last = false;
		}

		//if (g_Input.GetKeyState(GLFW_KEY_O) >= 1) 
		//{
		//	cameraController->ShakeCamera(1.0f, glm::vec3(0.1f,0.1f,0.1f));
		//}

		if (g_Checklist.shutted) 
		{
			if (g_Coordinator.GetComponent<CollisionComponent>(playerEnt).GetLastCollidedObjectName() == "WallHole")
			{
				g_LevelManager.SetNextLevel("TimeRush");
			}
		}

		//// Space to go back mainmenu
		//if (g_Input.GetKeyState(GLFW_KEY_ESCAPE) >= 1)
		//{
		//	g_LevelManager.SetNextLevel("MainMenu");
		//	g_Window->ShowMouseCursor();
		//}
	}

	void FreeLevel()
	{
		if (cameraController)
		{
			delete cameraController;
			cameraController = nullptr;
		}
	}

	void UnloadLevel()
	{
		g_Audio.StopBGM();
		g_Coordinator.GetSystem<MyPhysicsSystem>()->ClearAllBodies();
		g_Coordinator.ResetEntities();
	}
};