#include "ImGuiInspector.hpp"
#include "ImGuiHelper.hpp"
#include "ImGuiTransformEditor.hpp"
#include "Flow3D/Math.hpp"
#include "Flow3D/Application.hpp"
#include "Flow3D/ResourceManager.hpp"
#include "Flow3D/Components/ComponentManager.hpp"

#include <cstring>

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
	if (ImGui::Begin("Inspector", &show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	{
		if (gameObjectSet && currentGameObject != NULL)
		{
			const std::vector<std::shared_ptr<Component>>& components = currentGameObject->GetComponents();
			std::vector<std::string> componentNames;

			Scene& currentScene = Application::Get().GetCurrentScene();

			for (unsigned int i = 0; i < components.size(); i++)
			{
				Component& component = *components[i];
				std::string componentName = component.GetName();
				componentNames.push_back(componentName);
			}

			if (ImGui::Button("Add Component", ImVec2(360.0f, 20.0f)))
				ImGui::OpenPopup("select");

			if (ImGui::BeginPopup("select"))
			{
				std::vector<const char*> allComponentNames = ComponentManager::GetAllComponentNames();
				ImGui::Text("ComponentTypes");
				ImGui::Separator();
				int selectedComponent = -1;
				for (int i = 0; i < allComponentNames.size(); i++)
					if (ImGui::Button(allComponentNames[i], ImVec2(340.0f, 20.0f)))
					{
						selectedComponent = i;
						bool noDuplicates = true;
						// check to see if component already exists, no duplicate components are allowed
							
						for (unsigned int j = 0; j < componentNames.size(); j++)
							if (componentNames[j] == allComponentNames[selectedComponent])
								noDuplicates = false;

						if (noDuplicates)
						{
							std::string componentPopup = ComponentManager::ChooseComponentPopup(allComponentNames[selectedComponent]);
							if (componentPopup == "Rotatable")
							{
								currentGameObject->AddComponent<Rotatable>(currentGameObject);
							}
							else
							{
								componentPopup = "Add " + componentPopup;
								ImGui::OpenPopup(componentPopup.c_str());
							}							
						}
						else
							FLOW_CORE_INFO("This component already exists. No duplicates are allowed.");
																		
					}	



				ImGui::SetNextWindowBgAlpha(1.0f);
				if (ImGui::BeginPopup("Add Renderable"))
				{
					static int renderableType = 0;
					ImGui::Text("Renderable");
					ImGui::Separator();
					ImGui::RadioButton("From Model", &renderableType, 0);
					ImGui::SameLine();
					ImGui::RadioButton("From Shape", &renderableType, 1);
					ImGui::Separator();

					std::vector<std::shared_ptr<Shader>> shaders = ResourceManager::Get().GetAllShaders();
					static int currentShader = 0;
					std::vector<const char*> shaderNames;
					for (unsigned int i = 0; i < shaders.size(); i++)
						shaderNames.push_back(shaders[i]->m_Name.c_str());

					ImGui::PushItemWidth(200);
					ImGui::Combo("Shaders", &currentShader, &shaderNames[0], (int)shaderNames.size());

					if (renderableType == 0)
					{
						ImGui::SameLine();
						ShowHelpMarker("Should use the Models shader");
						std::vector<std::shared_ptr<Model>> models = ResourceManager::Get().GetAllModels();
						static int currentModel = 0;
						std::vector<const char*> modelNames;
						for (unsigned int i = 0; i < models.size(); i++)
							modelNames.push_back(models[i]->name.c_str());

						ImGui::PushItemWidth(200);
						ImGui::Combo("Models", &currentModel, &modelNames[0], (int)modelNames.size());							

						if (ImGui::Button("Add Renderable", ImVec2(320.0f, 20.0f)))
						{
							currentGameObject->AddComponent<Renderable>(currentGameObject, models[currentModel], shaders[currentShader]);
							ImGui::CloseCurrentPopup();
						}
					}
					else if (renderableType == 1)
					{
						static int shapeType = 0;
						ImGui::Text("Shape");
						ImGui::Separator();
						ImGui::RadioButton("Cube", &shapeType, 0);
						ImGui::SameLine();
						ImGui::RadioButton("Plane", &shapeType, 1);
						ImGui::Separator();

						std::vector<std::shared_ptr<Texture>> textures = ResourceManager::Get().GetAllTextures();
						static int currentDiffuseTexture = 0;
						static int currentSpecularTexture = 0;
						std::vector<const char*> textureNames;
						for (unsigned int i = 0; i < textures.size(); i++)
							textureNames.push_back(textures[i]->name.c_str());

						static int fragmentType = 0;
						ImGui::Separator();
						ImGui::RadioButton("Textured", &fragmentType, 0);
						ImGui::SameLine();
						ShowHelpMarker("Should use the Standard shader");
						ImGui::SameLine();
						ImGui::RadioButton("Colored", &fragmentType, 1);
						ImGui::SameLine();
						ShowHelpMarker("Should use the Colored shader");
						static ImVec4 color = ImColor();

						if (fragmentType == 0)
						{
							ImGui::Text("Textures");
							ImGui::Separator();
							ImGui::Combo("Diffuse", &currentDiffuseTexture, &textureNames[0], (int)textureNames.size());
							ImGui::Combo("Specular", &currentSpecularTexture, &textureNames[0], (int)textureNames.size());
						}
						else if (fragmentType == 1)
						{								
							ImGui::Text("Texture Color:");
							ImGui::ColorEdit3("##1", (float*)&color);
						}

						if (ImGui::Button("Add Renderable", ImVec2(320.0f, 20.0f)))
						{
							if (shapeType == 0 && fragmentType == 0)
							{
								currentGameObject->AddComponent<Renderable>(currentGameObject, 
									std::make_shared<Model>(std::make_shared<Cube>(textures[currentDiffuseTexture], textures[currentSpecularTexture])), shaders[currentShader]);
							}
							else if (shapeType == 0 && fragmentType == 1)
							{
								currentGameObject->AddComponent<Renderable>(currentGameObject,
									std::make_shared<Model>(std::make_shared<Cube>(color.x, color.y, color.z, color.w)), shaders[currentShader]);
							}
							else if (shapeType == 1 && fragmentType == 0)
							{
								currentGameObject->AddComponent<Renderable>(currentGameObject,
									std::make_shared<Model>(std::make_shared<Plane>(textures[currentDiffuseTexture], textures[currentSpecularTexture])), shaders[currentShader]);
							}
							else if (shapeType == 1 && fragmentType == 1)
							{
								currentGameObject->AddComponent<Renderable>(currentGameObject,
									std::make_shared<Model>(std::make_shared<Plane>(color.x, color.y, color.z, color.w)), shaders[currentShader]);
							}
							ImGui::CloseCurrentPopup();
						}
							
					}						

					ImGui::EndPopup();
				}

				if (ImGui::BeginPopup("Add FreeCamera"))
				{
					static bool isMainCamera;
					ImGui::Checkbox("Main Camera", &isMainCamera);

					ImGui::Text("Movement Speed");
					ImGui::SameLine(0, 71);
					ImGui::PushItemWidth(100);

					static float movementSpeed = 5.0f;
					ImGui::DragFloat("##4", &movementSpeed, 0.1f);

					ImGui::Text("Mouse Sensitivity");
					ImGui::SameLine(0, 50);
					ImGui::PushItemWidth(100);

					static float mouseSensitivity = 0.1f;
					ImGui::DragFloat("##5", &mouseSensitivity, 0.01f);

					ImGui::Text("Field of view");
					ImGui::SameLine(0, 78);
					ImGui::PushItemWidth(100);

					static float zoom = 45.0f;
					ImGui::DragFloat("##6", &zoom, 0.1f, 0.0f, 100.0f);

					ImGui::Text("Z-Near");
					ImGui::SameLine(0, 127);
					ImGui::PushItemWidth(100);

					static float zNear = 0.1f;
					ImGui::DragFloat("##7", &zNear, 0.1f, 0.0f, 100.0f);

					ImGui::Text("Z-Far");
					ImGui::SameLine(0, 134);
					ImGui::PushItemWidth(100);

					static float zFar = 100.0f;
					ImGui::DragFloat("##8", &zFar, 0.1f, 0.0f, 1000.0f);

					if (ImGui::Button("Add FreeCamera", ImVec2(320.0f, 20.0f)))
					{
						currentGameObject->AddComponent<FreeCamera>(currentGameObject, Application::Get().GetWindow());
						FreeCamera& camera = currentGameObject->GetComponent<FreeCamera>();
						camera.SetMovementSpeed(movementSpeed);
						camera.SetMouseSensitivity(mouseSensitivity);
						camera.SetZoom(zoom);
						camera.SetZNear(zNear);
						camera.SetZFar(zFar);
						camera.SetIsMainCamera(isMainCamera);
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				if (ImGui::BeginPopup("Add DirectionalLight"))
				{
					static float posX = 0.0f;
					static float posY = 0.0f;
					static float posZ = 0.0f;
					ImGui::Text("Direction");
					ImGui::SameLine();
					ImGui::PushItemWidth(66);
					ImGui::DragFloat("x##1", &posX, 0.1f);
					ImGui::SameLine();
					ImGui::DragFloat("y##1", &posY, 0.1f);
					ImGui::SameLine();
					ImGui::DragFloat("z##1", &posZ, 0.1f);
					ImGui::PopItemWidth();

					static float ambientR, ambientG, ambientB = 0.0f;

					ImGui::Text("Ambient");
					ImGui::SameLine(0, 20);
					ImGui::PushItemWidth(66);
					ImGui::DragFloat("r##8", &ambientR, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("g##8", &ambientG, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("b##8", &ambientB, 0.01f, 0.0f, 1.0f);
					ImGui::PopItemWidth();

					static float diffuseR, diffuseG, diffuseB = 0.0f;

					ImGui::Text("Diffuse");
					ImGui::SameLine(0, 20);
					ImGui::PushItemWidth(66);
					ImGui::DragFloat("r##9", &diffuseR, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("g##9", &diffuseG, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("b##9", &diffuseB, 0.01f, 0.0f, 1.0f);
					ImGui::PopItemWidth();

					static float specularR, specularG, specularB = 0.0f;

					ImGui::Text("Specular");
					ImGui::SameLine(0, 13);
					ImGui::PushItemWidth(66);
					ImGui::DragFloat("r##10", &specularR, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("g##10", &specularG, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("b##10", &specularB, 0.01f, 0.0f, 1.0f);
					ImGui::PopItemWidth();

					if (ImGui::Button("Add DirectionalLight", ImVec2(320.0f, 20.0f)))
					{
						currentGameObject->AddComponent<DirectionalLight>(currentGameObject, Vec3(posX, posY, posZ),
							Vec3(ambientR, ambientG, ambientB), Vec3(diffuseR, diffuseG, diffuseB), Vec3(specularR, specularG, specularB));
						// currentScene.AddDirectionalLight(currentGameObject->GetComponent<DirectionalLight>());
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				if (ImGui::BeginPopup("Add PointLight"))
				{
					static float ambientR, ambientG, ambientB = 0.0f;

					ImGui::Text("Ambient");
					ImGui::SameLine(0, 20);
					ImGui::PushItemWidth(66);
					ImGui::DragFloat("r##8", &ambientR, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("g##8", &ambientG, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("b##8", &ambientB, 0.01f, 0.0f, 1.0f);
					ImGui::PopItemWidth();

					static float diffuseR, diffuseG, diffuseB = 0.0f;

					ImGui::Text("Diffuse");
					ImGui::SameLine(0, 20);
					ImGui::PushItemWidth(66);
					ImGui::DragFloat("r##9", &diffuseR, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("g##9", &diffuseG, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("b##9", &diffuseB, 0.01f, 0.0f, 1.0f);
					ImGui::PopItemWidth();

					static float specularR, specularG, specularB = 0.0f;

					ImGui::Text("Specular");
					ImGui::SameLine(0, 13);
					ImGui::PushItemWidth(66);
					ImGui::DragFloat("r##10", &specularR, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("g##10", &specularG, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("b##10", &specularB, 0.01f, 0.0f, 1.0f);
					ImGui::PopItemWidth();

					static float constant, linear, exponent = 0.0f;

					ImGui::PushItemWidth(150);
					ImGui::DragFloat("Constant##15", &constant, 0.01f, 0.0f, 100.0f);
					ImGui::DragFloat("Linear##15", &linear, 0.01f, 0.0f, 100.0f);
					ImGui::DragFloat("Exponent##15", &exponent, 0.001f, 0.0f, 100.0f);
					ImGui::PopItemWidth();

					if (ImGui::Button("Add PointLight", ImVec2(320.0f, 20.0f)))
					{
						currentGameObject->AddComponent<PointLight>(currentGameObject, Vec3(ambientR, ambientG, ambientB), 
							Vec3(diffuseR, diffuseG, diffuseB), Vec3(specularR, specularG, specularB), Attenuation(constant, linear, exponent));
						currentScene.AddPointLight(&currentGameObject->GetComponent<PointLight>());
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				if (ImGui::BeginPopup("Add SpotLight"))
				{
					static float ambientR, ambientG, ambientB = 0.0f;

					ImGui::Text("Ambient");
					ImGui::SameLine(0, 20);
					ImGui::PushItemWidth(66);
					ImGui::DragFloat("r##8", &ambientR, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("g##8", &ambientG, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("b##8", &ambientB, 0.01f, 0.0f, 1.0f);
					ImGui::PopItemWidth();

					static float diffuseR, diffuseG, diffuseB = 0.0f;

					ImGui::Text("Diffuse");
					ImGui::SameLine(0, 20);
					ImGui::PushItemWidth(66);
					ImGui::DragFloat("r##9", &diffuseR, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("g##9", &diffuseG, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("b##9", &diffuseB, 0.01f, 0.0f, 1.0f);
					ImGui::PopItemWidth();

					static float specularR, specularG, specularB = 0.0f;

					ImGui::Text("Specular");
					ImGui::SameLine(0, 13);
					ImGui::PushItemWidth(66);
					ImGui::DragFloat("r##10", &specularR, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("g##10", &specularG, 0.01f, 0.0f, 1.0f);
					ImGui::SameLine();
					ImGui::DragFloat("b##10", &specularB, 0.01f, 0.0f, 1.0f);
					ImGui::PopItemWidth();

					static float cutoff, outerCutoff, constant, linear, exponent = 0.0f;

					ImGui::PushItemWidth(150);
					ImGui::DragFloat("cutoff##15", &cutoff, 0.1f, 0.0f, 360.0f);
					ImGui::DragFloat("outerCutoff##15", &outerCutoff, 0.1f, 0.0f, 360.0f);
					ImGui::DragFloat("Constant##15", &constant, 0.01f, 0.0f, 100.0f);
					ImGui::DragFloat("Linear##15", &linear, 0.01f, 0.0f, 100.0f);
					ImGui::DragFloat("Exponent##15", &exponent, 0.001f, 0.0f, 100.0f);
					ImGui::PopItemWidth();

					if (ImGui::Button("Add PointLight", ImVec2(320.0f, 20.0f)))
					{
						currentGameObject->AddComponent<SpotLight>(currentGameObject, Vec3(ambientR, ambientG, ambientB), Vec3(diffuseR, diffuseG, diffuseB), 
							Vec3(specularR, specularG, specularB), cutoff, outerCutoff, Attenuation(constant, linear, exponent));
						currentScene.AddSpotLight(&currentGameObject->GetComponent<SpotLight>());
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				if (ImGui::BeginPopup("Add ComponentToggler"))
				{
					static int componentID = -1;
					std::vector<const char*> chars;
					for (unsigned int i = 0; i < componentNames.size(); i++)
						chars.push_back(componentNames[i].c_str());

					ImGui::PushItemWidth(200);
					ImGui::Combo("Components", &componentID, &chars[0], (int)chars.size());
					ImGui::PopItemWidth();

					std::vector<std::tuple<Keycode, const char*>>& keyMap = Input::Get().GetKeyMap();
					static int selectedChar = -1;
					std::vector<const char*> keysChars;
					for (unsigned int i = 0; i < keyMap.size(); i++)
						keysChars.push_back(std::get<1>(keyMap[i]));

					ImGui::Combo("Key", &selectedChar, &keysChars[0], (int)keysChars.size());

					if (ImGui::Button("Add ComponentToggler", ImVec2(320.0f, 20.0f)))
					{
						currentGameObject->AddComponent<ComponentToggler>(currentGameObject);
						currentGameObject->GetComponent<ComponentToggler>().AddComponentToToggle(std::make_tuple(components[componentID].get(), std::get<0>(keyMap[selectedChar])), false);
						ImGui::CloseCurrentPopup();
					}	

					ImGui::EndPopup();
				}

				if (ImGui::BeginPopup("Add GameObjectToggler"))
				{
					static char nameBuffer[32] = "GameObject";
					ImGui::InputText("Name of GameObject", nameBuffer, IM_ARRAYSIZE(nameBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);						

					ImGui::PushItemWidth(200);

					std::vector<std::tuple<Keycode, const char*>>& keyMap = Input::Get().GetKeyMap();
					static int selectedChar = -1;
					std::vector<const char*> keysChars;
					for (unsigned int i = 0; i < keyMap.size(); i++)
						keysChars.push_back(std::get<1>(keyMap[i]));

					ImGui::Combo("Key", &selectedChar, &keysChars[0], (int)keysChars.size());

					if (ImGui::Button("Add GameObjectToggler", ImVec2(320.0f, 20.0f)))
					{
						GameObject* gameObjectToToggle = Application::Get().GetCurrentScene().FindGameObject(nameBuffer);
						if (gameObjectToToggle != nullptr)
						{
							currentGameObject->AddComponent<GameObjectToggler>(currentGameObject);
							currentGameObject->GetComponent<GameObjectToggler>().AddGameObjectToToggle(std::make_tuple(gameObjectToToggle, 
								nameBuffer, std::get<0>(keyMap[selectedChar])), false);
						}
						else
						{
							FLOW_CORE_INFO("Game Object not found");
						}
							
						ImGui::CloseCurrentPopup();
					}
						
					ImGui::EndPopup();
				}

				ImGui::EndPopup();
			}

			ImGui::Separator();

			bool gameObjectActive = currentGameObject->GetIsActive();
			if (ImGui::Checkbox("", &gameObjectActive))
				currentGameObject->SetActive(gameObjectActive);

			ImGui::SameLine(0, 20.0f);
			ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.8f, 1.0f), currentGameObject->GetName().c_str());

			std::string buttonName = "Delete ";
			buttonName.append(currentGameObject->GetName());
			if (ImGui::Button("Delete", ImVec2(340.0f, 20.0f)))
				ImGui::OpenPopup(buttonName.c_str());

			if (ImGui::BeginPopupModal(buttonName.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("This GameObject will be deleted.\n\n");
				ImGui::Separator();

				if (ImGui::Button("OK", ImVec2(120, 0)))
				{
					gameObjectSet = false;
						
					GameObject::Destroy(currentGameObject);
						
					currentGameObject = nullptr;
						
					ImGui::CloseCurrentPopup();
				}
				ImGui::SetItemDefaultFocus();
				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
				ImGui::EndPopup();
			}

			ImGui::Separator();

			if (gameObjectSet && currentGameObject != NULL)
			{
				TransformEditor transformEditor = TransformEditor();
				transformEditor.Draw(currentGameObject->GetTransform());
			}							
				
			for (unsigned int i = 0; i < components.size(); i++)
			{
				Component& component = *components[i];
				std::string componentName = component.GetName();

				if (ImGui::TreeNodeEx(componentName.c_str(), ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
				{
					bool componentActive = component.GetEnabled();
					if (ImGui::Checkbox("Enabled", &componentActive))
						component.SetEnabled(componentActive);
						
					ImGui::SameLine(0, 190);
					std::string buttonName = "Remove ";
					buttonName.append(componentName);
					if (ImGui::Button("Remove"))
						ImGui::OpenPopup(buttonName.c_str());

					if (ImGui::BeginPopupModal(buttonName.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text("This component will be removed.\n\n");
						ImGui::Separator();

						if (ImGui::Button("OK", ImVec2(120, 0)))
						{
							if (componentName == "FreeCamera")
							{
								currentGameObject->GetComponent<FreeCamera>().SetIsMainCamera(false);
								currentGameObject->RemoveComponent(componentName);
							}
							else if (componentName == "DirectionalLight")
							{
								FLOW_CORE_INFO("should not be removed at the moment");
							}
							else if (componentName == "PointLight")
							{
								currentScene.RemovePointLight(&currentGameObject->GetComponent<PointLight>());
								currentGameObject->RemoveComponent(componentName);
							}
							else if (componentName == "SpotLight")
							{
								currentScene.RemoveSpotLight(&currentGameObject->GetComponent<SpotLight>());
								currentGameObject->RemoveComponent(componentName);
							}
							else
							{
								currentGameObject->RemoveComponent(componentName);
							}

							ImGui::CloseCurrentPopup();
						}
						ImGui::SetItemDefaultFocus();
						ImGui::SameLine();
						if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
						ImGui::EndPopup();
					}

					ComponentManager::ShowComponentEditor(componentName, componentNames, components[i].get(), components);

					ImGui::TreePop();
				}

				ImGui::Separator();
			}				
		}


		ImGui::End();
	}
}

