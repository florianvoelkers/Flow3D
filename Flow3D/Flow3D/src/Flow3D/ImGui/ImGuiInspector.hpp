#pragma once

#include "imgui/imgui.h"

#include "Flow3D/GameObject.hpp"
#include "Flow3D/Components/Component.hpp"

namespace Flow {

	struct Flow3DInspector 
	{
		std::string gameObjectName;
		bool gameObjectSet;
		GameObject* currentGameObject;

		Flow3DInspector() 
		{
			gameObjectSet = false;
		}

		void SetGameObject(GameObject* gameObject)
		{
			currentGameObject = gameObject;
			gameObjectSet = true;
		}

		void Draw()
		{
			bool show = true;
			ImGui::SetNextWindowContentSize(ImVec2(360.0f, 960.0f));
			if (ImGui::Begin("Inspector", &show, ImGuiWindowFlags_NoCollapse))
			{
				if (gameObjectSet)
				{
					
					static bool gameObjectActive = currentGameObject->GetIsActive();
					if (ImGui::Checkbox("", &gameObjectActive))
						currentGameObject->SetActive(gameObjectActive);

					ImGui::SameLine(0, 20.0f);
					ImGui::SetWindowFontScale(1.5f);
					ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.8f, 1.0f), currentGameObject->GetName().c_str());
					ImGui::SetWindowFontScale(1.0f);

					ImGui::Separator();

					const std::vector<std::unique_ptr<Component>>& components = currentGameObject->GetComponents();
					for (unsigned int i = 0; i < components.size(); i++)
					{
						Component& component = *components[i];
						bool componentActive = component.GetEnabled();
						if (ImGui::Checkbox(component.GetName().c_str(), &componentActive))
							component.SetEnabled(componentActive);

						ImGui::Separator();
					}
				}
					

				ImGui::End();
			}
		}

	};

}
