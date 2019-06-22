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

				bool constrainPositionX = transform.GetConstrainPositionX();
				bool constrainPositionY = transform.GetConstrainPositionY();
				bool constrainPositionZ = transform.GetConstrainPositionZ();
				
				ImGui::Text("Constraints:");
				ImGui::SameLine(0, 20);
				if (ImGui::Checkbox("x##1constrain", &constrainPositionX))
					transform.ConstrainPosition(constrainPositionX, constrainPositionY, constrainPositionZ);
				ImGui::SameLine(0, 20);
				if (ImGui::Checkbox("y##1constrain", &constrainPositionY))
					transform.ConstrainPosition(constrainPositionX, constrainPositionY, constrainPositionZ);
				ImGui::SameLine(0, 20);
				if (ImGui::Checkbox("z##1constrain", &constrainPositionZ))
					transform.ConstrainPosition(constrainPositionX, constrainPositionY, constrainPositionZ);

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

				bool constrainRotationX = transform.GetConstrainRotationX();
				bool constrainRotationY = transform.GetConstrainRotationY();
				bool constrainRotationZ = transform.GetConstrainRotationZ();

				ImGui::Text("Constraints:");
				ImGui::SameLine(0, 20);
				if (ImGui::Checkbox("x##2constrain", &constrainRotationX))
					transform.ConstrainRotation(constrainRotationX, constrainRotationY, constrainRotationZ);
				ImGui::SameLine(0, 20);
				if (ImGui::Checkbox("y##2constrain", &constrainRotationY))
					transform.ConstrainRotation(constrainRotationX, constrainRotationY, constrainRotationZ);
				ImGui::SameLine(0, 20);
				if (ImGui::Checkbox("z##2constrain", &constrainRotationZ))
					transform.ConstrainRotation(constrainRotationX, constrainRotationY, constrainRotationZ);

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

				bool constrainScaleX = transform.GetConstrainScaleX();
				bool constrainScaleY = transform.GetConstrainScaleY();
				bool constrainScaleZ = transform.GetConstrainScaleZ();

				ImGui::Text("Constraints:");
				ImGui::SameLine(0, 20);
				if (ImGui::Checkbox("x##3constrain", &constrainScaleX))
					transform.SetConstrainScaleX(constrainScaleX);
				ImGui::SameLine(0, 20);
				if (ImGui::Checkbox("y##3constrain", &constrainScaleY))
					transform.SetConstrainScaleY(constrainScaleY);
				ImGui::SameLine(0, 20);
				if (ImGui::Checkbox("z##3constrain", &constrainScaleZ))
					transform.SetConstrainScaleZ(constrainScaleZ);

				ImGui::TreePop();
			}

			ImGui::Separator();
		}
	};
}
