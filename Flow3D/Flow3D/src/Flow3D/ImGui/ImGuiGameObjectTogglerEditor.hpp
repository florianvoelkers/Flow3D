#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/GameObjectToggler.hpp"

struct GameObjectTogglerEditor
{

	GameObjectTogglerEditor() {}

	void Draw(GameObjectToggler* toggler)
	{
		if (toggler != nullptr)
		{
			if (ImGui::Button("Add entry", ImVec2(320.0f, 20.0f)))
				ImGui::OpenPopup("Add Entry to toggle");

			if (ImGui::BeginPopup("Add Entry to toggle"))
			{
				static char nameBuffer[32] = "GameObject";
				ImGui::InputText("Name of GameObject", nameBuffer, IM_ARRAYSIZE(nameBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);

				ImGui::PushItemWidth(200);

				std::vector<std::tuple<Keycode, const char*>>& keyMap = Input::Get().GetKeyMap();
				static int selectedChar = -1;
				std::vector<const char*> keysChars;
				for (unsigned int i = 0; i < keyMap.size(); i++)
					keysChars.push_back(std::get<1>(keyMap[i]));

				ImGui::Combo("Key", &selectedChar, &keysChars[0], (int)keysChars.size());

				if (ImGui::Button("Add Entry", ImVec2(320.0f, 20.0f)))
				{
					GameObject* gameObjectToToggle = Application::Get().GetCurrentScene().FindGameObject(nameBuffer);
					if (gameObjectToToggle != nullptr)
					{
						toggler->AddGameObjectToToggle(std::make_tuple(gameObjectToToggle,
							nameBuffer, std::get<0>(keyMap[selectedChar])), false);
					}
					else
					{
						FLOW_CORE_INFO("Game Object not found");
					}

					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			std::vector<std::tuple<GameObject*, std::string, Keycode>>& gameObjectsToToggle = toggler->GetGameObjectsToToggle();

			for (unsigned int j = 0; j < gameObjectsToToggle.size(); j++)
			{
				std::string name = std::get<1>(gameObjectsToToggle[j]);
				static char nameBuffer[32] = "GameObject";
				strcpy(nameBuffer, name.c_str());
				if (ImGui::InputText("Name of GameObject", nameBuffer, IM_ARRAYSIZE(nameBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
				{
					GameObject* newGameObjectToToggle = Application::Get().GetCurrentScene().FindGameObject(nameBuffer);
					if (newGameObjectToToggle != nullptr)
					{
						std::get<0>(gameObjectsToToggle[j]) = newGameObjectToToggle;
						std::get<1>(gameObjectsToToggle[j]) = nameBuffer;
					}
					else
					{
						FLOW_CORE_INFO("Game Object not found");
					}
						
				}

				ImGui::PushItemWidth(200);

				std::vector<std::tuple<Keycode, const char*>>& keyMap = Input::Get().GetKeyMap();
				int selectedChar = -1;
				Keycode currentKey = std::get<2>(gameObjectsToToggle[j]);
				std::vector<const char*> keysChars;
				for (unsigned int i = 0; i < keyMap.size(); i++)
				{
					if (currentKey == std::get<0>(keyMap[i]))
						selectedChar = i;

					keysChars.push_back(std::get<1>(keyMap[i]));
				}

				if (ImGui::Combo("Key", &selectedChar, &keysChars[0], (int)keysChars.size()))
					std::get<2>(gameObjectsToToggle[j]) = std::get<0>(keyMap[selectedChar]);

				std::string buttonName = "Remove ";
				buttonName.append(name);
				std::string buttonLabel = "Remove Entry##" + j;
				if (ImGui::Button(buttonLabel.c_str(), ImVec2(320.0f, 20.0f)))
					ImGui::OpenPopup(buttonName.c_str());

				if (ImGui::BeginPopupModal(buttonName.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("This entry will be removed.\n\n");
					ImGui::Separator();

					if (ImGui::Button("OK", ImVec2(120, 0)))
					{
						toggler->RemoveGameObjectToToggle(std::get<0>(gameObjectsToToggle[j]));

						ImGui::CloseCurrentPopup();
					}
					ImGui::SetItemDefaultFocus();
					ImGui::SameLine();
					if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
					ImGui::EndPopup();
				}
			}
		}			
	}
};

