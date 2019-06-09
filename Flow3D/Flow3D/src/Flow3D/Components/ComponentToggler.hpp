#pragma once

#include "Component.hpp"
#include "Flow3D/Input.hpp"

namespace Flow {

	// Constructor: ComponentToggler(GameObject& gameObject, Component& componentToToggle, bool enabled = true)
	// gives the object the functionality and data to enable/disable the referenced component
	class ComponentToggler : public Component
	{
		CLASS_DECLARATION(ComponentToggler)

	public:
		ComponentToggler(GameObject& gameObject, Component& componentToToggle, bool enabled = true) 
			: Component(gameObject, enabled, "ComponentToggler"), m_Input(Input::Get()), m_ComponentToToggle(componentToToggle) {}

		virtual void OnEvent(Event& e) override
		{
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<KeyPressedEvent>(FLOW_BIND_EVENT_FUNCTION(ComponentToggler::OnKeyPressed));
		}

	private:
		Input& m_Input;
		Component& m_ComponentToToggle;

		bool OnKeyPressed(KeyPressedEvent& e)
		{
			if (e.GetKeyCode() == (int)Keycode::T)
				m_ComponentToToggle.SetEnabled(!m_ComponentToToggle.GetEnabled());

			return false; // should not block other events right now because it is only for testing
		}
	};
}
