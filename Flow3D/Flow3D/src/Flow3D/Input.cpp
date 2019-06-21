#include "Input.hpp"

#include "Log.hpp"

namespace Flow {

	Input* Input::s_Instance = nullptr;

	Input::Input()
		: m_MousePosition(glm::vec2(0, 0))
	{
		// assert for making sure there is only one instance
		s_Instance = this;

		keyMap.push_back(std::make_tuple(Keycode::MouseLeft, "MouseLeft"));
		keyMap.push_back(std::make_tuple(Keycode::MouseRight, "MouseRight"));
		keyMap.push_back(std::make_tuple(Keycode::MouseMiddle, "MouseMiddle"));
		keyMap.push_back(std::make_tuple(Keycode::Space, "Space"));
		keyMap.push_back(std::make_tuple(Keycode::Comma, "Comma"));
		keyMap.push_back(std::make_tuple(Keycode::Minus, "Minus"));
		keyMap.push_back(std::make_tuple(Keycode::Period, "Period"));
		keyMap.push_back(std::make_tuple(Keycode::Slash, "Slash"));
		keyMap.push_back(std::make_tuple(Keycode::Key0, "Key0"));
		keyMap.push_back(std::make_tuple(Keycode::Key1, "Key1"));
		keyMap.push_back(std::make_tuple(Keycode::Key2, "Key2"));
		keyMap.push_back(std::make_tuple(Keycode::Key3, "Key3"));
		keyMap.push_back(std::make_tuple(Keycode::Key4, "Key4"));
		keyMap.push_back(std::make_tuple(Keycode::Key5, "Key5"));
		keyMap.push_back(std::make_tuple(Keycode::Key6, "Key6"));
		keyMap.push_back(std::make_tuple(Keycode::Key7, "Key7"));
		keyMap.push_back(std::make_tuple(Keycode::Key8, "Key8"));
		keyMap.push_back(std::make_tuple(Keycode::Key9, "Key9"));
		keyMap.push_back(std::make_tuple(Keycode::Semicolon, "Semicolon"));
		keyMap.push_back(std::make_tuple(Keycode::Equal, "Equal"));
		keyMap.push_back(std::make_tuple(Keycode::A, "A"));
		keyMap.push_back(std::make_tuple(Keycode::B, "B"));
		keyMap.push_back(std::make_tuple(Keycode::C, "C"));
		keyMap.push_back(std::make_tuple(Keycode::D, "D"));
		keyMap.push_back(std::make_tuple(Keycode::E, "E"));
		keyMap.push_back(std::make_tuple(Keycode::F, "F"));
		keyMap.push_back(std::make_tuple(Keycode::G, "G"));
		keyMap.push_back(std::make_tuple(Keycode::H, "H"));
		keyMap.push_back(std::make_tuple(Keycode::I, "I"));
		keyMap.push_back(std::make_tuple(Keycode::J, "J"));
		keyMap.push_back(std::make_tuple(Keycode::K, "K"));
		keyMap.push_back(std::make_tuple(Keycode::L, "L"));
		keyMap.push_back(std::make_tuple(Keycode::M, "M"));
		keyMap.push_back(std::make_tuple(Keycode::N, "N"));
		keyMap.push_back(std::make_tuple(Keycode::O, "O"));
		keyMap.push_back(std::make_tuple(Keycode::P, "P"));
		keyMap.push_back(std::make_tuple(Keycode::Q, "Q"));
		keyMap.push_back(std::make_tuple(Keycode::R, "R"));
		keyMap.push_back(std::make_tuple(Keycode::S, "S"));
		keyMap.push_back(std::make_tuple(Keycode::T, "T"));
		keyMap.push_back(std::make_tuple(Keycode::U, "U"));
		keyMap.push_back(std::make_tuple(Keycode::V, "V"));
		keyMap.push_back(std::make_tuple(Keycode::W, "W"));
		keyMap.push_back(std::make_tuple(Keycode::X, "X"));
		keyMap.push_back(std::make_tuple(Keycode::Y, "Y"));
		keyMap.push_back(std::make_tuple(Keycode::Z, "Z"));
		keyMap.push_back(std::make_tuple(Keycode::LeftBracket, "LeftBracket"));
		keyMap.push_back(std::make_tuple(Keycode::Backslash, "Backslash"));
		keyMap.push_back(std::make_tuple(Keycode::RightBracket, "RightBracket"));
		keyMap.push_back(std::make_tuple(Keycode::GraveAccent, "GraveAccent"));
		keyMap.push_back(std::make_tuple(Keycode::Escape, "Escape"));
		keyMap.push_back(std::make_tuple(Keycode::Enter, "Enter"));
		keyMap.push_back(std::make_tuple(Keycode::Tab, "Tab"));
		keyMap.push_back(std::make_tuple(Keycode::Backspace, "Backspace"));
		keyMap.push_back(std::make_tuple(Keycode::Z, "Z"));
		keyMap.push_back(std::make_tuple(Keycode::LeftBracket, "LeftBracket"));
		keyMap.push_back(std::make_tuple(Keycode::Insert, "Insert"));
		keyMap.push_back(std::make_tuple(Keycode::Delete, "Delete"));
		keyMap.push_back(std::make_tuple(Keycode::Right, "Right"));
		keyMap.push_back(std::make_tuple(Keycode::Left, "Left"));
		keyMap.push_back(std::make_tuple(Keycode::Down, "Down"));
		keyMap.push_back(std::make_tuple(Keycode::Up, "Up"));
		keyMap.push_back(std::make_tuple(Keycode::PageUp, "PageUp"));
		keyMap.push_back(std::make_tuple(Keycode::PageDown, "PageDown"));
		keyMap.push_back(std::make_tuple(Keycode::Home, "Home"));
		keyMap.push_back(std::make_tuple(Keycode::End, "End"));
		keyMap.push_back(std::make_tuple(Keycode::CapsLock, "CapsLock"));
		keyMap.push_back(std::make_tuple(Keycode::ScrollLock, "ScrollLock"));
		keyMap.push_back(std::make_tuple(Keycode::NumLock, "NumLock"));
		keyMap.push_back(std::make_tuple(Keycode::PrintScreen, "PrintScreen"));
		keyMap.push_back(std::make_tuple(Keycode::Pause, "Pause"));
		keyMap.push_back(std::make_tuple(Keycode::F1, "F1"));
		keyMap.push_back(std::make_tuple(Keycode::F2, "F2"));
		keyMap.push_back(std::make_tuple(Keycode::F3, "F3"));
		keyMap.push_back(std::make_tuple(Keycode::F4, "F4"));
		keyMap.push_back(std::make_tuple(Keycode::F5, "F5"));
		keyMap.push_back(std::make_tuple(Keycode::F6, "F6"));
		keyMap.push_back(std::make_tuple(Keycode::F7, "F7"));
		keyMap.push_back(std::make_tuple(Keycode::F8, "F8"));
		keyMap.push_back(std::make_tuple(Keycode::F9, "F9"));
		keyMap.push_back(std::make_tuple(Keycode::F10, "F10"));
		keyMap.push_back(std::make_tuple(Keycode::F11, "F11"));
		keyMap.push_back(std::make_tuple(Keycode::F12, "F12"));
		keyMap.push_back(std::make_tuple(Keycode::Num0, "Num0"));
		keyMap.push_back(std::make_tuple(Keycode::Num1, "Num1"));
		keyMap.push_back(std::make_tuple(Keycode::Num2, "Num2"));
		keyMap.push_back(std::make_tuple(Keycode::Num3, "Num3"));
		keyMap.push_back(std::make_tuple(Keycode::Num4, "Num4"));
		keyMap.push_back(std::make_tuple(Keycode::Num5, "Num5"));
		keyMap.push_back(std::make_tuple(Keycode::Num6, "Num6"));
		keyMap.push_back(std::make_tuple(Keycode::Num7, "Num7"));
		keyMap.push_back(std::make_tuple(Keycode::Num8, "Num8"));
		keyMap.push_back(std::make_tuple(Keycode::Num9, "Num9"));
		keyMap.push_back(std::make_tuple(Keycode::Decimal, "Decimal"));
		keyMap.push_back(std::make_tuple(Keycode::Divide, "Divide"));
		keyMap.push_back(std::make_tuple(Keycode::Multiply, "Multiply"));
		keyMap.push_back(std::make_tuple(Keycode::Subtract, "Subtract"));
		keyMap.push_back(std::make_tuple(Keycode::Add, "Add"));
		keyMap.push_back(std::make_tuple(Keycode::NumEnter, "NumEnter"));
		keyMap.push_back(std::make_tuple(Keycode::NumEqual, "NumEqual"));
		keyMap.push_back(std::make_tuple(Keycode::LeftShift, "LeftShift"));
		keyMap.push_back(std::make_tuple(Keycode::LeftControl, "LeftControl"));
		keyMap.push_back(std::make_tuple(Keycode::LeftAlt, "LeftAlt"));
		keyMap.push_back(std::make_tuple(Keycode::LeftSuper, "LeftSuper"));
		keyMap.push_back(std::make_tuple(Keycode::RightShift, "RightShift"));
		keyMap.push_back(std::make_tuple(Keycode::RightControl, "RightControl"));
		keyMap.push_back(std::make_tuple(Keycode::RightAlt, "RightAlt"));
		keyMap.push_back(std::make_tuple(Keycode::RightSuper, "RightSuper"));
		keyMap.push_back(std::make_tuple(Keycode::Menu, "Menu"));

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