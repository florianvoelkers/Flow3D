#pragma once

#include "Component.hpp"
#include "Flow3D/Input.hpp"

#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>

namespace Flow {

	// Constructor: ComponentToggler(GameObject& gameObject, Component& componentToToggle, bool enabled = true)
	// gives the object the functionality and data to enable/disable the referenced component
	class ComponentToggler : public Component
	{
		CLASS_DECLARATION(ComponentToggler)

	public:
		ComponentToggler(GameObject& gameObject, Component* componentToToggle, bool enabled = true) 
			: Component(gameObject, enabled, "ComponentToggler"), m_Input(Input::Get()), m_ComponentToToggle(componentToToggle) {}

		virtual void OnEvent(Event& e) override
		{
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<KeyPressedEvent>(FLOW_BIND_EVENT_FUNCTION(ComponentToggler::OnKeyPressed));
		}

		Component& GetComponentToToggle() { return *m_ComponentToToggle; }
		void SetComponentToToggle(Component* componentToToggle) { m_ComponentToToggle = componentToToggle; }

		void AddComponentToToggle(std::tuple<Component*, Keycode> component)
		{
			m_ComponentsToToggle.push_back(component);
		}


		std::vector<std::tuple<Component*, Keycode>> GetComponentsToToggle() { return m_ComponentsToToggle; }

	private:
		Input& m_Input;
		Component* m_ComponentToToggle;

		std::vector<std::tuple<Component*, Keycode>> m_ComponentsToToggle;

		bool OnKeyPressed(KeyPressedEvent& e)
		{
			if (e.GetKeyCode() == (int)Keycode::T)
				m_ComponentToToggle->SetEnabled(!m_ComponentToToggle->GetEnabled());

			for (std::vector<std::tuple<Component*, Keycode>>::const_iterator i = m_ComponentsToToggle.begin(); i != m_ComponentsToToggle.end(); ++i)
				if (e.GetKeyCode() == (int)std::get<1>(*i))
					std::get<0>(*i)->SetEnabled(!std::get<0>(*i)->GetEnabled());

			return false; // should not block other events right now because it is only for testing
		}
	};
}
