#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/Lighting.hpp"
#include "ImGuiBaseLightEditor.hpp"

namespace Flow{

	struct DirectionalLightEditor
	{

		DirectionalLightEditor() {}

		void Draw(DirectionalLight* dl)
		{
			if (dl != nullptr)
			{

				BaseLightEditor editor = BaseLightEditor();
				editor.Draw(dynamic_cast<BaseLight*>(dl), "DirectionalLight");

				Vec3 direction = dl->GetDirection();
				float x, y, z;
				x = direction.x;
				y = direction.y;
				z = direction.z;
				ImGui::Text("Direction");
				ImGui::SameLine(0, 6);
				ImGui::PushItemWidth(66);

				if (ImGui::DragFloat("x##11", &x, 0.01f, -1.0f, 1.0f))
				{
					Vec3 newDirection = Vec3(x, y, z);
					dl->SetDirection(newDirection);
				}

				ImGui::SameLine();
				if (ImGui::DragFloat("y##11", &y, 0.01f, -1.0f, 1.0f))
				{
					Vec3 newDirection = Vec3(x, y, z);
					dl->SetDirection(newDirection);
				}

				ImGui::SameLine();
				if (ImGui::DragFloat("z##11", &z, 0.01f, -1.0f, 1.0f))
				{
					Vec3 newDirection = Vec3(x, y, z);
					dl->SetDirection(newDirection);
				}

				ImGui::PopItemWidth();
			}
		}
	};
}