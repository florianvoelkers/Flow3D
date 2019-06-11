#pragma once

#include "imgui/imgui.h"

#include "Flow3D/GameObject.hpp"
#include "Flow3D/Components/Component.hpp"

namespace Flow {

	// Struct for creating a Flow3DInspector Window
	struct Flow3DInspector 
	{
		std::string gameObjectName;
		bool gameObjectSet;
		GameObject* currentGameObject;

		Flow3DInspector() 
		{
			gameObjectSet = false;
		}

		void SetGameObject(GameObject* gameObject)
		{
			currentGameObject = gameObject;
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
					
					bool gameObjectActive = currentGameObject->GetIsActive();
					if (ImGui::Checkbox("", &gameObjectActive))
						currentGameObject->SetActive(gameObjectActive);

					ImGui::SameLine(0, 20.0f);
					ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.8f, 1.0f), currentGameObject->GetName().c_str());

					ImGui::Separator();
					ImGui::Separator();

					
					if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
					{
						Transform& transform = currentGameObject->GetTransform();
						Vec3 position = transform.GetPosition();
						float posX = position.x;
						float posY = position.y;
						float posZ = position.z;
						ImGui::Text("Position");
						ImGui::SameLine(); 
						ImGui::PushItemWidth(75);

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
						ImGui::PushItemWidth(75);

						if (ImGui::DragFloat("x##2", &rotX, 1.0f, -360.0f, 360.0f))
							transform.Rotate(Vec3(1.0f, 0.0f, 0.0f), rotX - transform.GetRotation().x);

						ImGui::SameLine();
						if (ImGui::DragFloat("y##2", &rotY, 1.0f, -360.0f, 360.0f))
							transform.Rotate(Vec3(0.0f, 1.0f, 0.0f), rotY - transform.GetRotation().y);

						ImGui::SameLine();
						if (ImGui::DragFloat("z##2", &rotZ, 1.0f, -360.0f, 360.0f))
							transform.Rotate(Vec3(0.0f, 0.0f, 1.0f), rotZ - transform.GetRotation().z);
						
						ImGui::PopItemWidth();

						/*
						Quaternion orientation = transform.GetOrientation();
						float quatX = orientation.x;
						float quatY = orientation.y;
						float quatZ = orientation.z;
						float quatW = orientation.w;
						ImGui::Text("Quat");
						ImGui::SameLine(0, 36);
						ImGui::PushItemWidth(56);

						Quaternion rotationQuat;
						if (ImGui::DragFloat("x##4", &quatX, 0.01f, -1.0f, 1.0f))
						{
							rotationQuat = Quaternion(quatX - orientation.x, 0.0f, 0.0f, 1.0f);
							transform.Rotate(rotationQuat);
						}							

						ImGui::SameLine();
						if (ImGui::DragFloat("y##4", &quatY, 0.01f, -1.0f, 1.0f))
						{
							rotationQuat = Quaternion(0.0f, quatY - orientation.y, 0.0f, 1.0f);
							transform.Rotate(rotationQuat);
						}

						ImGui::SameLine();
						if (ImGui::DragFloat("z##4", &quatZ, 0.01f, -1.0f, 1.0f))
						{
							rotationQuat = Quaternion(0.0f, 0.0f, quatZ - orientation.z, 1.0f);
							transform.Rotate(rotationQuat);
						}

						ImGui::SameLine();
						ImGui::Text("%.3f w", orientation.w);
						//ImGui::DragFloat("w##4", &quatW, 0.0f, -1.0f, 1.0f);
							//transform.SetOrientation(Quaternion(orientation.x, orientation.y, orientation.z, quatW));

						ImGui::PopItemWidth();
						*/

						float scaleX = transform.GetScale().x;
						float scaleY = transform.GetScale().y;
						float scaleZ = transform.GetScale().z;
						ImGui::Text("Scale");
						ImGui::SameLine(0, 29);
						ImGui::PushItemWidth(75);

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

					const std::vector<std::unique_ptr<Component>>& components = currentGameObject->GetComponents();
					for (unsigned int i = 0; i < components.size(); i++)
					{
						Component& component = *components[i];
						
						if (ImGui::TreeNodeEx(component.GetName().c_str(), ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
						{
							bool componentActive = component.GetEnabled();
							if (ImGui::Checkbox("Enabled", &componentActive))
								component.SetEnabled(componentActive);

							ImGui::TreePop();
						}

						ImGui::Separator();
					}
				}
					

				ImGui::End();
			}
		}

	};

}
