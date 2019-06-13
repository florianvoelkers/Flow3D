#include "ImGuiInspector.hpp"
#include "ImGuiTransformEditor.hpp"
#include "Flow3D/Components/FreeCamera.hpp"
#include "ImGuiFreeCameraEditor.hpp"
#include "Flow3D/Components/GameObjectToggler.hpp"
#include "ImGuiGameObjectTogglerEditor.hpp"
#include "Flow3D/Components/ComponentToggler.hpp"
#include "ImGuiComponentTogglerEditor.hpp"
#include "Flow3D/Components/Lighting.hpp"
#include "ImGuiDirectionalLightEditor.hpp"
#include "ImGuiPointLightEditor.hpp"
#include "ImGuiSpotLightEditor.hpp"
#include "Flow3D/Components/Renderable.hpp"
#include "ImGuiRenderableEditor.hpp"
#include "Flow3D/Math.hpp"

#include <cstring>

namespace Flow {
	
	Flow3DInspector::Flow3DInspector()
	{
		gameObjectSet = false;
	}

	void Flow3DInspector::SetGameObject(GameObject* gameObject)
	{
		currentGameObject = gameObject;
		gameObjectSet = true;
	}

	void Flow3DInspector::Draw()
	{
		bool show = true;
		ImGui::SetNextWindowContentSize(ImVec2(360.0f, 960.0f));
		if (ImGui::Begin("Inspector", &show, ImGuiWindowFlags_NoCollapse))
		{
			if (gameObjectSet)
			{

				bool gameObjectActive = currentGameObject->GetIsActive();
				if (ImGui::Checkbox("", &gameObjectActive))
					currentGameObject->SetActive(gameObjectActive);

				ImGui::SameLine(0, 20.0f);
				ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.8f, 1.0f), currentGameObject->GetName().c_str());

				ImGui::Separator();
				ImGui::Separator();

				TransformEditor transformEditor = TransformEditor();
				transformEditor.Draw(currentGameObject->GetTransform());
				

				const std::vector<std::unique_ptr<Component>>& components = currentGameObject->GetComponents();
				std::vector<std::string> componentNames;
				for (unsigned int i = 0; i < components.size(); i++)
				{
					Component& component = *components[i];
					std::string componentName = component.GetName();
					componentNames.push_back(componentName);
				}
				
				for (unsigned int i = 0; i < components.size(); i++)
				{
					Component& component = *components[i];
					std::string componentName = component.GetName();

					if (ImGui::TreeNodeEx(componentName.c_str(), ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
					{
						bool componentActive = component.GetEnabled();
						if (ImGui::Checkbox("Enabled", &componentActive))
							component.SetEnabled(componentActive);

						if (componentName == "FreeCamera")
						{
							FreeCameraEditor editor = FreeCameraEditor();
							editor.Draw(dynamic_cast<FreeCamera*>(components[i].get()));
						}
						else if (componentName == "GameObjectToggler")
						{
							GameObjectTogglerEditor editor = GameObjectTogglerEditor();
							editor.Draw(dynamic_cast<GameObjectToggler*>(components[i].get()));
						}
						else if (componentName == "ComponentToggler")
						{
							ComponentTogglerEditor editor = ComponentTogglerEditor();
							editor.Draw(dynamic_cast<ComponentToggler*>(components[i].get()), components, componentNames);
						}
						else if (componentName == "DirectionalLight")
						{
							DirectionalLightEditor editor = DirectionalLightEditor();
							editor.Draw(dynamic_cast<DirectionalLight*>(components[i].get()));		
						}
						else if (component.GetName() == "PointLight")
						{
							PointLightEditor editor = PointLightEditor();
							editor.Draw(dynamic_cast<PointLight*>(components[i].get()));							
						}
						else if (component.GetName() == "SpotLight")
						{
							SpotLightEditor editor = SpotLightEditor();
							editor.Draw(dynamic_cast<SpotLight*>(components[i].get()));							
						}
						else if (component.GetName() == "Renderable")
						{
							RenderableEditor editor = RenderableEditor();
							editor.Draw(dynamic_cast<Renderable*>(components[i].get()));
						}

						ImGui::TreePop();
					}

					ImGui::Separator();
				}				
			}


			ImGui::End();
		}
	}
}
