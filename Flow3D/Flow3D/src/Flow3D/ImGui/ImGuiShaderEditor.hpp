#pragma once

#include <imgui/imgui.h>

#include "ImGuiHelper.hpp"
#include "Flow3D/ResourceManager.hpp"

namespace Flow {

	struct ShaderEditor
	{

		ShaderEditor() {}

		void Draw()
		{
			if (ImGui::Button("Add Shader", ImVec2(960.0f, 20.0f)))
			{
				ImGui::OpenPopup("Adding Shader");
			}

			if (ImGui::BeginPopupModal("Adding Shader", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				static char nameBuffer[64] = "enterNameHere";
				ImGui::InputText("Name", nameBuffer, IM_ARRAYSIZE(nameBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);

				static char vertexPath[128] = "enterVertexPathHere";
				ImGui::InputText("Vertex Shader Path", vertexPath, IM_ARRAYSIZE(vertexPath), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);
				ImGui::SameLine();
				ShowHelpMarker("Path relative to Sandbox directory");

				static char fragmentPath[128] = "enterFragmentPathHere";
				ImGui::InputText("Fragment Shader Path", fragmentPath, IM_ARRAYSIZE(fragmentPath), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);
				ImGui::SameLine();
				ShowHelpMarker("Path relative to Sandbox directory");

				if (ImGui::Button("Create", ImVec2(120, 0)))
				{
					ResourceManager::Get().AddShader(std::make_shared<Shader>(vertexPath, fragmentPath, nameBuffer));
					ImGui::CloseCurrentPopup();
				}
				ImGui::SetItemDefaultFocus();
				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
				ImGui::EndPopup();
			}
			ImGui::Separator();

			std::vector<std::shared_ptr<Shader>> shaders = ResourceManager::Get().GetAllShaders();
			ImGui::Columns(3);
			ImGui::SetColumnWidth(0, 320.0f);
			ImGui::SetColumnWidth(1, 320.0f);
			ImGui::SetColumnWidth(2, 320.0f);

			ImGui::Text("Name");
			ImGui::NextColumn();
			ImGui::Text("ID");
			ImGui::NextColumn();
			ImGui::Text("Action");
			ImGui::NextColumn();

			ImGui::Separator();
			ImGui::Separator();

			for (unsigned int i = 0; i < shaders.size(); i++)
			{
				ImGui::Text(shaders[i]->m_Name.c_str());
				ImGui::NextColumn();
				std::string id = std::to_string(shaders[i]->m_ID);
				ImGui::Text(id.c_str());
				ImGui::NextColumn();
				std::string buttonName = "Delete ";
				buttonName.append(shaders[i]->m_Name);
				if (ImGui::Button(buttonName.c_str()))
					ImGui::OpenPopup(buttonName.c_str());

				if (ImGui::BeginPopupModal(buttonName.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("This shader will be deleted.\nPlease make sure no GameObject uses it.\n\n");
					ImGui::Separator();

					if (ImGui::Button("OK", ImVec2(120, 0)))
					{
						ResourceManager::Get().RemoveShader(i);
						ImGui::CloseCurrentPopup();
					}
					ImGui::SetItemDefaultFocus();
					ImGui::SameLine();
					if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
					ImGui::EndPopup();
				}

				ImGui::NextColumn();
				ImGui::Separator();
			}

			ImGui::Columns(1);
		}
	};
}
