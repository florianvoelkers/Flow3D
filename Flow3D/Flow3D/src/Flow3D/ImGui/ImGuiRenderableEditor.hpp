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

			if (model.filepath.empty())
			{
				std::shared_ptr<Cube> cubePtr = model.GetCube();
				std::shared_ptr<Plane> planePtr = model.GetPlane();
				if (cubePtr != nullptr)
				{
					bool hasTexture = cubePtr->GetIsTexture();
					if (ImGui::Checkbox("IsTexured", &hasTexture))
					{
						cubePtr->SetIsTextured(hasTexture);
						if (hasTexture)
						{
							if (!cubePtr->GetTextureInitialized())
							{
								Texture diffuse = Texture("resources/textures/container2.png", "diffuse", true);
								Texture specular = Texture("resources/textures/container2_specular.jpg", "specular", true);
								cubePtr->SetDiffuseTexture(diffuse);
								cubePtr->SetSpecularTexture(specular);
								cubePtr->SetTextureInitialized(true);
							}
							renderable->SetShader(Shader("resources/shader/Standard.vert", "resources/shader/Standard.frag"));
						}							
						else
							renderable->SetShader(Shader("resources/shader/Basic3D.vert", "resources/shader/Colored.frag"));						
					}						

					if (hasTexture)
					{
						if (ImGui::TreeNodeEx("Textures", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
						{
							Texture& diffuseTexture = cubePtr->GetDiffuseTexture();
							Texture& specularTexture = cubePtr->GetSpecularTexture();

							ImGui::PushItemWidth(320);
							ImGui::Text("Diffuse:");
							static char diffuseBuffer[128] = "DiffuseTexture";
							strcpy(diffuseBuffer, diffuseTexture.path.c_str());
							if (ImGui::InputText("Diffuse##hidelabel", diffuseBuffer, IM_ARRAYSIZE(diffuseBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
							{
								Texture texture = Texture(diffuseBuffer, "diffuse", true);
								if (texture.textureLoaded)
									cubePtr->SetDiffuseTexture(texture);
								else
									FLOW_CORE_ERROR("texture not loaded");
							}							

							ImGui::Text("Specular:");
							static char specularBuffer[128] = "SpecularTexture";
							strcpy(specularBuffer, specularTexture.path.c_str());
							if (ImGui::InputText("Specular##hidelabel", specularBuffer, IM_ARRAYSIZE(specularBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
							{
								Texture texture = Texture(specularBuffer, "specular", true);
								if (texture.textureLoaded)
									cubePtr->SetSpecularTexture(texture);
								else
									FLOW_CORE_ERROR("texture not loaded");
							}
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
							Texture texture = Texture(diffuseBuffer, "diffuse", true);
							if (texture.textureLoaded)
								planePtr->SetDiffuseTexture(texture);
							else
								FLOW_CORE_ERROR("texture not loaded");
						}

						ImGui::Text("Specular:");
						static char specularBuffer[128] = "SpecularTexture";
						strcpy(specularBuffer, specularTexture.path.c_str());
						if (ImGui::InputText("Specular##hidelabel", specularBuffer, IM_ARRAYSIZE(specularBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
						{
							Texture texture = Texture(specularBuffer, "specular", true);
							if (texture.textureLoaded)
								planePtr->SetSpecularTexture(texture);
							else
								FLOW_CORE_ERROR("texture not loaded");
						}
						ImGui::PopItemWidth();

						ImGui::TreePop();
					}
				}
			}
			else
			{
				FLOW_CORE_INFO("this is a loaded model");
			}
		}
	};
}