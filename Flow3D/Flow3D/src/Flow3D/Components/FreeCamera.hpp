#pragma once

#include "Component.hpp"
#include "Flow3D/Math.hpp"
#include "Flow3D/Window.hpp"

namespace Flow {

	// TODO: should be able to set these somewhere
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	class FreeCamera : public Component
	{
	public:
		FreeCamera(GameObject* gameObject, const Window& window);
		~FreeCamera();

		virtual void OnUpdate(double deltaTime) override;
		virtual void OnEvent(Event& event) override;

		Mat4 GetViewMatrix();

	private:
		const Window* m_Window;
		bool firstMouse = true;
		Vec2 lastMouse;

		Vec3 m_Front;
		Vec3 m_Up;
		Vec3 m_Right;
		Vec3 m_WorldUp;

		float m_Yaw;
		float m_Pitch;

		float m_MovementSpeed;
		float m_MouseSensitivity;
		float m_Zoom;

		void UpdateCameraVectors();
	};
}
