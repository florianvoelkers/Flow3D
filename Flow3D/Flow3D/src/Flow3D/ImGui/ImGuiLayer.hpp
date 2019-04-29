#pragma once

#include "Flow3D/Layer.hpp"
#include "Flow3D/Events/ApplicationEvent.hpp"
#include "Flow3D/Events/KeyEvent.hpp"
#include "Flow3D/Events/MouseEvent.hpp"

namespace Flow {

	// Creates an ImGui Overlay for the engine which can be customized
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(double deltaTime) override;
		void OnEvent(Event& event) override;

	private:
		float m_Time = 0.0f;

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
