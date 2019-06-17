#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/Renderable.hpp"

namespace Flow {

	struct RenderableEditor
	{

		RenderableEditor() {}

		void Draw(Renderable* renderable)
		{
			Model& model = renderable->GetModel();
			Shader& shader = renderable->GetShader();

			std::vector<std::shared_ptr<Texture>> textures = Application::Get().GetAllTextures();

			if (model.filepath.empty())
			{
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
								std::shared_ptr<Texture> diffuse = std::make_shared<Texture>("resources/textures/container2.png", "diffuse", true);
								std::shared_ptr<Texture> specular = std::make_shared<Texture>("resources/textures/container2_specular.jpg", "specular", true);
								cubePtr->SetDiffuseTexture(diffuse);
								cubePtr->SetSpecularTexture(specular);
								cubePtr->SetTextureInitialized(true);
							}
							renderable->SetShader(std::make_shared<Shader>("resources/shader/Standard.vert", "resources/shader/Standard.frag"));
						}							
						else
							renderable->SetShader(std::make_shared<Shader>("resources/shader/Basic3D.vert", "resources/shader/Colored.frag"));
					}						

					if (hasTexture)
					{
						if (ImGui::TreeNodeEx("Textures", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
						{
							Texture& diffuseTexture = cubePtr->GetDiffuseTexture();
							Texture& specularTexture = cubePtr->GetSpecularTexture();

							static int currentDiffuseName = -1; 
							static int currentSpecularName = -1;
							std::vector<const char*> textureNames;
							for (unsigned int i = 0; i < textures.size(); i++)
							{
								if (diffuseTexture.name == textures[i]->name)
									currentDiffuseName = i;

								if (specularTexture.name == textures[i]->name)
									currentSpecularName = i;

								textureNames.push_back(textures[i]->name.c_str());
							}

							ImGui::PushItemWidth(200);
							
							if (ImGui::Combo("Diffuse", &currentDiffuseName, &textureNames[0], textureNames.size()))
								cubePtr->SetDiffuseTexture(textures[currentDiffuseName]);

							if (ImGui::Combo("Specular", &currentSpecularName, &textureNames[0], textureNames.size()))
								cubePtr->SetSpecularTexture(textures[currentSpecularName]);

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
					if (ImGui::Checkbox("IsTexured", &hasTexture))
					{
						planePtr->SetIsTextured(hasTexture);
						if (hasTexture)
						{
							if (!planePtr->GetTextureInitialized())
							{
								std::shared_ptr<Texture> diffuse = std::make_shared<Texture>("resources/textures/container2.png", "diffuse", true);
								std::shared_ptr<Texture> specular = std::make_shared<Texture>("resources/textures/container2_specular.jpg", "specular", true);
								planePtr->SetDiffuseTexture(diffuse);
								planePtr->SetSpecularTexture(specular);
								planePtr->SetTextureInitialized(true);
							}
							renderable->SetShader(std::make_shared<Shader>("resources/shader/Standard.vert", "resources/shader/Standard.frag"));
						}
						else
							renderable->SetShader(std::make_shared<Shader>("resources/shader/Basic3D.vert", "resources/shader/Colored.frag"));
					}

					if (hasTexture)
					{
						if (ImGui::TreeNodeEx("Textures", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
						{
							Texture& diffuseTexture = planePtr->GetDiffuseTexture();
							Texture& specularTexture = planePtr->GetSpecularTexture();

							ImGui::PushItemWidth(320);
							ImGui::Text("Diffuse:");
							static char diffuseBuffer[128] = "DiffuseTexture";
							strcpy(diffuseBuffer, diffuseTexture.path.c_str());
							if (ImGui::InputText("Diffuse##hidelabel", diffuseBuffer, IM_ARRAYSIZE(diffuseBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
							{
								std::shared_ptr<Texture> texture = std::make_shared<Texture>(diffuseBuffer, "diffuse", true);
								if (texture->textureLoaded)
									planePtr->SetDiffuseTexture(texture);
								else
									FLOW_CORE_ERROR("texture not loaded");
							}

							ImGui::Text("Specular:");
							static char specularBuffer[128] = "SpecularTexture";
							strcpy(specularBuffer, specularTexture.path.c_str());
							if (ImGui::InputText("Specular##hidelabel", specularBuffer, IM_ARRAYSIZE(specularBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
							{
								std::shared_ptr<Texture> texture = std::make_shared<Texture>(specularBuffer, "specular", true);
								if (texture->textureLoaded)
									planePtr->SetSpecularTexture(texture);
								else
									FLOW_CORE_ERROR("texture not loaded");
							}
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
				
			}
		}
	};
}