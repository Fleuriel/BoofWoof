#include "PauseScreen.h"
#include "../Core/AssetManager/FilePaths.h"

std::unique_ptr<PauseMenu> pauser = CreatePausedMenu(PauseState::Paused);
Serialization serialPause;
bool g_IsPaused = false;

void PausedScreen::OnLoad()
{
	g_SceneManager.LoadScene(FILEPATH_ASSET_SCENES + "/PauseScreen.json");
	spawnedEntities = serialPause.GetStored();

	std::vector<Entity> entities = g_Coordinator.GetAliveEntitiesSet();
	for (auto entity : entities)
	{
		if (g_Coordinator.HaveComponent<MetadataComponent>(entity))
		{
			break;
		}
	}
}

void PausedScreen::OnExit()
{
	std::vector<Entity> entities = g_Coordinator.GetAliveEntitiesSet();

	for (auto i = entities.begin(); i != entities.end(); i++)
	{
		for (auto k = spawnedEntities.begin(); k != spawnedEntities.end(); k++)
		{
			if (*k == *i)
			{
				g_Coordinator.DestroyEntity(*i);
			}
		}
	}
}

void QuitScreen::OnLoad()
{
	// might need to separate the setting json based 
	// on whether it's pausedscreen's or mainmenu's ?

	g_SceneManager.LoadScene(FILEPATH_ASSET_SCENES + "/QuitGame.json");
	spawnedEntities = serialPause.GetStored();

	std::vector<Entity> entities = g_Coordinator.GetAliveEntitiesSet();
	for (auto entity : entities)
	{
		if (g_Coordinator.HaveComponent<MetadataComponent>(entity))
		{
			break;
		}
	}
}

void QuitScreen::OnExit()
{
	std::vector<Entity> entities = g_Coordinator.GetAliveEntitiesSet();

	for (auto i = entities.begin(); i != entities.end(); i++)
	{
		for (auto k = spawnedEntities.begin(); k != spawnedEntities.end(); k++)
		{
			if (*k == *i)
			{
				g_Coordinator.DestroyEntity(*i);
			}
		}
	}
}

void Settings::OnLoad()
{
	// might need to separate the setting json based 
	// on whether it's pausedscreen's or mainmenu's ?

	g_SceneManager.LoadScene(FILEPATH_ASSET_SCENES + "/Settings.json");
	spawnedEntities = serialPause.GetStored();

	std::vector<Entity> entities = g_Coordinator.GetAliveEntitiesSet();
	for (auto entity : entities)
	{
		if (g_Coordinator.HaveComponent<MetadataComponent>(entity))
		{
			break;
		}
	}
}

void Settings::OnExit()
{
	std::vector<Entity> entities = g_Coordinator.GetAliveEntitiesSet();

	for (auto i = entities.begin(); i != entities.end(); i++)
	{
		for (auto k = spawnedEntities.begin(); k != spawnedEntities.end(); k++)
		{
			if (*k == *i)
			{
				g_Coordinator.DestroyEntity(*i);
			}
		}
	}
}

void HowToPlay::OnLoad()
{
	// might need to separate the setting json based 
	// on whether it's pausedscreen's or mainmenu's ?

	g_SceneManager.LoadScene(FILEPATH_ASSET_SCENES + "/HowToPlay.json");
	spawnedEntities = serialPause.GetStored();

	std::vector<Entity> entities = g_Coordinator.GetAliveEntitiesSet();
	for (auto entity : entities)
	{
		if (g_Coordinator.HaveComponent<MetadataComponent>(entity))
		{
			break;
		}
	}
}

void HowToPlay::OnExit()
{
	std::vector<Entity> entities = g_Coordinator.GetAliveEntitiesSet();

	for (auto i = entities.begin(); i != entities.end(); i++)
	{
		for (auto k = spawnedEntities.begin(); k != spawnedEntities.end(); k++)
		{
			if (*k == *i)
			{
				g_Coordinator.DestroyEntity(*i);
			}
		}
	}
}

std::unique_ptr<PauseMenu> CreatePausedMenu(PauseState state)
{
	switch (state)
	{
	case PauseState::Paused:
		return std::make_unique<PausedScreen>();

	case PauseState::Settings:
		return std::make_unique<Settings>();

	case PauseState::HowToPlay:
		return std::make_unique<HowToPlay>();

	case PauseState::QuitGame:
		return std::make_unique<QuitScreen>();

	default:
		return std::make_unique<PausedScreen>();
	}
}

namespace pauseLogic 
{
	void OnUpdate()
	{
		if (!g_IsPaused && g_Input.GetKeyState(GLFW_KEY_ESCAPE)) 
		{
			g_IsPaused = true;
			pauser->OnLoad();

			std::cout << "entered paused screen" << std::endl;
		}

		if (g_IsPaused && g_Input.GetKeyState(GLFW_KEY_ESCAPE)) 
		{
			pauser->OnExit();
			g_IsPaused = true;

			std::cout << "unpaused" << std::endl;
		}

		if (g_IsPaused) 
		{
			// player cannot move

			// click the other buttons, need wait Interactive UI System.
		}
	}
}