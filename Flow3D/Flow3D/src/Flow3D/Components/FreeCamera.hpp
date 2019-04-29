#pragma once

#include "Component.hpp"
#include "Flow3D/Math.hpp"
#include "Flow3D/Window.hpp"
#include "Flow3D/Input.hpp"

namespace Flow {

	// TODO: should be able to set these somewhere
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
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
			m_WorldUp = Vec3(0.0f, 1.0f, 0.0f);
			m_Yaw = YAW;
			m_Pitch = PITCH;
			m_MovementSpeed = SPEED;
			m_MouseSensitivity = SENSITIVITY;
			m_Zoom = ZOOM;

			UpdateCameraVectors();

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
				GetTransform()->m_Position += m_Front * velocity;
			}
			if (m_Input.GetKey(Keycode::S))
			{
				GetTransform()->m_Position -= m_Front * velocity;
			}
			if (m_Input.GetKey(Keycode::D))
			{
				GetTransform()->m_Position += m_Right * velocity;
			}
			if (m_Input.GetKey(Keycode::A))
			{
				GetTransform()->m_Position -= m_Right * velocity;
			}
			if (m_Input.GetKey(Keycode::PageUp))
			{
				GetTransform()->m_Position += m_Up * velocity;
			}
			if (m_Input.GetKey(Keycode::PageDown))
			{
				GetTransform()->m_Position -= m_Up * velocity;
			}

			UpdateCameraVectors();
		}

		virtual void OnEvent(Event& event) override
		{
			EventDispatcher dispatcher(event);
			dispatcher.Dispatch<MouseMovedEvent>(FLOW_BIND_EVENT_FUNCTION(FreeCamera::OnMouseMoved));
			// TODO: mouse scroll
		}

		Mat4 GetViewMatrix() { return Mat4::LookAt(GetTransform()->m_Position, GetTransform()->m_Position + m_Front, m_Up); }
		float GetZoom() { return m_Zoom; }

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

		Input& m_Input;

		void UpdateCameraVectors()
		{
			Vec3 front;
			front.x = Math::Cos(m_Yaw) * Math::Cos(m_Pitch);
			front.y = Math::Sin(m_Pitch);
			front.z = Math::Sin(m_Yaw) * Math::Cos(m_Pitch);
			m_Front = front.Normalize();
			m_Right = Vec3::Cross(m_Front, m_WorldUp).Normalize();
			m_Up = Vec3::Cross(m_Right, m_Front).Normalize();
		}

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

			m_Yaw += xOffset;
			m_Pitch += yOffset;

			// constrain the pitch so the camera can only rotate 89° upwards and downwards
			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;

			UpdateCameraVectors();

			return false;
		}
	};
}
