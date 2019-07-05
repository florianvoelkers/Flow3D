#pragma once

// this includes ComponentClasses.cpp
#include "Scene.hpp"

// basic file operations
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

// for serialization
#include <MetaStuff/include/Meta.h>
#include <json/json.hpp>
#include <MetaStuff/include/JsonCast.h>
#include <Windows.h>

class Serializer
{

public:
	
	static void Serialize(Scene& scene);
	static void Deserialize(Scene& scene);

	static void SerializeRotatable(std::ofstream & myfile, Component* component);
	static void SerializeFreeCamera(std::ofstream & myfile, Component* component);
	static void SerializeGameObjectToggler(std::ofstream & myfile, Component* component);
	static void SerializeComponentToggler(std::ofstream & myfile, Component* component);
	static void SerializeDirectionalLight(std::ofstream & myfile, Component* component);
	static void SerializePointLight(std::ofstream & myfile, Component* component);
	static void SerializeSpotLight(std::ofstream & myfile, Component* component);
	static void SerializeRenderable(std::ofstream & myfile, Component* component, const std::string& componentDirectory);

	static void DeserializeRotatable(json& json, GameObject& gameObject, Scene& scene);
	static void DeserializeFreeCamera(json& json, GameObject& gameObject, Scene& scene);
	static void DeserializeGameObjectToggler(json& json, GameObject& gameObject, Scene& scene, std::vector<std::shared_ptr<GameObject>>& gameObjectsWithGameObjectToggler);
	static void DeserializeComponentToggler(json& json, GameObject& gameObject, Scene& scene);
	static void DeserializeDirectionalLight(json& json, GameObject& gameObject, Scene& scene);
	static void DeserializePointLight(json& json, GameObject& gameObject, Scene& scene);
	static void DeserializeSpotLight(json& json, GameObject& gameObject, Scene& scene);
	static void DeserializeRenderable(json& componentAsJson, GameObject& gameObject, Scene& scene, const std::string& componentsDirectory);

private:

	static void SerializeChildren(const std::vector<std::shared_ptr<GameObject>>& rootChildren, std::string directory, std::ofstream& myfile);
	static void DeserializeChildren(const std::string rootDirectory, GameObject& parent, std::vector<const char*>& allComponentNames, Scene& scene, std::vector<std::shared_ptr<GameObject>>& gameObjectsWithGameObjectToggler);
	static std::vector<std::string> get_directories(const std::string& s);
	static std::string GetShaderName(const std::string& componentsDirectory);
	static std::string GetModelFilepath(const std::string& componentsDirectory);
	static std::string GetTexturePath(const std::string& texturesDirectory, const std::string& type);
	static void SerializeResources(std::ofstream& myfile);
	static void SerializeTextures(std::ofstream& myfile);
	static void SerializeShaders(std::ofstream& myfile);
	static void SerializeModels(std::ofstream& myfile);
	static void SerializeSkyboxes(std::ofstream& myfile);
	static void DeserializeResources();
	static void DeserializeTextures();
	static void DeserializeShaders();
	static void DeserializeModels();
	static void DeserializeSkyboxes();
	
};
