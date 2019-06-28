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

private:

	static void SerializeChildren(const std::vector<std::shared_ptr<GameObject>>& rootChildren, std::string directory, std::ofstream& myfile);
	static void DeserializeChildren(const std::string rootDirectory, GameObject& parent, std::vector<const char*>& allComponentNames, Scene& scene, std::vector<std::shared_ptr<GameObject>>& gameObjectsWithGameObjectToggler);
	static std::vector<std::string> get_directories(const std::string& s);
	static unsigned int GetShaderID(const std::string& componentsDirectory);
	static std::string GetModelFilepath(const std::string& componentsDirectory);
	static unsigned int GetTextureID(const std::string& texturesDirectory, const std::string& type);

	
};
