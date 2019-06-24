#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/Lighting.hpp"

struct AttenuationEditor
{
	AttenuationEditor() {}

	void Draw(Attenuation& att, std::string lightType)
	{
		if (ImGui::TreeNodeEx("Attenuation", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
		{
			float constant, linear, exponent;
			constant = att.GetConstant();
			linear = att.GetLinear();
			exponent = att.GetExponent();

			ImGui::PushItemWidth(150);
			std::string label = "Constant##15";
			label.append(lightType);
			if (ImGui::DragFloat(label.c_str(), &constant, 0.01f, 0.0f, 100.0f))
				att.SetConstant(constant);

			label = "Linear##15";
			label.append(lightType);
			if (ImGui::DragFloat(label.c_str(), &linear, 0.01f, 0.0f, 100.0f))
				att.SetLinear(linear);

			label = "Exponent##15";
			label.append(lightType);
			if (ImGui::DragFloat(label.c_str(), &exponent, 0.001f, 0.0f, 100.0f))
				att.SetExponent(exponent);

			ImGui::PopItemWidth();
			ImGui::TreePop();
		}
	}
};

