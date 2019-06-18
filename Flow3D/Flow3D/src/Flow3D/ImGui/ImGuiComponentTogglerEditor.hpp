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
				int componentID = -1;
				std::string currentComponentName = toggler->GetComponentToToggle().GetName();
				std::vector<const char*> chars;
				for (unsigned int i = 0; i < componentNames.size(); i++)
				{
					if (componentNames[i] == currentComponentName)
						componentID = i;

					chars.push_back(componentNames[i].c_str());
				}

				ImGui::PushItemWidth(200);

				if (ImGui::Combo("Components", &componentID, &chars[0], (int)chars.size()))
					toggler->SetComponentToToggle(components[componentID].get());

				ImGui::PopItemWidth();
			}			
		}		
	};
}
