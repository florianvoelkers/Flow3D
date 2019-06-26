#pragma once

#include "Component.hpp"
#include "Flow3D/Input.hpp"

#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>

// Constructor: ComponentToggler(GameObject& gameObject, Component& componentToToggle, bool enabled = true)
// gives the object the functionality and data to enable/disable the referenced component
class ComponentToggler : public Component
{
	CLASS_DECLARATION(ComponentToggler)

public:
	ComponentToggler(GameObject* gameObject, bool enabled = true) 
		: Component(gameObject, enabled, "ComponentToggler"), m_Input(Input::Get()) {}

	virtual void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(FLOW_BIND_EVENT_FUNCTION(ComponentToggler::OnKeyPressed));
	}

	void AddComponentToToggle(std::tuple<Component*, Keycode> component)
	{
		m_ComponentsToToggle.push_back(component);
	}

	void RemoveComponentToToggle(Component* component)
	{
		for (int i = 0; i < m_ComponentsToToggle.size(); i++)
		{
			// Test: we're going to delete the tuple of which the 3rd element (index 2) = 3.
			if (std::get<0>(m_ComponentsToToggle[i]) == component)
			{
				m_ComponentsToToggle.erase(m_ComponentsToToggle.begin() + i);
				i--;
			}
		}
	}

	std::vector<std::tuple<Component*, Keycode>>& GetComponentsToToggle() { return m_ComponentsToToggle; }

	std::vector<std::tuple<Component*, Keycode>> m_ComponentsToToggle;

private:
	Input& m_Input;	

	bool OnKeyPressed(KeyPressedEvent& e)
	{
		for (std::vector<std::tuple<Component*, Keycode>>::const_iterator i = m_ComponentsToToggle.begin(); i != m_ComponentsToToggle.end(); ++i)
			if (e.GetKeyCode() == (int)std::get<1>(*i))
				std::get<0>(*i)->SetEnabled(!std::get<0>(*i)->GetEnabled());

		return false; // should not block other events right now because it is only for testing
	}
};



