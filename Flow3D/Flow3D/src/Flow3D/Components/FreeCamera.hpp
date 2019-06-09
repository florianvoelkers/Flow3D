#pragma once

#include "Component.hpp"
#include "Flow3D/Math.hpp"
#include "Flow3D/Window.hpp"
#include "Flow3D/Input.hpp"

#include "Flow3D/Log.hpp"

namespace Flow {

	static const float PI = 3.1415926f;

	// TODO: should be able to set these somewhere
	const float SPEED = 5.0f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	// Constructor: FreeCamera(GameObject* gameObject, const Window& window)
	// Gives functionality and data for a free moving camera which can be moved with 
	// PAGE UP, PAGE DOWN for vertical movement,
	// WASD or UP, DOWN, LEFT, RIGHT 
	// and rotated with mouse movement
	class FreeCamera : public Component
	{
		CLASS_DECLARATION(FreeCamera)

	public:
		FreeCamera(GameObject& gameObject, const Window& window, bool enabled = true)
			: m_Window(window), Component(gameObject, enabled, "FreeCamera"), m_Input(Input::Get())
		{
			m_MovementSpeed = SPEED;
			m_MouseSensitivity = SENSITIVITY;
			m_Zoom = ZOOM;

			m_WorldUp = Vec3(0.0f, 1.0f, 0.0f);

			m_Yaw = -90.0f;
			m_Pitch = 0.0f;

			GetTransform().SetIsCamera(true);

			// make sure that the camera can't be moved
			firstMouse = true;
			// center the mouse position
			lastMouse = Vec2((float)m_Window.GetWidth() / 2, (float)m_Window.GetHeight() / 2);

			UpdateVectors();
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
				Vec3 front = GetTransform().GetFrontVector();
				GetTransform().Translate(front * velocity);
			}
			if (m_Input.GetKey(Keycode::S))
			{
				Vec3 front = GetTransform().GetFrontVector();
				GetTransform().Translate(front * velocity * -1.0f);
			}
			if (m_Input.GetKey(Keycode::D))
			{
				Vec3 right = GetTransform().GetRightVector();
				GetTransform().Translate(right * velocity);
			}
			if (m_Input.GetKey(Keycode::A))
			{
				Vec3 right = GetTransform().GetRightVector();
				GetTransform().Translate(right * velocity * -1.0f);
			}
			if (m_Input.GetKey(Keycode::PageUp))
			{
				Vec3 up = GetTransform().GetUpVector();
				GetTransform().Translate(up * velocity);
			}
			if (m_Input.GetKey(Keycode::PageDown))
			{
				Vec3 up = GetTransform().GetUpVector();
				GetTransform().Translate(up * velocity * -1.0f);
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
			Vec3 position = GetTransform().GetPosition();
			return Mat4::LookAt(position, position + m_Front, m_Up);
		}

		float GetZoom() { return m_Zoom; }

	private:
		const Window& m_Window;
		bool firstMouse = true;
		Vec2 lastMouse;

		float m_Pitch;
		float m_Yaw;
		float adjustedYaw;

		Vec3 m_WorldUp;
		Vec3 m_Front;
		Vec3 m_Right;
		Vec3 m_Up;

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

			Look(xOffset, yOffset);

			return false;
		}

		// adapted from: https://community.khronos.org/t/how-to-limit-x-axis-rotation/75515/11
		void Look(float xOffset, float yOffset) {
			m_Yaw += xOffset;
			m_Pitch += yOffset;

			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;

			if (m_Yaw < -450.0f)
				m_Yaw = -90.0f;
			if (m_Yaw >= 270.0f)
				m_Yaw = -90.0f;

			UpdateVectors();
		}

		void UpdateVectors()
		{
			// Calculate the new Front vector
			glm::vec3 front;
			front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
			front.y = sin(glm::radians(m_Pitch));
			front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
			m_Front = Vec3(glm::normalize(front));
			// Also re-calculate the Right and Up vector
			m_Right = Vec3(glm::normalize(glm::cross(glm::vec3(m_Front.x, m_Front.y, m_Front.z), glm::vec3(m_WorldUp.x, m_WorldUp.y, m_WorldUp.z))));
			// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			m_Up = glm::normalize(glm::cross(glm::vec3(m_Right.x, m_Right.y, m_Right.z), glm::vec3(m_Front.x, m_Front.y, m_Front.z)));

			Vec3 rotationVector = Vec3(- 1 * m_Pitch, m_Yaw + 90.0f, 0.0f);
			
			Quaternion rotation = Quaternion(rotationVector);
			GetTransform().SetOrientation(rotation);
			GetTransform().SetFrontVector(m_Front);
			GetTransform().SetRightVector(m_Right);
			GetTransform().SetUpVector(m_Up);
		}
	};
}
