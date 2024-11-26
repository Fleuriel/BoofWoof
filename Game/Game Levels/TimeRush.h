#pragma once
#include "Level Manager/Level.h"
#include "ResourceManager/ResourceManager.h"
#include "ECS/Coordinator.hpp"

class TimeRush : public Level
{
    double timer = 0.0;
    double interval = 1.0; // Time interval in seconds
    int currentTextureIndex = 53; // Start from "Group53"
    Entity timerTextEntity{}, playerEnt{};
    CameraController* cameraController = nullptr;

    void LoadLevel() override
    {
        g_SceneManager.LoadScene("../BoofWoof/Assets/Scenes/TimeRushPuzzle.json");
        g_SceneManager.LoadScene("../BoofWoof/Assets/Scenes/Timer.json");

        std::vector<Entity> entities = g_Coordinator.GetAliveEntitiesSet();
        for (auto entity : entities)
        {
            if (g_Coordinator.HaveComponent<MetadataComponent>(entity))
            {
                if (g_Coordinator.GetComponent<MetadataComponent>(entity).GetName() == "Player")
                {
                    playerEnt = entity;
                }

                if (g_Coordinator.GetComponent<MetadataComponent>(entity).GetName() == "Group")
                {
                    timerTextEntity = entity;
                    break;
                }
            }
        }
    }

    void InitLevel() override 
    {  
        cameraController = new CameraController(playerEnt);
    }

    void UpdateLevel(double deltaTime) override
    {
        cameraController->Update(static_cast<float>(deltaTime));

        timer += deltaTime;

        if (!g_Coordinator.HaveComponent<GraphicsComponent>(timerTextEntity)) return;

        auto& text = g_Coordinator.GetComponent<GraphicsComponent>(timerTextEntity);

        // Change the texture every second
        if (timer >= interval && currentTextureIndex <= 233)
        {
            std::string currentTextureName = "Group" + std::to_string(currentTextureIndex);
            std::string nextTextureName = "Group" + std::to_string(currentTextureIndex + 1);

            int currentTextureId = g_ResourceManager.GetTextureDDS(currentTextureName);

            // Remove the current texture and add the next one
            if (text.RemoveTexture(currentTextureId))
            {
                text.clearTextures();

                int nextTextureId = g_ResourceManager.GetTextureDDS(nextTextureName);
                text.AddTexture(nextTextureId);
                text.setTexture(nextTextureName);
            }

            timer = 0.0; // Reset timer
            currentTextureIndex++; // Move to the next texture
        }

        // When the timer reaches the end ("Group234"), transition to the next level
        if (currentTextureIndex > 234)
        {
            std::cout << "End of timer" << std::endl;
        }

        if (g_Coordinator.GetComponent<CollisionComponent>(playerEnt).GetLastCollidedObjectName() == "WallDoor")
        {
            g_LevelManager.SetNextLevel("MainHall");
        }
    }

    void FreeLevel() override 
    {
        if (cameraController)
        {
            delete cameraController;
            cameraController = nullptr;
        }
    }

    void UnloadLevel() override
    {
        g_Coordinator.GetSystem<MyPhysicsSystem>()->ClearAllBodies();
        g_Coordinator.ResetEntities();
        timer = 0.0;
        currentTextureIndex = 53;
    }
};