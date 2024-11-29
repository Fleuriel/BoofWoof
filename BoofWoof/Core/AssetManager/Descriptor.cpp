/**************************************************************************
 * @file Descriptor.cpp
 * @author 	Aaron Chan Jun Xiang
 * @param DP email: aaronjunxiang.chan@digipen.edu [2200880]
 * @param Course: CS 3401
 * @param Course: Game Project 3
 * @date  10/06/2024 (06 OCTOBER 2024)
 * @brief
 *
 * This file defines the Descriptor class
 *
 *************************************************************************/
#include "pch.h"
#include "Descriptor.h"

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <stdexcept> // For std::runtime_error

bool TextureDescriptor::SaveTextureDescriptor(const std::string& filepath) {
	using namespace rapidjson;

	// Create a JSON document
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();

	// Add members to the JSON object

	document.AddMember("textureType", textureType, allocator);
	document.AddMember("textureShape", textureShape, allocator);
	document.AddMember("sRGB", sRGB, allocator);
	document.AddMember("alphaSource", alphaSource, allocator);
	document.AddMember("alphaIsTransparency", alphaIsTransparency, allocator);
	document.AddMember("nonPowerOfTwo", nonPowerOfTwo, allocator);
	document.AddMember("readWrite", readWrite, allocator);
	document.AddMember("generateMipMaps", generateMipMaps, allocator);
	document.AddMember("mipMapLimits", mipMapLimits, allocator);
	document.AddMember("mipMapLimitGroup", mipMapLimitGroup, allocator);
	document.AddMember("mipStreaming", mipStreaming, allocator);
	document.AddMember("mipMapFiltering", mipMapFiltering, allocator);
	document.AddMember("preserveCoverage", preserveCoverage, allocator);
	document.AddMember("replicateBorder", replicateBorder, allocator);
	document.AddMember("fadeoutToGray", fadeoutToGray, allocator);
	document.AddMember("ignorePngGamma", ignorePngGamma, allocator);
	document.AddMember("wrapMode", wrapMode, allocator);
	document.AddMember("filterMode", filterMode, allocator);
	document.AddMember("anisoLevel", anisoLevel, allocator);
	document.AddMember("maxSize", maxSize, allocator);
	document.AddMember("resizeAlgorithm", resizeAlgorithm, allocator);
	document.AddMember("format", format, allocator);
	document.AddMember("compression", compression, allocator);
	document.AddMember("useCrunchCompression", useCrunchCompression, allocator);

	// Write JSON to file
	std::ofstream ofs(filepath, std::ios::out | std::ios::trunc);
	if (!ofs) {
		std::cerr << "Error: Unable to open file for writing: " << filepath << std::endl;
		return false;
	}

	// Use RapidJSON's PrettyWriter to write the document
	OStreamWrapper osw(ofs);
	PrettyWriter<OStreamWrapper> writer(osw);

	if (!document.Accept(writer)) {
		std::cerr << "Error: Failed to write JSON data to file." << std::endl;
		return false;
	}

	return true;
}


bool TextureDescriptor::LoadTextureDescriptor(const std::string& filepath) {
	using namespace rapidjson;

	// Open the file
	std::ifstream ifs(filepath, std::ios::in);
	if (!ifs.is_open()) {
		std::cerr << "Error: Failed to open descriptor file: " << filepath << std::endl;
		return false;
	}

	// Parse the JSON file
	IStreamWrapper isw(ifs);
	Document document;
	if (document.ParseStream(isw).HasParseError()) {
		std::cerr << "Error: Failed to parse descriptor file: " << filepath
			<< " (Error code: " << document.GetParseError()
			<< ", Offset: " << document.GetErrorOffset() << ")" << std::endl;
		return false;
	}

	// Check that the document is an object
	if (!document.IsObject()) {
		std::cerr << "Error: Descriptor file does not contain a valid JSON object: " << filepath << std::endl;
		return false;
	}

	// Helper lambda functions to safely extract values
	auto GetInt = [&](const char* key, int& target) {
		if (document.HasMember(key) && document[key].IsInt())
			target = document[key].GetInt();
		};

	auto GetString = [&](const char* key, std::string& target) {
		if (document.HasMember(key) && document[key].IsString())
			target = document[key].GetString();
		};

	auto GetBool = [&](const char* key, bool& target) {
		if (document.HasMember(key) && document[key].IsBool())
			target = document[key].GetBool();
		};

	auto GetFloat = [&](const char* key, float& target) {
		if (document.HasMember(key) && document[key].IsFloat())
			target = document[key].GetFloat();
		};

	// Populate descriptor fields
	GetInt("textureType", textureType);
	GetInt("textureShape", textureShape);
	GetBool("sRGB", sRGB);
	GetInt("alphaSource", alphaSource);
	GetBool("alphaIsTransparency", alphaIsTransparency);
	GetInt("nonPowerOfTwoOption", nonPowerOfTwo);
	GetBool("readWrite", readWrite);
	GetBool("generateMipMaps", generateMipMaps);
	GetBool("mipMapLimits", mipMapLimits);
	GetInt("mipMapLimitGroup", mipMapLimitGroup);
	GetBool("mipStreaming", mipStreaming);
	GetInt("mipMapFiltering", mipMapFiltering);
	GetBool("preserveCoverage", preserveCoverage);
	GetBool("replicateBorder", replicateBorder);
	GetBool("fadeoutToGray", fadeoutToGray);
	GetBool("ignorePngGamma", ignorePngGamma);
	GetInt("wrapMode", wrapMode);
	GetInt("filterMode", filterMode);
	GetFloat("anisoLevel", anisoLevel);
	GetInt("maxSize", maxSize);
	GetInt("resizeAlgorithm", resizeAlgorithm);
	GetInt("format", format);
	GetInt("compressionQuality", compression);
	GetBool("useCrunchCompression", useCrunchCompression);

	return true;
}







bool MaterialDescriptor::SaveMaterialDescriptor(const std::string& filepath) {
	using namespace rapidjson;

	// Create a JSON document
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();

	std::string filename = std::filesystem::path(filepath).stem().string();

	// Add top-level members
	document.AddMember("name", Value(filename.c_str(), allocator), allocator); // Change as needed
	document.AddMember("type", Value("Example", allocator), allocator);

	// Add "properties" object
	Value properties(kObjectType);

	// Add "color" array
	Value color(kArrayType);
	color.PushBack(albedoColorRed, allocator)
		.PushBack(albedoColorGreen, allocator)
		.PushBack(albedoColorBlue, allocator)
		.PushBack(albedoColorAlpha, allocator);
	properties.AddMember("color", color, allocator);

	// Add other properties
	properties.AddMember("shininess", smoothness, allocator);
//	properties.AddMember("textureID", textureID, allocator); // Assuming textureID exists in your class
	
	rapidjson::Value shaderValue(shaderChosen.c_str(), allocator); // Convert std::string to rapidjson::Value
	properties.AddMember("shader", shaderValue, allocator);
	properties.AddMember("reflectivity", metallic, allocator);

	// Attach "properties" to the main document
	document.AddMember("properties", properties, allocator);

	// Write JSON to file
	std::ofstream ofs(filepath, std::ios::out | std::ios::trunc);
	if (!ofs) {
		std::cerr << "Error: Unable to open file for writing: " << filepath << std::endl;
		return false;
	}

	// Use PrettyWriter to write the JSON document
	OStreamWrapper osw(ofs);
	PrettyWriter<OStreamWrapper> writer(osw);

	if (!document.Accept(writer)) {
		std::cerr << "Error: Failed to write JSON data to file." << std::endl;
		return false;
	}

	return true;
}


bool MaterialDescriptor::LoadMaterialDescriptor(const std::string& filepath) {
	using namespace rapidjson;

	// Open the file
	std::ifstream ifs(filepath, std::ios::in);
	if (!ifs.is_open()) {
		std::cerr << "Error: Failed to open descriptor file: " << filepath << std::endl;
		return false;
	}

	// Parse the JSON file
	IStreamWrapper isw(ifs);
	Document document;
	if (document.ParseStream(isw).HasParseError()) {
		std::cerr << "Error: Failed to parse descriptor file: " << filepath
			<< " (Error code: " << document.GetParseError()
			<< ", Offset: " << document.GetErrorOffset() << ")" << std::endl;
		return false;
	}

	if (!document.IsObject()) {
		std::cerr << "Error: Descriptor file does not contain a valid JSON object: " << filepath << std::endl;
		return false;
	}

	// Extract top-level values
	if (document.HasMember("name") && document["name"].IsString()) {
		std::string name = document["name"].GetString();
		std::cout << "Material Name: " << name << std::endl;
	}

	if (document.HasMember("type") && document["type"].IsString()) {
		std::string type = document["type"].GetString();
		std::cout << "Material Type: " << type << std::endl;
	}

	// Extract properties object
	if (document.HasMember("properties") && document["properties"].IsObject()) {
		const Value& properties = document["properties"];

		// Extract color array
		if (properties.HasMember("color") && properties["color"].IsArray()) {
			const Value& color = properties["color"];
			if (color.Size() == 4) {
				albedoColorRed = color[0].GetFloat();
				albedoColorGreen = color[1].GetFloat();
				albedoColorBlue = color[2].GetFloat();
				albedoColorAlpha = color[3].GetFloat();
			}
		}

		// Extract other properties
		if (properties.HasMember("shininess") && properties["shininess"].IsFloat()) {
			smoothness = properties["shininess"].GetFloat();
		}

		
		if (properties.HasMember("shader") && properties["shader"].IsString()) {
			std::string shader = properties["shader"].GetString();
			std::cout << "Shader: " << shader << std::endl;
		}

		if (properties.HasMember("reflectivity") && properties["reflectivity"].IsFloat()) {
			metallic = properties["reflectivity"].GetFloat();
		}
	}

	return true;
}
