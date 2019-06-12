#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/Lighting.hpp"

namespace Flow {

	struct AttenuationEditor
	{
		AttenuationEditor() {}

		void Draw(Attenuation& att)
		{
			if (ImGui::TreeNodeEx("Attenuation", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
			{
				float constant, linear, exponent;
				constant = att.GetConstant();
				linear = att.GetLinear();
				exponent = att.GetExponent();

				ImGui::PushItemWidth(150);
				if (ImGui::DragFloat("Constant##15", &constant, 0.01f, 0.0f, 100.0f))
					att.SetConstant(constant);

				if (ImGui::DragFloat("Linear##15", &linear, 0.01f, 0.0f, 100.0f))
					att.SetLinear(linear);

				if (ImGui::DragFloat("Exponent##15", &exponent, 0.001f, 0.0f, 100.0f))
					att.SetExponent(exponent);

				ImGui::PopItemWidth();
				ImGui::TreePop();
			}
		}
	};
}
