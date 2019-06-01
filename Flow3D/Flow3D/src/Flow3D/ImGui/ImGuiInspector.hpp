#pragma once

#include "imgui/imgui.h"

#include "Flow3D/GameObject.hpp"

namespace Flow {

	struct Flow3DInspector 
	{
		std::string gameObjectName;
		bool gameObjectSet;

		Flow3DInspector() 
		{
			gameObjectSet = false;
		}

		void SetGameObject(std::string name)
		{
			gameObjectName = name;
			FLOW_CORE_INFO("in inspector the name is {0}", gameObjectName);
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
					ImGui::SetWindowFontScale(1.7f);
					ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.8f, 1.0f), gameObjectName.c_str());
					ImGui::SetWindowFontScale(1.0f);
				}
					

				ImGui::End();
			}
		}

	};

}
