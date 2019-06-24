#pragma once

#include <imgui/imgui.h>

#include "ImGuiHelper.hpp"
#include "Flow3D/ResourceManager.hpp"

struct ModelsEditor
{

	ModelsEditor() {}

	void Draw()
	{
		if (ImGui::Button("Add Models", ImVec2(960.0f, 20.0f)))
		{
			ImGui::OpenPopup("Adding Models");
		}

		if (ImGui::BeginPopupModal("Adding Models", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			static char pathBuffer[128] = "enterPathHere";
			ImGui::InputText("Path", pathBuffer, IM_ARRAYSIZE(pathBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);
			ImGui::SameLine();
			ShowHelpMarker("Path relative to Sandbox directory");

			if (ImGui::Button("Create", ImVec2(120, 0)))
			{
				ResourceManager::Get().AddModel(std::make_shared<Model>(pathBuffer));
				ImGui::CloseCurrentPopup();
			}
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::EndPopup();
		}
		ImGui::Separator();

		std::vector<std::shared_ptr<Model>> models = ResourceManager::Get().GetAllModels();
		ImGui::Columns(5);
		ImGui::SetColumnWidth(0, 200.0f);
		ImGui::SetColumnWidth(1, 460.0f);
		ImGui::SetColumnWidth(2, 100.0f);
		ImGui::SetColumnWidth(3, 100.0f);
		ImGui::SetColumnWidth(4, 100.0f);

		ImGui::Text("Name");
		ImGui::NextColumn();
		ImGui::Text("Path");
		ImGui::NextColumn();
		ImGui::Text("Mesh count");
		ImGui::NextColumn();
		ImGui::Text("Texture count");
		ImGui::NextColumn();
		ImGui::Text("Action");
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::Separator();

		for (unsigned int i = 0; i < models.size(); i++)
		{
			ImGui::Text(models[i]->name.c_str());
			ImGui::NextColumn();
			ImGui::Text(models[i]->filepath.c_str());
			ImGui::NextColumn();
			std::string meshCount = std::to_string(models[i]->meshes.size());
			ImGui::Text(meshCount.c_str());
			ImGui::NextColumn();
			std::string textureCount = std::to_string(models[i]->textures_loaded.size());
			ImGui::Text(textureCount.c_str());
			ImGui::NextColumn();
			std::string buttonName = "Delete ";
			buttonName.append(models[i]->name);
			if (ImGui::Button(buttonName.c_str()))
				ImGui::OpenPopup(buttonName.c_str());

			if (ImGui::BeginPopupModal(buttonName.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("This model will be deleted.\nPlease make sure no GameObject uses it.\n\n");
				ImGui::Separator();

				if (ImGui::Button("OK", ImVec2(120, 0)))
				{
					ResourceManager::Get().RemoveModel(i);
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

