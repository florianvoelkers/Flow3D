#pragma once

#include "Flow3D/Events/ApplicationEvent.hpp"
#include "Flow3D/Events/KeyEvent.hpp"
#include "Flow3D/Events/MouseEvent.hpp"

namespace Flow {

	// Creates an ImGui Overlay for the engine which can be customized
	class ImGuiLayer
	{
	public:
		ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate(double deltaTime);
		void OnEvent(Event& event);

		void ToggleDemoWindow(bool showDemo) { m_ShowDemo = showDemo; }
		inline const bool GetShowDemo() const { return m_ShowDemo; }

	private:
		float m_Time = 0.0f;
		bool m_ShowDemo = false;

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);
	};
}
