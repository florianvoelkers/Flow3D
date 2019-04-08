#include "Input.hpp"

#include "Log.hpp"

namespace Flow {

	Input* Input::s_Instance = nullptr;

	Input::Input()
		: Layer("Input"), m_MousePosition(glm::vec2(0, 0))
	{
		// assert for making sure there is only one instance
		s_Instance = this;

		FLOW_CORE_INFO("input added");

		memset(m_Inputs, 0, NUMBER_OF_KEYS * sizeof(bool));
		memset(m_DownKeys, 0, NUMBER_OF_KEYS * sizeof(bool));
		memset(m_UpKeys, 0, NUMBER_OF_KEYS * sizeof(bool));

		memset(m_MouseInput, 0, NUMBER_OF_MOUSEBUTTONS * sizeof(bool));
		memset(m_DownMouse, 0, NUMBER_OF_MOUSEBUTTONS * sizeof(bool));
		memset(m_UpMouse, 0, NUMBER_OF_MOUSEBUTTONS * sizeof(bool));
	}

	void Input::OnUpdate(double deltaTime)
	{
		for (unsigned int i = 0; i < NUMBER_OF_MOUSEBUTTONS; i++)
		{
			m_DownMouse[i] = false;
			m_UpMouse[i] = false;
		}

		for (unsigned int i = 0; i < NUMBER_OF_KEYS; i++)
		{
			m_DownKeys[i] = false;
			m_UpKeys[i] = false;
		}
	}

	void Input::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseMovedEvent>(FLOW_BIND_EVENT_FUNCTION(Input::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseButtonPressedEvent>(FLOW_BIND_EVENT_FUNCTION(Input::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(FLOW_BIND_EVENT_FUNCTION(Input::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<KeyPressedEvent>(FLOW_BIND_EVENT_FUNCTION(Input::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(FLOW_BIND_EVENT_FUNCTION(Input::OnKeyReleasedEvent));
	}

	bool Input::OnMouseMovedEvent(MouseMovedEvent & event)
	{
		MouseMovedEvent& mouseEvent = (MouseMovedEvent&)event;
		m_MousePosition = Vec2(mouseEvent.GetX(), mouseEvent.GetY());
		return false;
	}

	bool Input::OnMouseButtonPressedEvent(MouseButtonPressedEvent & event)
	{
		MouseButtonPressedEvent& mouseEvent = (MouseButtonPressedEvent&)event;
		m_MouseInput[mouseEvent.GetMouseButton()] = true;
		m_DownMouse[mouseEvent.GetMouseButton()] = true;
		return false;
	}

	bool Input::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent & event)
	{
		MouseButtonReleasedEvent& mouseEvent = (MouseButtonReleasedEvent&)event;
		m_MouseInput[mouseEvent.GetMouseButton()] = false;
		m_UpMouse[mouseEvent.GetMouseButton()] = true;
		return false;
	}

	bool Input::OnKeyPressedEvent(KeyPressedEvent & event)
	{
		KeyPressedEvent& keyEvent = (KeyPressedEvent&)event;
		m_Inputs[keyEvent.GetKeyCode()] = true;
		m_DownKeys[keyEvent.GetKeyCode()] = true;
		return false;
	}

	bool Input::OnKeyReleasedEvent(KeyReleasedEvent & event)
	{
		KeyReleasedEvent& keyEvent = (KeyReleasedEvent&)event;
		m_Inputs[keyEvent.GetKeyCode()] = false;
		m_UpKeys[keyEvent.GetKeyCode()] = true;
		return false;
	}
}