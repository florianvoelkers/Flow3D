#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/Renderable.hpp"
#include "Flow3D/ResourceManager.hpp"
#include "ImGuiHelper.hpp"

namespace Flow {

	struct RenderableEditor
	{

		RenderableEditor() {}

		void Draw(Renderable* renderable)
		{
			if (renderable != nullptr)
			{
				Model& model = renderable->GetModel();
				Shader& shader = renderable->GetShader();

				bool blendingActive = renderable->GetBlending();
				if (ImGui::Checkbox("Blending", &blendingActive))
					renderable->SetBlending(blendingActive);

				std::vector<std::shared_ptr<Shader>> shaders = ResourceManager::Get().GetAllShaders();

				static int currentShader = -1;
				bool shaderFound = false;
				std::vector<const char*> shaderNames;
				for (unsigned int i = 0; i < shaders.size(); i++)
				{
					if (shader.m_Name == shaders[i]->m_Name)
					{
						shaderFound = true;
						currentShader = i;
					}

					if (!shaderFound)
						currentShader = -1;

					shaderNames.push_back(shaders[i]->m_Name.c_str());
				}

				ImGui::PushItemWidth(200);

				if (ImGui::Combo("Shader", &currentShader, &shaderNames[0], (int)shaderNames.size()))
				{
					//renderable->SetShader(shaders[currentShader]);
				}
				ImGui::SameLine();
				ShowHelpMarker("Currently shaders should not be swapped, because that causes problems!");

				ImGui::PopItemWidth();

				if (model.filepath.empty())
				{
					std::vector<std::shared_ptr<Texture>> textures = ResourceManager::Get().GetAllTextures();

					std::shared_ptr<Cube> cubePtr = model.GetCube();
					std::shared_ptr<Plane> planePtr = model.GetPlane();

					if (cubePtr != nullptr)
					{
						bool wireframeMode = cubePtr->GetWireframeMode();
						if (ImGui::Checkbox("Wireframe Mode", &wireframeMode))
							cubePtr->SetWireframeMode(wireframeMode);

						bool hasTexture = cubePtr->GetIsTexture();
						if (ImGui::Checkbox("IsTextured", &hasTexture))
						{
							cubePtr->SetIsTextured(hasTexture);
							if (hasTexture)
							{
								if (!cubePtr->GetTextureInitialized())
								{
									cubePtr->SetDiffuseTexture(textures[0]);
									cubePtr->SetSpecularTexture(textures[0]);
									cubePtr->SetTextureInitialized(true);
								}

								renderable->SetShader(shaders[0]);
							}
							else
								renderable->SetShader(shaders[1]);
						}

						if (hasTexture)
						{
							if (ImGui::TreeNodeEx("Textures", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
							{
								Texture& diffuseTexture = cubePtr->GetDiffuseTexture();
								Texture& specularTexture = cubePtr->GetSpecularTexture();

								static int currentDiffuseName = -1;
								bool diffuseFound = false;
								static int currentSpecularName = -1;
								bool specularFound = false;
								std::vector<const char*> textureNames;
								for (unsigned int i = 0; i < textures.size(); i++)
								{
									if (diffuseTexture.name == textures[i]->name)
									{
										diffuseFound = true;
										currentDiffuseName = i;
									}

									if (!diffuseFound)
										currentDiffuseName = -1;

									if (specularTexture.name == textures[i]->name)
									{
										specularFound = true;
										currentSpecularName = i;
									}

									if (!specularFound)
										currentSpecularName = -1;

									textureNames.push_back(textures[i]->name.c_str());
								}

								ImGui::PushItemWidth(200);

								if (ImGui::Combo("Diffuse", &currentDiffuseName, &textureNames[0], (int)textureNames.size()))
									cubePtr->SetDiffuseTexture(textures[currentDiffuseName]);

								if (ImGui::Combo("Specular", &currentSpecularName, &textureNames[0], (int)textureNames.size()))
									cubePtr->SetSpecularTexture(textures[currentSpecularName]);

								ImGui::PopItemWidth();
								ImGui::TreePop();
							}

						}
						else
						{
							Color cubeColor = cubePtr->GetColor();
							static ImVec4 color = ImColor(cubeColor.r, cubeColor.g, cubeColor.b, cubeColor.a);
							ImGui::Text("Texture Color:");
							if (ImGui::ColorEdit3("##1", (float*)&color))
								cubePtr->SetColor(Color(color.x, color.y, color.z, color.w));
						}
					}
					else if (planePtr != nullptr)
					{
						bool wireframeMode = planePtr->GetWireframeMode();
						if (ImGui::Checkbox("Wireframe Mode", &wireframeMode))
							planePtr->SetWireframeMode(wireframeMode);

						bool hasTexture = planePtr->GetIsTexture();
						if (ImGui::Checkbox("IsTextured", &hasTexture))
						{
							planePtr->SetIsTextured(hasTexture);
							if (hasTexture)
							{
								if (!planePtr->GetTextureInitialized())
								{
									planePtr->SetDiffuseTexture(textures[0]);
									planePtr->SetSpecularTexture(textures[0]);
									planePtr->SetTextureInitialized(true);
								}

								renderable->SetShader(shaders[0]);
							}
							else
								renderable->SetShader(shaders[1]);
						}

						if (hasTexture)
						{
							if (ImGui::TreeNodeEx("Textures", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
							{
								Texture& diffuseTexture = planePtr->GetDiffuseTexture();
								Texture& specularTexture = planePtr->GetSpecularTexture();

								static int currentDiffuseName = -1;
								bool diffuseFound = false;
								static int currentSpecularName = -1;
								bool specularFound = false;
								std::vector<const char*> textureNames;
								for (unsigned int i = 0; i < textures.size(); i++)
								{
									if (diffuseTexture.name == textures[i]->name)
									{
										diffuseFound = true;
										currentDiffuseName = i;
									}

									if (!diffuseFound)
										currentDiffuseName = -1;

									if (specularTexture.name == textures[i]->name)
									{
										specularFound = true;
										currentSpecularName = i;
									}

									if (!specularFound)
										currentSpecularName = -1;

									textureNames.push_back(textures[i]->name.c_str());
								}

								ImGui::PushItemWidth(200);

								if (ImGui::Combo("Diffuse", &currentDiffuseName, &textureNames[0], (int)textureNames.size()))
									planePtr->SetDiffuseTexture(textures[currentDiffuseName]);

								if (ImGui::Combo("Specular", &currentSpecularName, &textureNames[0], (int)textureNames.size()))
									planePtr->SetSpecularTexture(textures[currentSpecularName]);

								ImGui::PopItemWidth();

								ImGui::TreePop();
							}

						}
						else
						{
							Color planeColor = planePtr->GetColor();
							static ImVec4 color = ImColor(planeColor.r, planeColor.g, planeColor.b, planeColor.a);
							ImGui::Text("Texture Color:");
							if (ImGui::ColorEdit3("##1", (float*)&color))
								planePtr->SetColor(Color(color.x, color.y, color.z, color.w));
						}
					}
				}
				else
				{
					std::vector<std::shared_ptr<Model>> models = ResourceManager::Get().GetAllModels();
					static int currentModel = -1;
					bool modelFound = false;
					std::vector<const char*> modelNames;
					for (unsigned int i = 0; i < models.size(); i++)
					{
						if (model.name == models[i]->name)
						{
							modelFound = true;
							currentModel = i;
						}

						if (!modelFound)
							currentModel = -1;

						modelNames.push_back(models[i]->name.c_str());
					}

					ImGui::PushItemWidth(200);

					if (ImGui::Combo("Models", &currentModel, &modelNames[0], (int)modelNames.size()))
					{
						renderable->SetModel(models[currentModel]);
					}
				}
			}
			
		}
	};
}