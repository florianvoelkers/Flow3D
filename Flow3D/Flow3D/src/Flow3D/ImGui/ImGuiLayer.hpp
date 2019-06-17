#pragma once

#include "Flow3D/Events/ApplicationEvent.hpp"
#include "Flow3D/Events/KeyEvent.hpp"
#include "Flow3D/Events/MouseEvent.hpp"
#include "Flow3D/Log.hpp"

#include "ImGuiLog.hpp"
#include "ImGuiInspector.hpp"

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

		Flow3DLog& GetLogger() { return *m_Logger; }

		void ToggleReceiveEvents() { m_ReceiveEvents = !m_ReceiveEvents; }
		inline const bool GetReceiveEvents() const { return m_ReceiveEvents; }

	private:
		float m_Time = 0.0f;
		bool m_ReceiveEvents = true;

		std::unique_ptr<Flow3DLog> m_Logger;
		std::unique_ptr<Flow3DInspector> m_Inspector;		

		void ShowGameObject(const char* prefix, int uid, GameObject& child);

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
