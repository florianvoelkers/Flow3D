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
	const float SENSITIVITY = 0.01f;
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
		FreeCamera(GameObject* gameObject, const Window& window)
			: m_Window(window), Component(gameObject), m_Input(Input::Get())
		{
			m_MovementSpeed = SPEED;
			m_MouseSensitivity = SENSITIVITY;
			m_Zoom = ZOOM;

			m_Right = Vec3(1.0f, 0.0f, 0.0f);
			m_Front = Vec3(0.0f, 0.0f, -1.0f);

			// make sure that the camera can't be moved
			firstMouse = true;
			// center the mouse position
			lastMouse = Vec2((float)m_Window.GetWidth() / 2, (float)m_Window.GetHeight() / 2);
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
				GetTransform()->Translate(m_Front * velocity);
			}
			if (m_Input.GetKey(Keycode::S))
			{
				GetTransform()->Translate(m_Front * velocity * -1.0f);
			}
			if (m_Input.GetKey(Keycode::D))
			{
				GetTransform()->Translate(m_Right * velocity);
			}
			if (m_Input.GetKey(Keycode::A))
			{
				GetTransform()->Translate(m_Right * velocity * -1.0f);
			}
			if (m_Input.GetKey(Keycode::PageUp))
			{
				Vec3 up = GetTransform()->GetUpVector();
				GetTransform()->Translate(up * velocity);
			}
			if (m_Input.GetKey(Keycode::PageDown))
			{
				Vec3 up = GetTransform()->GetUpVector();
				GetTransform()->Translate(up * velocity * -1.0f);
			}

			/*
			if (m_Input.GetKey(Keycode::J))
			{
				Look(0.0f, 0.01f);
			}
			if (m_Input.GetKey(Keycode::K))
			{
				Look(0.01f, 0.0f);
			}
			if (m_Input.GetKey(Keycode::U))
			{
				Look(0.0f, -0.01f);
			}
			if (m_Input.GetKey(Keycode::I))
			{
				Look(-0.01f, 0.0f);
			}
			*/
		}

		virtual void OnEvent(Event& event) override
		{
			EventDispatcher dispatcher(event);
			dispatcher.Dispatch<MouseMovedEvent>(FLOW_BIND_EVENT_FUNCTION(FreeCamera::OnMouseMoved));
			// TODO: mouse scroll
		}

		Mat4 GetViewMatrix() 
		{ 
			Mat4 view = Quaternion::CalculateView(m_Pitch, GetTransform()->GetOrientation(), GetTransform()->GetWorldPosition());
			return view;
		}
		float GetZoom() { return m_Zoom; }

	private:
		const Window& m_Window;
		bool firstMouse = true;
		Vec2 lastMouse;

		Vec3 m_Front;
		Vec3 m_Right;
		Vec3 m_Up;

		float m_Pitch;

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
			glm::quat yaw = glm::quat(glm::vec3(0.0f, xOffset, 0.0f));

			Quaternion orientationQuat = GetTransform()->GetOrientation();
			glm::quat orientation = glm::quat(orientationQuat.w, orientationQuat.x, orientationQuat.y, orientationQuat.z);
			m_Front = Vec3(glm::vec3(0.0f, 0.0f, -1.0f) * orientation);
			m_Right = Vec3(glm::vec3(1.0f, 0.0f, 0.0f) * orientation);

			orientation = orientation * yaw;
			GetTransform()->SetOrientation(orientation);

			m_Pitch -= yOffset;

			if (m_Pitch > PI / 2)
				m_Pitch = PI / 2;
			else if (m_Pitch < -PI / 2)
				m_Pitch = -PI / 2;
		}
	};
}
