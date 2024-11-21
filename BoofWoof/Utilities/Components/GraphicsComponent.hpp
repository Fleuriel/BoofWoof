/**************************************************************************
 * @file GraphicsComponent.hpp
 * @author  Guo Chen
 * @param DP email: g.chen@digipen.edu [2200518]
 * @param Course: CS 3401
 * @param Course: Game Project 3
 * @date  10/06/2024 (06 OCTOBER 2024)
 * @brief
 *
 * This file contains the definition of the GraphicsComponent class, which is used to
 * store the model name and model ID of an entity.
 *
 *************************************************************************/

#pragma once
#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include "ECS/Coordinator.hpp"
#include "../Core/Graphics/Model.h"   // Make sure Model is included
#include "../Core/Graphics/Object.h"  // Full definition of Object is needed here
#include "../Core/Reflection/ReflectionManager.hpp" // Include the reflection manager

class GraphicsComponent
{
public:
    void SetComponentEntityID(Entity& entity) { m_EntityID = entity; }

    // Setters
    void setModelName(std::string modelName) { m_ModelName = modelName; }
    void SetModelID(int modelID) { m_ModelID = modelID; }
    void AddTexture(int textureid) { textures.push_back(textureid); }
	void SetFollowCamera(bool follow) { followCamera = follow; }

    // Getters
    std::string getModelName() const { return m_ModelName; }
    int getModelID() const { return m_ModelID; }
    
    std::string getTextureName() const { return textureName; }

    bool incrementTextureNumber() { Texture texture; textures.push_back(texture.id); return true; }
    int getTextureNumber() const { return static_cast<int>(textures.size()); }
    int getTexture(int i) const { return textures[i]; }

	bool getFollowCamera() const { return followCamera; }

    // Set texture name
    void setTexture(std::string texture) { textureName = texture; }





    // Constructor and destructor
	GraphicsComponent() : textureName (" "){};
	
	GraphicsComponent(std::string modelName, Entity& entity, std::string texName, bool followCam = true) : m_ModelName(modelName), m_EntityID(g_Coordinator.GetEntityId(entity)), textureName(texName), followCamera(followCam)
	{/*Empty by design*/

        

		std::cout << "Model Name of Graphics Component: " << m_ModelName << '\n';
		std::cout << "Texture Name of Graphics Component: " << textureName << '\n';
	}

    ~GraphicsComponent() = default;

    // Reflection integration
    REFLECT_COMPONENT(GraphicsComponent)
    {
        REGISTER_PROPERTY(GraphicsComponent, ModelName, std::string, setModelName, getModelName);
        REGISTER_PROPERTY(GraphicsComponent, ModelID, int, SetModelID, getModelID);
        REGISTER_PROPERTY(GraphicsComponent, TextureName, std::string, setTexture, getTextureName);
		REGISTER_PROPERTY(GraphicsComponent, FollowCamera, bool, SetFollowCamera, getFollowCamera);
    }

private:
    Entity m_EntityID{};
    std::string m_ModelName{};
    int m_ModelID{};
    std::string textureName;
    std::vector<int> textures{};
    bool followCamera = true;

};

#endif  // GRAPHICS_COMPONENT_H
