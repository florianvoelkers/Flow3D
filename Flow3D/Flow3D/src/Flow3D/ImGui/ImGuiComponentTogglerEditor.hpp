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
			int componentID = -1;
			std::string currentComponentName = toggler->GetComponentToToggle().GetName();
			std::vector<const char*> chars;
			FLOW_CORE_INFO("component names has a size of {0}", components.size());
			for (unsigned int i = 0; i < componentNames.size(); i++)
			{				
				if (componentNames[i] == currentComponentName)
				{
					FLOW_CORE_INFO("component name found at {0}", i);
					componentID = i;
				}	
				chars.push_back(componentNames[i].c_str());
			}

			ImGui::PushItemWidth(200);	
			
			if (ImGui::Combo("Components", &componentID, &chars[0], chars.size()))
				toggler->SetComponentToToggle(components[componentID].get());

			ImGui::PopItemWidth();
		}		
	};
}
