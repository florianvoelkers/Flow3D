#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/Lighting.hpp"
#include "ImGuiBaseLightEditor.hpp"
#include "ImGuiAttenuationEditor.hpp"

namespace Flow {

	struct SpotLightEditor
	{

		SpotLightEditor() {}

		void Draw(SpotLight* sl)
		{
			if (sl != nullptr)
			{
				Vec3 direction = sl->GetDirection();
				float x, y, z;
				x = direction.x;
				y = direction.y;
				z = direction.z;
				ImGui::Text("Direction");
				ImGui::SameLine(0, 6);
				ImGui::PushItemWidth(66);

				if (ImGui::DragFloat("x##21", &x, 0.01f, -1.0f, 1.0f))
				{

				}

				ImGui::SameLine();
				if (ImGui::DragFloat("y##21", &y, 0.01f, -1.0f, 1.0f))
				{

				}

				ImGui::SameLine();
				if (ImGui::DragFloat("z##21", &z, 0.01f, -1.0f, 1.0f))
				{

				}

				ImGui::PopItemWidth();

				BaseLightEditor editor = BaseLightEditor();
				editor.Draw(dynamic_cast<BaseLight*>(sl));

				float cutoff = sl->GetCutoff();
				float outerCutoff = sl->GetOuterCutoff();
				ImGui::PushItemWidth(150);
				if (ImGui::DragFloat("Cutoff##20", &cutoff, 0.1f, 0.0f, 360.0f))
					sl->SetCutoff(cutoff);

				if (ImGui::DragFloat("OuterCutoff##20", &outerCutoff, 0.1f, 0.0f, 360.0f))
					sl->SetOuterCutoff(outerCutoff);

				ImGui::PopItemWidth();

				AttenuationEditor attEditor = AttenuationEditor();
				attEditor.Draw(sl->GetAttenuation());
			}			
		}
	};
}
