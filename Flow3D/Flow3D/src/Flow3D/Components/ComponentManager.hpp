#pragma once

#include "Component.hpp"
// Add all the different component classes here
#include "Lighting.hpp"
#include "FreeCamera.hpp"
#include "Renderable.hpp"
#include "Rotatable.hpp"
#include "ComponentToggler.hpp"
#include "GameObjectToggler.hpp"

class ComponentManager
{

public:

	static void AddComponentToGameObject(std::string componentName, GameObject& gameObject);

	static std::vector<const char*> GetAllComponentNames() 
	{ 
		std::vector<const char*> componentNames;

		componentNames.push_back("Rotatable");
		componentNames.push_back("FreeCamera");
		componentNames.push_back("Renderable");
		componentNames.push_back("DirectionalLight");
		componentNames.push_back("PointLight");
		componentNames.push_back("SpotLight");
		componentNames.push_back("ComponentToggler");
		componentNames.push_back("GameObjectToggler");

		return componentNames; 
	}
	
};
