#include "ComponentManager.hpp"

const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

// All class definitions for components
// CLASS_DEFINITION(parent class, sub class)
CLASS_DEFINITION(Component, Rotatable)
CLASS_DEFINITION(Component, FreeCamera)
CLASS_DEFINITION(Component, Renderable)
CLASS_DEFINITION(Component, BaseLight)
CLASS_DEFINITION(BaseLight, DirectionalLight)
CLASS_DEFINITION(BaseLight, PointLight)
CLASS_DEFINITION(BaseLight, SpotLight)
CLASS_DEFINITION(Component, ComponentToggler)
CLASS_DEFINITION(Component, GameObjectToggler)

#include "Flow3D/ImGui/ImGuiFreeCameraEditor.hpp"
#include "Flow3D/ImGui/ImGuiGameObjectTogglerEditor.hpp"
#include "Flow3D/ImGui/ImGuiComponentTogglerEditor.hpp"
#include "Flow3D/ImGui/ImGuiDirectionalLightEditor.hpp"
#include "Flow3D/ImGui/ImGuiPointLightEditor.hpp"
#include "Flow3D/ImGui/ImGuiSpotLightEditor.hpp"
#include "Flow3D/ImGui/ImGuiRenderableEditor.hpp"

#include "Flow3D/Serializer.hpp"

#include <io.h>     // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <filesystem>

std::string ComponentManager::ChooseComponentPopup(std::string componentName)
{
	if (componentName == "Rotatable")
	{
		return "Rotatable";
	}
	else if (componentName == "FreeCamera")
	{
		return "FreeCamera";
	}
	else if (componentName == "Renderable")
	{
		return "Renderable";
	}
	else if (componentName == "DirectionalLight")
	{
		return "DirectionalLight";
	}
	else if (componentName == "PointLight")
	{
		return "PointLight";
	}
	else if (componentName == "SpotLight")
	{
		return "SpotLight";
	}
	else if (componentName == "ComponentToggler")
	{
		return "ComponentToggler";
	}
	else if (componentName == "GameObjectToggler")
	{
		return "GameObjectToggler";
	}
}

void ComponentManager::DuplicateComponent(Component & component, GameObject& gameObject)
{
	std::string componentName = component.GetName();
	if (componentName == "FreeCamera")
	{
		FLOW_CORE_WARN("a camera component should not be copied");
	}
	else if (componentName == "GameObjectToggler")
	{
		gameObject.AddComponent<GameObjectToggler>(&gameObject, component.GetEnabled());

		GameObjectToggler* goToggler = dynamic_cast<GameObjectToggler*>(&component);
		std::vector<std::tuple<GameObject*, std::string, Keycode>>& gameObjectsToToggle = goToggler->GetGameObjectsToToggle();

		GameObjectToggler& togglerOfNewGameObject = gameObject.GetComponent<GameObjectToggler>();
		for (unsigned int i = 0; i < gameObjectsToToggle.size(); i++)
		{
			togglerOfNewGameObject.AddGameObjectToToggle(std::make_tuple(std::get<0>(gameObjectsToToggle[i]), 
				std::get<1>(gameObjectsToToggle[i]), std::get<2>(gameObjectsToToggle[i])), false);
		}
	}
	else if (componentName == "ComponentToggler")
	{
		gameObject.AddComponent<ComponentToggler>(&gameObject, component.GetEnabled());

		ComponentToggler* toggler = dynamic_cast<ComponentToggler*>(&component);
		std::vector<std::tuple<Component*, Keycode>>& componentsToToggle = toggler->GetComponentsToToggle();

		ComponentToggler& togglerOfNewGameObject = gameObject.GetComponent<ComponentToggler>();
		for (unsigned int i = 0; i < componentsToToggle.size(); i++)
		{
			togglerOfNewGameObject.AddComponentToToggle(std::make_tuple(std::get<0>(componentsToToggle[i]),
				std::get<1>(componentsToToggle[i])), false);
		}
	}
	else if (componentName == "DirectionalLight")
	{
		FLOW_CORE_WARN("a directional light component should not be copied");
	}
	else if (componentName == "PointLight")
	{
		PointLight* pointLight = dynamic_cast<PointLight*>(&component);
		gameObject.AddComponent<PointLight>(&gameObject, pointLight->GetAmbientIntensity(), pointLight->GetDiffuseIntensity(), pointLight->GetSpecularIntensity(),
			pointLight->GetAttenuation(), pointLight->GetEnabled());
		Application::Get().GetCurrentScene().AddPointLight(&gameObject.GetComponent<PointLight>());
	}
	else if (componentName == "SpotLight")
	{
		SpotLight* spotLight = dynamic_cast<SpotLight*>(&component);
		gameObject.AddComponent<SpotLight>(&gameObject, spotLight->GetAmbientIntensity(), spotLight->GetDiffuseIntensity(), spotLight->GetSpecularIntensity(),
			spotLight->GetCutoff(), spotLight->GetOuterCutoff(), spotLight->GetAttenuation(), spotLight->GetEnabled());
		Application::Get().GetCurrentScene().AddPointLight(&gameObject.GetComponent<PointLight>());
	}
	else if (componentName == "Renderable")
	{
		
	}
}

void ComponentManager::ShowComponentEditor(std::string componentName, std::vector<std::string> componentNames, Component* component, const std::vector<std::shared_ptr<Component>>& components)
{
	if (componentName == "FreeCamera")
	{
		FreeCameraEditor editor = FreeCameraEditor();
		editor.Draw(dynamic_cast<FreeCamera*>(component));
	}
	else if (componentName == "GameObjectToggler")
	{
		GameObjectTogglerEditor editor = GameObjectTogglerEditor();
		editor.Draw(dynamic_cast<GameObjectToggler*>(component));
	}
	else if (componentName == "ComponentToggler")
	{
		ComponentTogglerEditor editor = ComponentTogglerEditor();
		editor.Draw(dynamic_cast<ComponentToggler*>(component), components, componentNames);
	}
	else if (componentName == "DirectionalLight")
	{
		DirectionalLightEditor editor = DirectionalLightEditor();
		editor.Draw(dynamic_cast<DirectionalLight*>(component));
	}
	else if (componentName == "PointLight")
	{
		PointLightEditor editor = PointLightEditor();
		editor.Draw(dynamic_cast<PointLight*>(component));
	}
	else if (componentName == "SpotLight")
	{
		SpotLightEditor editor = SpotLightEditor();
		editor.Draw(dynamic_cast<SpotLight*>(component));
	}
	else if (componentName == "Renderable")
	{
		RenderableEditor editor = RenderableEditor();
		editor.Draw(dynamic_cast<Renderable*>(component));
	}
}

void ComponentManager::SerializeComponent(const std::string& componentName, std::ofstream& myfile, Component* component, const std::string& componentDirectory)
{
	if (componentName == "Rotatable")
	{
		Serializer::SerializeRotatable(myfile, component);
	}
	else if (componentName == "FreeCamera")
	{
		Serializer::SerializeFreeCamera(myfile, component);
	}
	else if (componentName == "GameObjectToggler")
	{
		Serializer::SerializeGameObjectToggler(myfile, component);
	}
	else if (componentName == "ComponentToggler")
	{
		Serializer::SerializeComponentToggler(myfile, component);
	}
	else if (componentName == "DirectionalLight")
	{
		Serializer::SerializeDirectionalLight(myfile, component);
	}
	else if (componentName == "PointLight")
	{
		Serializer::SerializePointLight(myfile, component);
	}
	else if (componentName == "SpotLight")
	{
		Serializer::SerializeSpotLight(myfile, component);
	}
	else if (componentName == "Renderable")
	{
		Serializer::SerializeRenderable(myfile, component, componentDirectory);
	}
}

void ComponentManager::DeserializeComponent(const std::string& componentName, json & json, GameObject & gameObject, Scene & scene, const std::string & componentsDirectory, std::vector<std::shared_ptr<GameObject>>& gameObjectsWithGameObjectToggler)
{
	if (componentName == "Rotatable")
	{
		Serializer::DeserializeRotatable(json, gameObject, scene);
	}
	else if (componentName == "FreeCamera")
	{
		Serializer::DeserializeFreeCamera(json, gameObject, scene);
	}
	else if (componentName == "GameObjectToggler")
	{
		Serializer::DeserializeGameObjectToggler(json, gameObject, scene, gameObjectsWithGameObjectToggler);
	}
	else if (componentName == "ComponentToggler")
	{
		Serializer::DeserializeComponentToggler(json, gameObject, scene);
	}
	else if (componentName == "DirectionalLight")
	{
		Serializer::DeserializeDirectionalLight(json, gameObject, scene);
	}
	else if (componentName == "PointLight")
	{
		Serializer::DeserializePointLight(json, gameObject, scene);
	}
	else if (componentName == "SpotLight")
	{
		Serializer::DeserializeSpotLight(json, gameObject, scene);
	}
	else if (componentName == "Renderable")
	{
		Serializer::DeserializeRenderable(json, gameObject, scene, componentsDirectory);
	}
}
