#pragma once

#include <imgui/imgui.h>
#include "ImGuiHelper.hpp"

#include "Flow3D/ResourceManager.hpp"

struct TextureEditor
{

	TextureEditor() {}

	void Draw()
	{
		if (ImGui::Button("Add Texture", ImVec2(960.0f, 20.0f)))
		{
			ImGui::OpenPopup("Adding Texture");
		}

		if (ImGui::BeginPopupModal("Adding Texture", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			static char pathBuffer[128] = "enterPathHere";
			ImGui::InputText("Path", pathBuffer, IM_ARRAYSIZE(pathBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);
			ImGui::SameLine();
			ShowHelpMarker("Path relative to Sandbox directory");

			static char typeBuffer[32] = "enterTypeHere";
			ImGui::InputText("Type", typeBuffer, IM_ARRAYSIZE(typeBuffer), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);
			ImGui::SameLine();
			ShowHelpMarker("Possible types: Diffuse or Specular");

			static bool flip = false;
			ImGui::Checkbox("Flip texture", &flip);

			if (ImGui::Button("Create", ImVec2(120, 0)))
			{
				ResourceManager::Get().AddTexture(std::make_shared<Texture>(pathBuffer, typeBuffer, flip));
				ImGui::CloseCurrentPopup();
			}
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::EndPopup();
		}
		ImGui::Separator();

		std::vector<std::shared_ptr<Texture>> textures = ResourceManager::Get().GetAllTextures();
		ImGui::Columns(5);
		ImGui::SetColumnWidth(0, 200.0f);
		ImGui::SetColumnWidth(1, 400.0f);
		ImGui::SetColumnWidth(2, 80.0f);
		ImGui::SetColumnWidth(3, 60.0f);
		ImGui::SetColumnWidth(4, 220.0f);

		ImGui::Text("Name");
		ImGui::NextColumn();
		ImGui::Text("Path");
		ImGui::NextColumn();
		ImGui::Text("Type");
		ImGui::NextColumn();
		ImGui::Text("Flipped");
		ImGui::NextColumn();
		ImGui::Text("Action");
		ImGui::NextColumn();

		ImGui::Separator();
		ImGui::Separator();

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			ImGui::Text(textures[i]->name.c_str());
			ImGui::NextColumn();
			ImGui::Text(textures[i]->path.c_str());
			ImGui::NextColumn();
			ImGui::Text(textures[i]->type.c_str());
			ImGui::NextColumn();
			bool flipped = textures[i]->GetFlipped();
			ImGui::Checkbox("", &flipped);
			ImGui::NextColumn();

			std::string buttonName = "Delete ";
			buttonName.append(textures[i]->name);
			if (ImGui::Button(buttonName.c_str()))
				ImGui::OpenPopup(buttonName.c_str());

			if (ImGui::BeginPopupModal(buttonName.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("This texture will be deleted.\nPlease make sure no GameObject uses it.\n\n");
				ImGui::Separator();

				if (ImGui::Button("OK", ImVec2(120, 0)))
				{
					ResourceManager::Get().RemoveTexture(i);
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

