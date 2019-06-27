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

private:

	static void SerializeChildren(const std::vector<std::shared_ptr<GameObject>>& rootChildren, std::string directory, std::ofstream& myfile);
	static std::vector<std::string> get_directories(const std::string& s);
	static unsigned int GetShaderID(const std::string& componentsDirectory);
	static std::string GetModelFilepath(const std::string& componentsDirectory);
	static unsigned int GetTextureID(const std::string& texturesDirectory, const std::string& type);
};
