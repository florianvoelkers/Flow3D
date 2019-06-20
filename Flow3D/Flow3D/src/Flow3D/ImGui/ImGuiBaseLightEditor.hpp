#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/Lighting.hpp"

namespace Flow {

	struct BaseLightEditor
	{

		BaseLightEditor() {}

		void Draw(BaseLight* bl, std::string lightType)
		{
			if (bl != nullptr)
			{
				Vec3 ambient = bl->GetAmbientIntensity();
				float ambientR, ambientG, ambientB;
				ambientR = ambient.x;
				ambientG = ambient.y;
				ambientB = ambient.z;
				ImGui::Text("Ambient");
				ImGui::SameLine(0, 20);
				ImGui::PushItemWidth(66);

				std::string label = "r##8";
				label.append(lightType);
				if (ImGui::DragFloat(label.c_str(), &ambientR, 0.01f, 0.0f, 1.0f))
					bl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

				ImGui::SameLine();
				label = "g##8";
				label.append(lightType);
				if (ImGui::DragFloat(label.c_str(), &ambientG, 0.01f, 0.0f, 1.0f))
					bl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

				ImGui::SameLine();
				label = "b##8";
				label.append(lightType);
				if (ImGui::DragFloat(label.c_str(), &ambientB, 0.01f, 0.0f, 1.0f))
					bl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

				ImGui::PopItemWidth();

				Vec3 diffuse = bl->GetDiffuseIntensity();
				float diffuseR, diffuseG, diffuseB;
				diffuseR = diffuse.x;
				diffuseG = diffuse.y;
				diffuseB = diffuse.z;
				ImGui::Text("Diffuse");
				ImGui::SameLine(0, 20);
				ImGui::PushItemWidth(66);

				label = "r##9";
				label.append(lightType);
				if (ImGui::DragFloat(label.c_str(), &diffuseR, 0.01f, 0.0f, 1.0f))
					bl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

				ImGui::SameLine();
				label = "g##9";
				label.append(lightType);
				if (ImGui::DragFloat(label.c_str(), &diffuseG, 0.01f, 0.0f, 1.0f))
					bl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

				ImGui::SameLine();
				label = "b##9";
				label.append(lightType);
				if (ImGui::DragFloat(label.c_str(), &diffuseB, 0.01f, 0.0f, 1.0f))
					bl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

				ImGui::PopItemWidth();

				Vec3 specular = bl->GetSpecularIntensity();
				float specularR, specularG, specularB;
				specularR = specular.x;
				specularG = specular.y;
				specularB = specular.z;
				ImGui::Text("Specular");
				ImGui::SameLine(0, 13);
				ImGui::PushItemWidth(66);

				label = "r##10";
				label.append(lightType);
				if (ImGui::DragFloat(label.c_str(), &specularR, 0.01f, 0.0f, 1.0f))
					bl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

				ImGui::SameLine();
				label = "g##10";
				label.append(lightType);
				if (ImGui::DragFloat(label.c_str(), &specularG, 0.01f, 0.0f, 1.0f))
					bl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

				ImGui::SameLine();
				label = "b##10";
				label.append(lightType);
				if (ImGui::DragFloat(label.c_str(), &specularB, 0.01f, 0.0f, 1.0f))
					bl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

				ImGui::PopItemWidth();
			}
		}
	};
}
