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

namespace Flow {

	struct ComponentTogglerEditor
	{

		ComponentTogglerEditor () {}

		void Draw(ComponentToggler* toggler, const std::vector<std::unique_ptr<Component>>& components, std::vector<std::string> componentNames)
		{
			if (toggler != nullptr)
			{
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
				}				

				ImGui::PopItemWidth();
			}			
		}		
	};
}
