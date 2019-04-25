#include "FreeCamera.hpp"

#include "Flow3D/Events/MouseEvent.hpp"
#include "Flow3D/Input.hpp"

namespace Flow {

	FreeCamera::FreeCamera(GameObject* gameObject, const Window& window)
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

	FreeCamera::~FreeCamera()
	{
		// TODO: does m_Window need to be deleted here?
	}

	void FreeCamera::OnUpdate(double deltaTime)
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

	void FreeCamera::OnEvent(Event& event)
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

	Mat4 FreeCamera::GetViewMatrix()
	{
		return Mat4::LookAt(GetTransform()->m_Position, GetTransform()->m_Position + m_Front, m_Up);
	}

	void FreeCamera::UpdateCameraVectors()
	{
		Vec3 front;
		front.x = Math::Cos(m_Yaw) * Math::Cos(m_Pitch);
		front.y = Math::Sin(m_Pitch);
		front.z = Math::Sin(m_Yaw) * Math::Cos(m_Pitch);
		m_Front = front.Normalize();
		m_Right = Vec3::Cross(m_Front, m_WorldUp).Normalize();
		m_Up = Vec3::Cross(m_Right, m_Front).Normalize();
	}
}