#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/ComponentToggler.hpp"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

char *convert(const std::string & s)
{
	char *pc = new char[s.size() + 1];
	std::strcpy(pc, s.c_str());
	return pc;
}

struct ComponentTogglerEditor
{

	ComponentTogglerEditor () {}

	void Draw(ComponentToggler* toggler, const std::vector<std::shared_ptr<Component>>& components, std::vector<std::string> componentNames)
	{
		if (toggler != nullptr)
		{
			if (ImGui::Button("Add entry", ImVec2(320.0f, 20.0f)))
				ImGui::OpenPopup("Add Entry to toggle");

			if (ImGui::BeginPopup("Add Entry to toggle"))
			{
				static int componentID = -1;
				std::vector<const char*> chars;
				for (unsigned int i = 0; i < componentNames.size(); i++)
					chars.push_back(componentNames[i].c_str());

				ImGui::PushItemWidth(200);
				ImGui::Combo("Components", &componentID, &chars[0], (int)chars.size());
				ImGui::PopItemWidth();

				std::vector<std::tuple<Keycode, const char*>>& keyMap = Input::Get().GetKeyMap();
				static int selectedChar = -1;
				std::vector<const char*> keysChars;
				for (unsigned int i = 0; i < keyMap.size(); i++)
					keysChars.push_back(std::get<1>(keyMap[i]));

				ImGui::Combo("Key", &selectedChar, &keysChars[0], (int)keysChars.size());

				if (ImGui::Button("Add ComponentToggler", ImVec2(320.0f, 20.0f)))
				{
					toggler->AddComponentToToggle(std::make_tuple(components[componentID].get(), std::get<0>(keyMap[selectedChar])), false);
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			std::vector<std::tuple<Component*, Keycode>>& componentsToToggle = toggler->GetComponentsToToggle();

			for (unsigned int j = 0; j < componentsToToggle.size(); j++)
			{
				int componentID = -1;
				std::string currentComponentName = std::get<0>(componentsToToggle[j])->GetName();
				std::vector<const char*> chars;
				for (unsigned int i = 0; i < componentNames.size(); i++)
				{
					if (componentNames[i] == currentComponentName)
						componentID = i;

					chars.push_back(componentNames[i].c_str());
				}

				ImGui::PushItemWidth(200);

				if (ImGui::Combo("Components", &componentID, &chars[0], (int)chars.size()))
					std::get<0>(componentsToToggle[j]) = components[componentID].get();

				std::vector<std::tuple<Keycode, const char*>>& keyMap = Input::Get().GetKeyMap();
				int selectedChar = -1;
				Keycode currentKey = std::get<1>(componentsToToggle[j]);
				std::vector<const char*> keysChars;
				for (unsigned int i = 0; i < keyMap.size(); i++)
				{
					if (currentKey == std::get<0>(keyMap[i]))
						selectedChar = i;

					keysChars.push_back(std::get<1>(keyMap[i]));
				}

				if (ImGui::Combo("Key", &selectedChar, &keysChars[0], (int)keysChars.size()))
					std::get<1>(componentsToToggle[j]) = std::get<0>(keyMap[selectedChar]);

				std::string buttonName = "Remove ";
				buttonName.append(currentComponentName);
				std::string buttonLabel = "Remove Entry##" + j;
				if (ImGui::Button(buttonLabel.c_str(), ImVec2(320.0f, 20.0f)))
					ImGui::OpenPopup(buttonName.c_str());

				if (ImGui::BeginPopupModal(buttonName.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("This entry will be removed.\n\n");
					ImGui::Separator();

					if (ImGui::Button("OK", ImVec2(120, 0)))
					{
						toggler->RemoveComponentToToggle(std::get<0>(componentsToToggle[j]));
						
						ImGui::CloseCurrentPopup();
					}
					ImGui::SetItemDefaultFocus();
					ImGui::SameLine();
					if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
					ImGui::EndPopup();
				}

				ImGui::PopItemWidth();
			}				
		}			
	}		
};

