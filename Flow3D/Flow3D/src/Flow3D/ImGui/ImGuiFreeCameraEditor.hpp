#pragma once

#include <imgui/imgui.h>
#include "Flow3D/Components/FreeCamera.hpp"

namespace Flow {

	struct FreeCameraEditor
	{

		FreeCameraEditor() {}

		void Draw(FreeCamera* freeCamera)
		{
			ImGui::Text("Movement Speed");
			ImGui::SameLine(0, 71);
			ImGui::PushItemWidth(100);

			float movementSpeed = freeCamera->GetMovementSpeed();
			if (ImGui::DragFloat("##4", &movementSpeed, 0.1f))
				freeCamera->SetMovementSpeed(movementSpeed);

			ImGui::Text("Mouse Sensitivity");
			ImGui::SameLine(0, 50);
			ImGui::PushItemWidth(100);

			float mouseSensitivity = freeCamera->GetMouseSensitivy();
			if (ImGui::DragFloat("##5", &mouseSensitivity, 0.01f))
				freeCamera->SetMouseSensititvy(mouseSensitivity);

			ImGui::Text("Field of view");
			ImGui::SameLine(0, 78);
			ImGui::PushItemWidth(100);

			float zoom = freeCamera->GetZoom();
			if (ImGui::DragFloat("##6", &zoom, 0.1f, 0.0f, 100.0f))
				freeCamera->SetZoom(zoom);

			ImGui::Text("Z-Near");
			ImGui::SameLine(0, 127);
			ImGui::PushItemWidth(100);

			float zNear = freeCamera->GetZNear();
			float zFar = freeCamera->GetZFar();
			if (ImGui::DragFloat("##7", &zNear, 0.1f, 0.0f, zFar))
				freeCamera->SetZNear(zNear);

			ImGui::Text("Z-Far");
			ImGui::SameLine(0, 134);
			ImGui::PushItemWidth(100);
			if (ImGui::DragFloat("##8", &zFar, 0.1f, zNear, 1000.0f))
				freeCamera->SetZFar(zFar);
		}
	};
}

