#pragma once

#include "imgui/imgui.h"

#include "Flow3D/GameObject.hpp"
#include "Flow3D/Components/Component.hpp"

// Struct for creating a Flow3DInspector Window
struct Flow3DInspector 
{
	std::string gameObjectName;
	bool gameObjectSet;
	GameObject* currentGameObject;

	Flow3DInspector();

	void SetGameObject(GameObject* gameObject);

	void Draw();

};

