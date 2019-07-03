#pragma once

#include <imgui/imgui.h>

#include "ImGuiHelper.hpp"
#include "Flow3D/ResourceManager.hpp"

struct SkyboxEditor
{

	SkyboxEditor() {}

	void Draw()
	{
		if (ImGui::Button("Add Skybox", ImVec2(960.0f, 20.0f)))
		{
			ImGui::OpenPopup("Adding Skybox");
		}

		if (ImGui::BeginPopupModal("Adding Skybox", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			static char nameBuffer[64] = "enterNameHere";
			ImGui::InputText("Name", nameBuffer, IM_ARRAYSIZE(nameBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);

			static char directory[128] = "enterDirectoryPathHere";
			ImGui::InputText("Path to directory", directory, IM_ARRAYSIZE(directory), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);
			ImGui::SameLine();
			ShowHelpMarker("Path relative to Sandbox directory");

			static char filetype[24] = "enterFiletypeHere";
			ImGui::InputText("Filetype", filetype, IM_ARRAYSIZE(filetype), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);
			ImGui::SameLine();
			ShowHelpMarker("Filetype of the textures");

			if (ImGui::Button("Create", ImVec2(120, 0)))
			{
				ResourceManager::Get().AddSkybox(std::make_shared<Skybox>(directory, filetype, nameBuffer, false));
				ImGui::CloseCurrentPopup();
			}
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::EndPopup();
		}
		ImGui::Separator();

		std::vector<std::shared_ptr<Skybox>> skyboxes = ResourceManager::Get().GetAllSkyboxes();
		ImGui::Columns(5);
		ImGui::SetColumnWidth(0, 200.0f);
		ImGui::SetColumnWidth(1, 400.0f);
		ImGui::SetColumnWidth(2, 100.0f);
		ImGui::SetColumnWidth(3, 80.0f);
		ImGui::SetColumnWidth(4, 180.0f);

		ImGui::Text("Name");
		ImGui::NextColumn();
		ImGui::Text("Directory");
		ImGui::NextColumn();
		ImGui::Text("Filetype");
		ImGui::NextColumn();
		ImGui::Text("Shown");
		ImGui::NextColumn();
		ImGui::Text("Action");
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::Separator();

		for (unsigned int i = 0; i < skyboxes.size(); i++)
		{
			ImGui::Text(skyboxes[i]->GetName().c_str());
			ImGui::NextColumn();
			ImGui::Text(skyboxes[i]->GetDirectory().c_str());
			ImGui::NextColumn();
			ImGui::Text(skyboxes[i]->GetFiletype().c_str());
			ImGui::NextColumn();
			std::string shown = std::to_string(skyboxes[i]->IsShown());
			ImGui::Text(shown.c_str());
			ImGui::NextColumn();

			std::string buttonName = "Delete ";
			buttonName.append(skyboxes[i]->GetName());
			if (ImGui::Button(buttonName.c_str()))
				ImGui::OpenPopup(buttonName.c_str());

			if (ImGui::BeginPopupModal(buttonName.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("This skybox will be deleted.\n");
				ImGui::Separator();

				if (ImGui::Button("OK", ImVec2(120, 0)))
				{
					ResourceManager::Get().RemoveSkybox(i);
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

