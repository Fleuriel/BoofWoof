#pragma once
#include <EngineCore.h>

class ChangeText
{
public:
	void OnInitialize();
	void OnUpdate(double deltaTime);
	void OnShutdown();

public:
	bool shutted{ false };
	int textureIndex = 5;
	int indexLimit = 6;

private:
	Entity m_Text{};
	double cdTimer = 0.0;
	double cdLimit = 4.0;   


protected:

	// Storage is for those entity you added in when you load a scene file
	// during exit, can just delete those entity - clearing spawned entities
	std::vector<Entity> storage;
};

extern ChangeText g_ChangeText;