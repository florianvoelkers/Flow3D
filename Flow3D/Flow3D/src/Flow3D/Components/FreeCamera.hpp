#pragma once

#include "Component.hpp"
#include "Flow3D/Math.hpp"
#include "Flow3D/Window.hpp"
#include "Flow3D/Input.hpp"

namespace Flow {

	// TODO: should be able to set these somewhere
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	// Gives functionality and data for a free moving camera which can be moved with 
	// PAGE UP, PAGE DOWN for vertical movement,
	// WASD or UP, DOWN, LEFT, RIGHT 
	// and rotated with mouse movement
	class FreeCamera : public Component
	{
		CLASS_DECLARATION(FreeCamera)

	public:
		FreeCamera(GameObject* gameObject, const Window& window)
			: m_Window(&window), Component(gameObject), m_Input(Input::Get())
		{
			m_MovementSpeed = SPEED;
			m_MouseSensitivity = SENSITIVITY;
			m_Zoom = ZOOM;

			// make sure that the camera can't be moved
			firstMouse = true;
			// center the mouse position
			lastMouse = Vec2((float)m_Window->GetWidth() / 2, (float)m_Window->GetHeight() / 2);
		}

		~FreeCamera()
		{
			// TODO: does m_Window need to be deleted here?
		}

		virtual void OnUpdate(double deltaTime) override
		{
			// calculate the velocity depending on the frame rate and user set movement speed
			float velocity = m_MovementSpeed * (float)deltaTime;

			if (m_Input.GetKey(Keycode::W))
			{
				Vec3 front = GetTransform()->GetFrontVector();
				GetTransform()->m_Position += front * velocity;
			}
			if (m_Input.GetKey(Keycode::S))
			{
				Vec3 front = GetTransform()->GetFrontVector();
				GetTransform()->m_Position -= front * velocity;
			}
			if (m_Input.GetKey(Keycode::D))
			{
				Vec3 right = GetTransform()->GetRightVector();
				GetTransform()->m_Position += right * velocity;
			}
			if (m_Input.GetKey(Keycode::A))
			{
				Vec3 right = GetTransform()->GetRightVector();
				GetTransform()->m_Position -= right * velocity;
			}
			if (m_Input.GetKey(Keycode::PageUp))
			{
				Vec3 up = GetTransform()->GetUpVector();
				GetTransform()->m_Position += up * velocity;
			}
			if (m_Input.GetKey(Keycode::PageDown))
			{
				Vec3 up = GetTransform()->GetUpVector();
				GetTransform()->m_Position -= up * velocity;
			}
		}

		virtual void OnEvent(Event& event) override
		{
			EventDispatcher dispatcher(event);
			dispatcher.Dispatch<MouseMovedEvent>(FLOW_BIND_EVENT_FUNCTION(FreeCamera::OnMouseMoved));
			// TODO: mouse scroll
		}

		Mat4 GetViewMatrix() 
		{ 
			return Mat4::LookAt(GetTransform()->m_Position, GetTransform()->m_Position + GetTransform()->GetFrontVector(), GetTransform()->GetUpVector()); 
		}
		float GetZoom() { return m_Zoom; }

	private:
		const Window* m_Window;
		bool firstMouse = true;
		Vec2 lastMouse;

		float m_MovementSpeed;
		float m_MouseSensitivity;
		float m_Zoom;

		Input& m_Input;

		bool OnMouseMoved(MouseMovedEvent& e)
		{
			Vec2 mousePosition = Vec2(e.GetX(), e.GetY());

			// set lastMouse equal to mousePosition when it the first mousemovement is detected
			// so the offset will be 0 for the first movement
			// otherwise the camera will rotate with the first movement and position itself wrong
			if (firstMouse)
			{
				lastMouse = mousePosition;
				firstMouse = false;
			}

			float xOffset = mousePosition.x - lastMouse.x;
			float yOffset = lastMouse.y - mousePosition.y;

			lastMouse = mousePosition;

			xOffset *= m_MouseSensitivity;
			yOffset *= m_MouseSensitivity;

			float yaw = GetTransform()->GetYaw();
			float pitch = GetTransform()->GetPitch();
			
			yaw += xOffset;
			pitch += yOffset;

			// constrain the pitch so the camera can only rotate 89° upwards and downwards
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			GetTransform()->SetYawAndPitch(yaw, pitch);

			return false;
		}
	};
}
