#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/Lighting.hpp"

namespace Flow {

	struct BaseLightEditor
	{

		BaseLightEditor() {}

		void Draw(BaseLight* bl)
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

				if (ImGui::DragFloat("r##8", &ambientR, 0.01f, 0.0f, 1.0f))
					bl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

				ImGui::SameLine();
				if (ImGui::DragFloat("g##8", &ambientG, 0.01f, 0.0f, 1.0f))
					bl->SetAmbientIntensity(Vec3(ambientR, ambientG, ambientB));

				ImGui::SameLine();
				if (ImGui::DragFloat("b##8", &ambientB, 0.01f, 0.0f, 1.0f))
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

				if (ImGui::DragFloat("r##9", &diffuseR, 0.01f, 0.0f, 1.0f))
					bl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

				ImGui::SameLine();
				if (ImGui::DragFloat("g##9", &diffuseG, 0.01f, 0.0f, 1.0f))
					bl->SetDiffuseIntensity(Vec3(diffuseR, diffuseG, diffuseB));

				ImGui::SameLine();
				if (ImGui::DragFloat("b##9", &diffuseB, 0.01f, 0.0f, 1.0f))
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

				if (ImGui::DragFloat("r##10", &specularR, 0.01f, 0.0f, 1.0f))
					bl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

				ImGui::SameLine();
				if (ImGui::DragFloat("g##10", &specularG, 0.01f, 0.0f, 1.0f))
					bl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

				ImGui::SameLine();
				if (ImGui::DragFloat("b##10", &specularB, 0.01f, 0.0f, 1.0f))
					bl->SetSpecularIntensity(Vec3(specularR, specularG, specularB));

				ImGui::PopItemWidth();
			}
		}
	};
}
