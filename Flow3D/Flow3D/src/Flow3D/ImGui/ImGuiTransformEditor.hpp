#pragma once

#include <imgui/imgui.h>

#include "Flow3D/GameObject.hpp"

namespace Flow {

	struct TransformEditor
	{

		TransformEditor()
		{

		}

		void Draw(Transform& transform)
		{
			if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
			{
				Vec3 position = transform.GetPosition();
				float posX = position.x;
				float posY = position.y;
				float posZ = position.z;
				ImGui::Text("Position");
				ImGui::SameLine();
				ImGui::PushItemWidth(66);

				if (ImGui::DragFloat("x##1", &posX, 0.1f))
					transform.SetPosition(Vec3(posX, posY, posZ));

				ImGui::SameLine();
				if (ImGui::DragFloat("y##1", &posY, 0.1f))
					transform.SetPosition(Vec3(posX, posY, posZ));

				ImGui::SameLine();
				if (ImGui::DragFloat("z##1", &posZ, 0.1f))
					transform.SetPosition(Vec3(posX, posY, posZ));

				ImGui::PopItemWidth();

				Vec3 rotation = transform.GetRotation();
				float rotX = rotation.x;
				float rotY = rotation.y;
				float rotZ = rotation.z;
				ImGui::Text("Rotation");
				ImGui::SameLine();
				ImGui::PushItemWidth(66);

				if (ImGui::DragFloat("x##2", &rotX, 1.0f, -360.0f, 360.0f))
					transform.Rotate(Vec3(1.0f, 0.0f, 0.0f), rotX - transform.GetRotation().x);

				ImGui::SameLine();
				if (ImGui::DragFloat("y##2", &rotY, 1.0f, -360.0f, 360.0f))
					transform.Rotate(Vec3(0.0f, 1.0f, 0.0f), rotY - transform.GetRotation().y);

				ImGui::SameLine();
				if (ImGui::DragFloat("z##2", &rotZ, 1.0f, -360.0f, 360.0f))
					transform.Rotate(Vec3(0.0f, 0.0f, 1.0f), rotZ - transform.GetRotation().z);

				ImGui::PopItemWidth();

				float scaleX = transform.GetScale().x;
				float scaleY = transform.GetScale().y;
				float scaleZ = transform.GetScale().z;
				ImGui::Text("Scale");
				ImGui::SameLine(0, 29);
				ImGui::PushItemWidth(66);

				if (ImGui::DragFloat("x##3", &scaleX, 0.01f))
					transform.SetScale(Vec3(scaleX, scaleY, scaleZ));

				ImGui::SameLine();
				if (ImGui::DragFloat("y##3", &scaleY, 0.01f))
					transform.SetScale(Vec3(scaleX, scaleY, scaleZ));

				ImGui::SameLine();
				if (ImGui::DragFloat("z##3", &scaleZ, 0.01f))
					transform.SetScale(Vec3(scaleX, scaleY, scaleZ));

				ImGui::PopItemWidth();

				ImGui::TreePop();
			}

			ImGui::Separator();
		}
	};
}
