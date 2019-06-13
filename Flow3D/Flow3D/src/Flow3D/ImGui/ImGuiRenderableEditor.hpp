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
					if (cubePtr->GetIsTexture())
					{
						if (ImGui::TreeNodeEx("Textures", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen))
						{
							Texture& diffuseTexture = cubePtr->GetDiffuseTexture();
							Texture& specularTexture = cubePtr->GetSpecularTexture();

							ImGui::PushItemWidth(320);
							ImGui::Text("Diffuse:");
							static char diffuseBuffer[128] = "DiffuseTexture";
							strcpy(diffuseBuffer, diffuseTexture.path.c_str());
							if (ImGui::InputText("", diffuseBuffer, IM_ARRAYSIZE(diffuseBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
							{

							}

							ImGui::Text("Specular:");
							static char specularBuffer[128] = "SpecularTexture";
							strcpy(specularBuffer, specularTexture.path.c_str());
							if (ImGui::InputText("", specularBuffer, IM_ARRAYSIZE(specularBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue))
							{

							}
							ImGui::PopItemWidth();

							ImGui::TreePop();
						}
						
					}
					else
					{

					}
				}
				else if (planePtr != nullptr)
				{
					FLOW_CORE_INFO("this is a plane");
				}
			}
			else
			{
				FLOW_CORE_INFO("this is a loaded model");
			}
		}
	};
}