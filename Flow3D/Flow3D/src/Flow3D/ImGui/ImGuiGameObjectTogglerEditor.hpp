#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/GameObjectToggler.hpp"

namespace Flow {

	struct GameObjectTogglerEditor
	{

		GameObjectTogglerEditor() {}

		void Draw(GameObjectToggler* toggler)
		{
			if (toggler != nullptr)
			{
				/*
				std::string name = toggler->GetGameObjectName();
				static char nameBuffer[32] = "GameObject";
				strcpy(nameBuffer, name.c_str());
				if (ImGui::InputText("Name of GameObject", nameBuffer, IM_ARRAYSIZE(nameBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
					toggler->SetGameObjectName(nameBuffer);
					*/

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
				}
			}			
		}
	};
}
