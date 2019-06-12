#include "ImGuiInspector.hpp"
#include "Flow3D/Components/FreeCamera.hpp"
#include "Flow3D/Components/GameObjectToggler.hpp"
#include "Flow3D/Components/Lighting.hpp"
#include "Flow3D/Math.hpp"

#include <cstring>

namespace Flow {
	
	Flow3DInspector::Flow3DInspector()
	{
		gameObjectSet = false;
	}

	void Flow3DInspector::SetGameObject(GameObject* gameObject)
	{
		currentGameObject = gameObject;
		gameObjectSet = true;
	}

	void Flow3DInspector::Draw()
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

				const std::vector<std::unique_ptr<Component>>& components = currentGameObject->GetComponents();
				for (unsigned int i = 0; i < components.size(); i++)
				{
					Component& component = *components[i];

					if (ImGui::TreeNodeEx(component.GetName().c_str(), ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
					{
						bool componentActive = component.GetEnabled();
						if (ImGui::Checkbox("Enabled", &componentActive))
							component.SetEnabled(componentActive);

						if (component.GetName() == "FreeCamera")
						{
							FreeCamera* freeCamera = dynamic_cast<FreeCamera*>(components[i].get());
							
							ImGui::Text("Movement Speed");
							ImGui::SameLine(0, 71);
							ImGui::PushItemWidth(100);

							float movementSpeed = freeCamera->GetMovementSpeed();
							if (ImGui::DragFloat("##4", &movementSpeed, 0.1f))
								freeCamera->SetMovementSpeed(movementSpeed);

							ImGui::Text("Mouse Sensitivity");
							ImGui::SameLine(0, 50);
							ImGui::PushItemWidth(100);

							float mouseSensitivity = freeCamera->GetMouseSensitivy();
							if (ImGui::DragFloat("##5", &mouseSensitivity, 0.01f))
								freeCamera->SetMouseSensititvy(mouseSensitivity);

							ImGui::Text("Field of view");
							ImGui::SameLine(0, 78);
							ImGui::PushItemWidth(100);

							float zoom = freeCamera->GetZoom();
							if (ImGui::DragFloat("##6", &zoom, 0.1f, 0.0f, 100.0f))
								freeCamera->SetZoom(zoom);

							ImGui::Text("Z-Near");
							ImGui::SameLine(0, 127);
							ImGui::PushItemWidth(100);

							float zNear = freeCamera->GetZNear();
							float zFar = freeCamera->GetZFar();
							if (ImGui::DragFloat("##7", &zNear, 0.1f, 0.0f, zFar))
								freeCamera->SetZNear(zNear);

							ImGui::Text("Z-Far");
							ImGui::SameLine(0, 134);
							ImGui::PushItemWidth(100);
							if (ImGui::DragFloat("##8", &zFar, 0.1f, zNear, 1000.0f))
								freeCamera->SetZFar(zFar);
						}

						if (component.GetName() == "GameObjectToggler")
						{
							GameObjectToggler* toggler = dynamic_cast<GameObjectToggler*>(components[i].get());
							std::string name = toggler->GetGameObjectName();
							static char nameBuffer[32] = "thisisamerica";
							strcpy(nameBuffer, name.c_str());
							if (ImGui::InputText("Name of GameObject", nameBuffer, IM_ARRAYSIZE(nameBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
								toggler->SetGameObjectName(nameBuffer);
						}

						if (component.GetName() == "DirectionalLight")
						{
							DirectionalLight* dl = dynamic_cast<DirectionalLight*>(components[i].get());
							
							Vec3 ambient = dl->GetAmbientIntensity();
							float ambientR, ambientG, ambientB;
							ambientR = ambient.x;
							ambientG = ambient.y;
							ambientB = ambient.z;
							ImGui::Text("Ambient");
							ImGui::SameLine(0, 20);
							ImGui::PushItemWidth(66);

							if (ImGui::DragFloat("r##8", &ambientR, 0.01f, 0.0f, 1.0f))
								dl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

							ImGui::SameLine();
							if (ImGui::DragFloat("g##8", &ambientG, 0.01f, 0.0f, 1.0f))
								dl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

							ImGui::SameLine();
							if (ImGui::DragFloat("b##8", &ambientB, 0.01f, 0.0f, 1.0f))
								dl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

							ImGui::PopItemWidth();

							Vec3 diffuse = dl->GetDiffuseIntensity();
							float diffuseR, diffuseG, diffuseB;
							diffuseR = diffuse.x;
							diffuseG = diffuse.y;
							diffuseB = diffuse.z;
							ImGui::Text("Diffuse");
							ImGui::SameLine(0, 20);
							ImGui::PushItemWidth(66);

							if (ImGui::DragFloat("r##9", &diffuseR, 0.01f, 0.0f, 1.0f))
								dl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

							ImGui::SameLine();
							if (ImGui::DragFloat("g##9", &diffuseG, 0.01f, 0.0f, 1.0f))
								dl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

							ImGui::SameLine();
							if (ImGui::DragFloat("b##9", &diffuseB, 0.01f, 0.0f, 1.0f))
								dl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

							ImGui::PopItemWidth();

							Vec3 specular = dl->GetSpecularIntensity();
							float specularR, specularG, specularB;
							specularR = specular.x;
							specularG = specular.y;
							specularB = specular.z;
							ImGui::Text("Specular");
							ImGui::SameLine(0, 13);
							ImGui::PushItemWidth(66);

							if (ImGui::DragFloat("r##10", &specularR, 0.01f, 0.0f, 1.0f))
								dl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

							ImGui::SameLine();
							if (ImGui::DragFloat("g##10", &specularG, 0.01f, 0.0f, 1.0f))
								dl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

							ImGui::SameLine();
							if (ImGui::DragFloat("b##10", &specularB, 0.01f, 0.0f, 1.0f))
								dl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

							ImGui::PopItemWidth();

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

						if (component.GetName() == "PointLight")
						{
							PointLight* pl = dynamic_cast<PointLight*>(components[i].get());

							Vec3 ambient = pl->GetAmbientIntensity();
							float ambientR, ambientG, ambientB;
							ambientR = ambient.x;
							ambientG = ambient.y;
							ambientB = ambient.z;
							ImGui::Text("Ambient");
							ImGui::SameLine(0, 20);
							ImGui::PushItemWidth(66);

							if (ImGui::DragFloat("r##12", &ambientR, 0.01f, 0.0f, 1.0f))
								pl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

							ImGui::SameLine();
							if (ImGui::DragFloat("g##12", &ambientG, 0.01f, 0.0f, 1.0f))
								pl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

							ImGui::SameLine();
							if (ImGui::DragFloat("b##12", &ambientB, 0.01f, 0.0f, 1.0f))
								pl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

							ImGui::PopItemWidth();

							Vec3 diffuse = pl->GetDiffuseIntensity();
							float diffuseR, diffuseG, diffuseB;
							diffuseR = diffuse.x;
							diffuseG = diffuse.y;
							diffuseB = diffuse.z;
							ImGui::Text("Diffuse");
							ImGui::SameLine(0, 20);
							ImGui::PushItemWidth(66);

							if (ImGui::DragFloat("r##13", &diffuseR, 0.01f, 0.0f, 1.0f))
								pl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

							ImGui::SameLine();
							if (ImGui::DragFloat("g##13", &diffuseG, 0.01f, 0.0f, 1.0f))
								pl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

							ImGui::SameLine();
							if (ImGui::DragFloat("b##13", &diffuseB, 0.01f, 0.0f, 1.0f))
								pl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

							ImGui::PopItemWidth();

							Vec3 specular = pl->GetSpecularIntensity();
							float specularR, specularG, specularB;
							specularR = specular.x;
							specularG = specular.y;
							specularB = specular.z;
							ImGui::Text("Specular");
							ImGui::SameLine(0, 13);
							ImGui::PushItemWidth(66);

							if (ImGui::DragFloat("r##14", &specularR, 0.01f, 0.0f, 1.0f))
								pl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

							ImGui::SameLine();
							if (ImGui::DragFloat("g##14", &specularG, 0.01f, 0.0f, 1.0f))
								pl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

							ImGui::SameLine();
							if (ImGui::DragFloat("b##14", &specularB, 0.01f, 0.0f, 1.0f))
								pl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

							ImGui::PopItemWidth();

							if (ImGui::TreeNodeEx("Attenuation", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
							{
								Attenuation& att = pl->GetAttenuation();
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

						if (component.GetName() == "SpotLight")
						{
							SpotLight* sl = dynamic_cast<SpotLight*>(components[i].get());

							Vec3 ambient = sl->GetAmbientIntensity();
							float ambientR, ambientG, ambientB;
							ambientR = ambient.x;
							ambientG = ambient.y;
							ambientB = ambient.z;
							ImGui::Text("Ambient");
							ImGui::SameLine(0, 20);
							ImGui::PushItemWidth(66);

							if (ImGui::DragFloat("r##16", &ambientR, 0.01f, 0.0f, 1.0f))
								sl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

							ImGui::SameLine();
							if (ImGui::DragFloat("g##16", &ambientG, 0.01f, 0.0f, 1.0f))
								sl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

							ImGui::SameLine();
							if (ImGui::DragFloat("b##16", &ambientB, 0.01f, 0.0f, 1.0f))
								sl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

							ImGui::PopItemWidth();

							Vec3 diffuse = sl->GetDiffuseIntensity();
							float diffuseR, diffuseG, diffuseB;
							diffuseR = diffuse.x;
							diffuseG = diffuse.y;
							diffuseB = diffuse.z;
							ImGui::Text("Diffuse");
							ImGui::SameLine(0, 20);
							ImGui::PushItemWidth(66);

							if (ImGui::DragFloat("r##17", &diffuseR, 0.01f, 0.0f, 1.0f))
								sl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

							ImGui::SameLine();
							if (ImGui::DragFloat("g##17", &diffuseG, 0.01f, 0.0f, 1.0f))
								sl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

							ImGui::SameLine();
							if (ImGui::DragFloat("b##17", &diffuseB, 0.01f, 0.0f, 1.0f))
								sl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

							ImGui::PopItemWidth();

							Vec3 specular = sl->GetSpecularIntensity();
							float specularR, specularG, specularB;
							specularR = specular.x;
							specularG = specular.y;
							specularB = specular.z;
							ImGui::Text("Specular");
							ImGui::SameLine(0, 13);
							ImGui::PushItemWidth(66);

							if (ImGui::DragFloat("r##18", &specularR, 0.01f, 0.0f, 1.0f))
								sl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

							ImGui::SameLine();
							if (ImGui::DragFloat("g##18", &specularG, 0.01f, 0.0f, 1.0f))
								sl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

							ImGui::SameLine();
							if (ImGui::DragFloat("b##18", &specularB, 0.01f, 0.0f, 1.0f))
								sl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

							ImGui::PopItemWidth();

							if (ImGui::TreeNodeEx("Attenuation", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
							{
								Attenuation& att = sl->GetAttenuation();
								float constant, linear, exponent;
								constant = att.GetConstant();
								linear = att.GetLinear();
								exponent = att.GetExponent();

								ImGui::PushItemWidth(150);
								if (ImGui::DragFloat("Constant##19", &constant, 0.01f, 0.0f, 100.0f))
									att.SetConstant(constant);

								if (ImGui::DragFloat("Linear##19", &linear, 0.01f, 0.0f, 100.0f))
									att.SetLinear(linear);

								if (ImGui::DragFloat("Exponent##19", &exponent, 0.001f, 0.0f, 100.0f))
									att.SetExponent(exponent);

								ImGui::PopItemWidth();
								ImGui::TreePop();
							}

							float cutoff = sl->GetCutoff();
							float outerCutoff = sl->GetOuterCutoff();
							ImGui::PushItemWidth(150);
							if (ImGui::DragFloat("Cutoff##20", &cutoff, 0.1f, 0.0f, 360.0f))
								sl->SetCutoff(cutoff);

							if (ImGui::DragFloat("OuterCutoff##20", &outerCutoff, 0.1f, 0.0f, 360.0f))
								sl->SetOuterCutoff(outerCutoff);

							ImGui::PopItemWidth();
						}

						ImGui::TreePop();
					}

					ImGui::Separator();
				}
			}


			ImGui::End();
		}
	}
}
