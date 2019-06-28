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
	static std::string ChooseComponentPopup(std::string componentName);
	static void ShowComponentEditor(std::string componentName, std::vector<std::string> componentNames, Component* component, const std::vector<std::shared_ptr<Component>>& components);
	static void SerializeComponent(const std::string& componentName, std::ofstream& myfile, Component* component, const std::string& componentDirectory);

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
