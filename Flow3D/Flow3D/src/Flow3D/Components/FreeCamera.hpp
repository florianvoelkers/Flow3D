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

	class FreeCamera : public Component
	{
		CLASS_DECLARATION(FreeCamera)

	public:
		FreeCamera(GameObject* gameObject, const Window& window)
			: m_Window(&window), Component(gameObject)
		{
			m_WorldUp = Vec3(0.0f, 1.0f, 0.0f);
			m_Yaw = YAW;
			m_Pitch = PITCH;
			m_MovementSpeed = SPEED;
			m_MouseSensitivity = SENSITIVITY;
			m_Zoom = ZOOM;

			UpdateCameraVectors();

			firstMouse = true;
			lastMouse = Vec2((float)m_Window->GetWidth() / 2, (float)m_Window->GetHeight() / 2);
		}

		~FreeCamera()
		{
			// TODO: does m_Window need to be deleted here?
		}

		virtual void OnUpdate(double deltaTime) override
		{

			float velocity = m_MovementSpeed * (float)deltaTime;

			Input& input = Input::Get();
			if (input.GetKey(Keycode::W))
			{
				GetTransform()->m_Position += m_Front * velocity;
			}
			if (input.GetKey(Keycode::S))
			{
				GetTransform()->m_Position -= m_Front * velocity;
			}
			if (input.GetKey(Keycode::D))
			{
				GetTransform()->m_Position += m_Right * velocity;
			}
			if (input.GetKey(Keycode::A))
			{
				GetTransform()->m_Position -= m_Right * velocity;
			}
			if (input.GetKey(Keycode::PageUp))
			{
				GetTransform()->m_Position += m_Up * velocity;
			}
			if (input.GetKey(Keycode::PageDown))
			{
				GetTransform()->m_Position -= m_Up * velocity;
			}

			UpdateCameraVectors();
		}

		virtual void OnEvent(Event& event) override
		{
			if (event.GetEventType() == MouseMovedEvent::GetStaticType())
			{
				MouseMovedEvent& mouseEvent = (MouseMovedEvent&)event;
				Vec2 mousePosition = Vec2(mouseEvent.GetX(), mouseEvent.GetY());
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

				if (m_Pitch > 89.0f)
					m_Pitch = 89.0f;
				if (m_Pitch < -89.0f)
					m_Pitch = -89.0f;

				UpdateCameraVectors();
			}

			// TODO: mouse scroll
		}

		Mat4 GetViewMatrix() { return Mat4::LookAt(GetTransform()->m_Position, GetTransform()->m_Position + m_Front, m_Up); }

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
	};
}
