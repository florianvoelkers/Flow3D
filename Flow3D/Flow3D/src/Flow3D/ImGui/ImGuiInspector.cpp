#include "ImGuiInspector.hpp"
#include "ImGuiTransformEditor.hpp"
#include "Flow3D/Components/FreeCamera.hpp"
#include "ImGuiFreeCameraEditor.hpp"
#include "Flow3D/Components/GameObjectToggler.hpp"
#include "ImGuiGameObjectTogglerEditor.hpp"
#include "Flow3D/Components/ComponentToggler.hpp"
#include "ImGuiComponentTogglerEditor.hpp"
#include "Flow3D/Components/Lighting.hpp"
#include "ImGuiDirectionalLightEditor.hpp"
#include "ImGuiPointLightEditor.hpp"
#include "ImGuiSpotLightEditor.hpp"
#include "Flow3D/Components/Renderable.hpp"
#include "ImGuiRenderableEditor.hpp"
#include "Flow3D/Components/Rotatable.hpp"
#include "Flow3D/Math.hpp"
#include "Flow3D/Application.hpp"

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
				if (ImGui::Button("Add Component", ImVec2(360.0f, 20.0f)))
					ImGui::OpenPopup("select");

				ImGui::SameLine();
				if (ImGui::BeginPopup("select"))
				{
					std::vector<const char*> componentNames = Application::Get().GetAllComponentNames();
					ImGui::Text("ComponentTypes");
					ImGui::Separator();
					int selectedComponent = -1;
					for (int i = 0; i < componentNames.size(); i++)
						if (ImGui::Button(componentNames[i], ImVec2(340.0f, 20.0f)))
						{
							selectedComponent = i;
							if (componentNames[selectedComponent] == "Rotatable")
							{
								currentGameObject->AddComponent<Rotatable>(*currentGameObject);
							}
							else if (componentNames[selectedComponent] == "FreeCamera")
							{
								FLOW_CORE_INFO("should not be added at the moment");
							}
							else if (componentNames[selectedComponent] == "Renderable")
							{
								
								ImGui::OpenPopup("AddRenderable");
							}
							else if (componentNames[selectedComponent] == "DirectionalLight")
							{

							}
							else if (componentNames[selectedComponent] == "PointLight")
							{

							}
							else if (componentNames[selectedComponent] == "SpotLight")
							{

							}
							else if (componentNames[selectedComponent] == "ComponentToggler")
							{

							}
							else if (componentNames[selectedComponent] == "GameObjectToggler")
							{

							}																			
						}	

					ImGui::SetNextWindowBgAlpha(1.0f);
					if (ImGui::BeginPopup("AddRenderable"))
					{
						static int renderableType = 0;
						ImGui::Text("Renderable");
						ImGui::Separator();
						ImGui::RadioButton("From Model", &renderableType, 0);
						ImGui::SameLine();
						ImGui::RadioButton("From Shape", &renderableType, 1);
						ImGui::Separator();

						std::vector<std::shared_ptr<Shader>> shaders = Application::Get().GetAllShaders();
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
							std::vector<std::shared_ptr<Model>> models = Application::Get().GetAllModels();
							static int currentModel = 0;
							std::vector<const char*> modelNames;
							for (unsigned int i = 0; i < models.size(); i++)
								modelNames.push_back(models[i]->name.c_str());

							ImGui::PushItemWidth(200);
							ImGui::Combo("Models", &currentModel, &modelNames[0], (int)modelNames.size());							

							if (ImGui::Button("Add Renderable", ImVec2(320.0f, 20.0f)))
							{
								currentGameObject->AddComponent<Renderable>(*currentGameObject, models[currentModel], shaders[currentShader]);
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

							std::vector<std::shared_ptr<Texture>> textures = Application::Get().GetAllTextures();
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
									currentGameObject->AddComponent<Renderable>(*currentGameObject, 
										std::make_shared<Model>(std::make_shared<Cube>(textures[currentDiffuseTexture], textures[currentSpecularTexture])), shaders[currentShader]);
								}
								else if (shapeType == 0 && fragmentType == 1)
								{
									currentGameObject->AddComponent<Renderable>(*currentGameObject,
										std::make_shared<Model>(std::make_shared<Cube>(color.x, color.y, color.z, color.w)), shaders[currentShader]);
								}
								else if (shapeType == 1 && fragmentType == 0)
								{
									currentGameObject->AddComponent<Renderable>(*currentGameObject,
										std::make_shared<Model>(std::make_shared<Plane>(textures[currentDiffuseTexture], textures[currentSpecularTexture])), shaders[currentShader]);
								}
								else if (shapeType == 1 && fragmentType == 1)
								{
									currentGameObject->AddComponent<Renderable>(*currentGameObject,
										std::make_shared<Model>(std::make_shared<Plane>(color.x, color.y, color.z, color.w)), shaders[currentShader]);
								}
								ImGui::CloseCurrentPopup();
							}
							
						}

						

						ImGui::EndPopup();
					}

					ImGui::EndPopup();
				}

				

				bool gameObjectActive = currentGameObject->GetIsActive();
				if (ImGui::Checkbox("", &gameObjectActive))
					currentGameObject->SetActive(gameObjectActive);

				ImGui::SameLine(0, 20.0f);
				ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.8f, 1.0f), currentGameObject->GetName().c_str());

				ImGui::Separator();
				ImGui::Separator();

				TransformEditor transformEditor = TransformEditor();
				transformEditor.Draw(currentGameObject->GetTransform());
				

				const std::vector<std::unique_ptr<Component>>& components = currentGameObject->GetComponents();
				std::vector<std::string> componentNames;
				for (unsigned int i = 0; i < components.size(); i++)
				{
					Component& component = *components[i];
					std::string componentName = component.GetName();
					componentNames.push_back(componentName);
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

						if (componentName == "FreeCamera")
						{
							FreeCameraEditor editor = FreeCameraEditor();
							editor.Draw(dynamic_cast<FreeCamera*>(components[i].get()));
						}
						else if (componentName == "GameObjectToggler")
						{
							GameObjectTogglerEditor editor = GameObjectTogglerEditor();
							editor.Draw(dynamic_cast<GameObjectToggler*>(components[i].get()));
						}
						else if (componentName == "ComponentToggler")
						{
							ComponentTogglerEditor editor = ComponentTogglerEditor();
							editor.Draw(dynamic_cast<ComponentToggler*>(components[i].get()), components, componentNames);
						}
						else if (componentName == "DirectionalLight")
						{
							DirectionalLightEditor editor = DirectionalLightEditor();
							editor.Draw(dynamic_cast<DirectionalLight*>(components[i].get()));		
						}
						else if (component.GetName() == "PointLight")
						{
							PointLightEditor editor = PointLightEditor();
							editor.Draw(dynamic_cast<PointLight*>(components[i].get()));							
						}
						else if (component.GetName() == "SpotLight")
						{
							SpotLightEditor editor = SpotLightEditor();
							editor.Draw(dynamic_cast<SpotLight*>(components[i].get()));							
						}
						else if (component.GetName() == "Renderable")
						{
							RenderableEditor editor = RenderableEditor();
							editor.Draw(dynamic_cast<Renderable*>(components[i].get()));
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
