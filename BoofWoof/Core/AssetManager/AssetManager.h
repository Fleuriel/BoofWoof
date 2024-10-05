/**************************************************************************
 * @file AssetManager.cpp
 * @author 	Aaron Chan Jun Xiang
 * @param DP email: aaronjunxiang.chan@digipen.edu [2200880]
 * @param Course: CS 350
 * @param Course: Advanced Computer Graphics II
 * @date  06/14/2024 (14 JUNE 2024)
 * @brief
 *
 * This file allows assets to be loaded into containers to be used by
 * the application.
 *
 *
 *************************************************************************/
#pragma once

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Graphics/GraphicsSystem.h"
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Graphics/Object.h"
#include "Sprite.h"

 // Forward declarations




/**************************************************************************
* @brief AssetManager Class
*************************************************************************/
class AssetManager
{


public:

	// General functions
	AssetManager();																			//Constructor for AssetManager class
	~AssetManager();																		//Destructor for AssetManager class

	void LoadAll();																			//Function to load all assets
	void FreeAll();																			//Function to free all assets
	//void ReloadAll();																		//Function to reload all assets

	// Texture functions
	bool LoadTextures();																	//Function to load textures
	bool FreeTextures();																	//Function to free textures
	bool ReloadTextures();																	//Function to reload textures


	// Scene functions
	bool LoadScenes();																		//Function to load scenes
	bool ReloadScenes();																	//Function to reload scenes



	using VectorPairString = std::vector <std::pair<std::string, std::string>>;				// Using a vector-->pair string for shaders

	bool LoadShaders();																		// Load Shaders
	void InitShdrpgms(VectorPairString const& vpss);										//Function to initialize shaders
	bool FreeShaders();																		//Function to free shaders


	//Getters
	Sprite GetSprite(std::string);															//Function to access sprite
	int GetSpriteTexture(std::string);														//Function to access sprite texture
	OpenGLShader& GetShader(std::string);													//Function to access shaders





	std::map <std::string, Model> ModelMap;
	std::vector <Model>	Models;
	std::vector <Object> Objects;


	bool Currentlyloading{ false };

private:

	//Containers
	std::vector<std::string> TextureDescriptionFiles;										//Container to store texture description files
	std::map<std::string, Sprite> sprites{};												//Container to store sprites
	std::vector<OpenGLShader>shdrpgms;														//Container to store shader programs
	std::vector<std::string>shdrpgmOrder{};													//Container to store the order of shader programs


};




extern AssetManager g_AssetManager;		// Allow usage of class outside of assetManager.cpp

#endif