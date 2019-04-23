#pragma once

#include "Flow3D/Math.hpp"

#include <vector>

#include "Flow3D/Input.hpp"
#include "Flow3D/Window.hpp"
#include "Flow3D/Log.hpp"
#include "Flow3D/Events/MouseEvent.hpp"

namespace Flow {

	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	class Camera {

	public:
		Vec3 m_Position;
		Vec3 m_Front;
		Vec3 m_Up;
		Vec3 m_Right;
		Vec3 m_WorldUp;

		float m_Yaw;
		float m_Pitch;

		float m_MovementSpeed;
		float m_MouseSensitivity;
		float m_Zoom;

		Camera(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), Vec3 up = Vec3(0.0f, 1.0f, 0.0f),
			float yaw = YAW, float pitch = PITCH)
			: m_Front(Vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
		{
			m_Position = position;
			m_WorldUp = up;
			m_Yaw = yaw;
			m_Pitch = pitch;

			UpdateCameraVectors();
		}

		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
			: m_Front(Vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
		{
			m_Position = Vec3(posX, posY, posZ);
			m_WorldUp = Vec3(upX, upY, upZ);
			m_Yaw = yaw;
			m_Pitch = pitch;

			UpdateCameraVectors();
		}

		void SetWindow(const Window& window)
		{
			m_Window = &window;

			firstMouse = true;
			lastMouse = Vec2((float)m_Window->GetWidth() / 2, (float)m_Window->GetHeight() / 2);
		}

		Mat4 GetViewMatrix()
		{
			return Mat4::LookAt(m_Position, m_Position + m_Front, m_Up);
		}

		void OnEvent(Event& event)
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

		void OnUpdate(double deltaTime)
		{
			float velocity = m_MovementSpeed * (float)deltaTime;

			Input& input = Input::Get();
			if (input.GetKey(Keycode::W))
			{
				m_Position += m_Front * velocity;
			}
			if (input.GetKey(Keycode::S))
			{
				m_Position -= m_Front * velocity;
			}
			if (input.GetKey(Keycode::D))
			{
				m_Position += m_Right * velocity;
			}
			if (input.GetKey(Keycode::A))
			{
				m_Position -= m_Right * velocity;
			}
			if (input.GetKey(Keycode::PageUp))
			{
				m_Position += m_Up * velocity;
			}
			if (input.GetKey(Keycode::PageDown))
			{
				m_Position -= m_Up * velocity;
			}

			UpdateCameraVectors();
		}

	private:
		const Window* m_Window;
		bool firstMouse = true;
		Vec2 lastMouse;

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



