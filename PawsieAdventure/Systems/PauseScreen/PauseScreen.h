#pragma once
#include <EngineCore.h>

extern bool g_IsPaused;

enum class PauseState
{
	Paused,
	Settings,
	HowToPlay,
	QuitGame,
};

class PauseMenu 
{
public:
	virtual ~PauseMenu() {}
	virtual void OnLoad() = 0;
	virtual void OnExit() = 0;

protected:
	std::vector<Entity> spawnedEntities;
};

// Main Pause Screen
class PausedScreen : public PauseMenu
{
public:
	void OnLoad() override;
	void OnExit() override;
};

class QuitScreen : public PauseMenu
{
public:
	void OnLoad() override;
	void OnExit() override;
};

class Settings : public PauseMenu
{
public:
	void OnLoad() override;
	void OnExit() override;
};

class HowToPlay : public PauseMenu
{
public:
	void OnLoad() override;
	void OnExit() override;
};

std::unique_ptr<PauseMenu> CreatePausedMenu(PauseState state);

namespace pauseLogic 
{
	void OnUpdate();
}