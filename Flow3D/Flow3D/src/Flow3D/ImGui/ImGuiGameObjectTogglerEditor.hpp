#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/GameObjectToggler.hpp"

namespace Flow {

	struct GameObjectTogglerEditor
	{

		GameObjectTogglerEditor() {}

		void Draw(GameObjectToggler* toggler)
		{
			std::string name = toggler->GetGameObjectName();
			static char nameBuffer[32] = "thisisamerica";
			strcpy(nameBuffer, name.c_str());
			if (ImGui::InputText("Name of GameObject", nameBuffer, IM_ARRAYSIZE(nameBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
				toggler->SetGameObjectName(nameBuffer);
		}
	};
}
