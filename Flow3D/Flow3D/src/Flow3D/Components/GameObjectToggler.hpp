#pragma once

#include "Component.hpp"
#include "Flow3D/Input.hpp"
#include "Flow3D/Application.hpp"

#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>


// Constructor: GameObjectToggler(GameObject& gameObject, std::string gameObjectName, bool enabled = true)
// gives an object the functionality and data to toggle the active state of a given GameObject
class GameObjectToggler : public Component
{
	CLASS_DECLARATION(GameObjectToggler)

public:
	GameObjectToggler() : m_Input(Input::Get()) {}
	GameObjectToggler(GameObject* gameObject, bool enabled = true)
		: Component(gameObject, enabled, "GameObjectToggler"), m_Input(Input::Get())
	{
	}

	virtual void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(FLOW_BIND_EVENT_FUNCTION(GameObjectToggler::OnKeyPressed));
	}

	void AddGameObjectToToggle(std::tuple<GameObject*, std::string, Keycode> gameObject)
	{
		m_GameObjectsToToggle.push_back(gameObject);
		gameObjectsToToggle.push_back(std::make_tuple(std::get<1>(gameObject), (int)std::get<2>(gameObject)));
	}

	void RemoveGameObjectToToggle(GameObject* gameObject)
	{
		for (int i = 0; i < m_GameObjectsToToggle.size(); i++)
		{
			// Test: we're going to delete the tuple of which the 3rd element (index 2) = 3.
			if (std::get<0>(m_GameObjectsToToggle[i]) == gameObject)
			{
				m_GameObjectsToToggle.erase(m_GameObjectsToToggle.begin() + i);
				gameObjectsToToggle.erase(gameObjectsToToggle.begin() + i);
				i--;
			}
		}
	}

	std::vector<std::tuple<GameObject*, std::string, Keycode>>& GetGameObjectsToToggle() { return m_GameObjectsToToggle; }

	// only for serialization
	std::vector<std::tuple<std::string, int>> gameObjectsToToggle;

private:
	Input& m_Input;

	std::vector<std::tuple<GameObject*, std::string, Keycode>> m_GameObjectsToToggle;

	bool OnKeyPressed(KeyPressedEvent& e)
	{
		for (std::vector<std::tuple<GameObject*, std::string, Keycode>>::const_iterator i = m_GameObjectsToToggle.begin(); i != m_GameObjectsToToggle.end(); ++i)
			if (e.GetKeyCode() == (int)std::get<2>(*i))
				std::get<0>(*i)->SetActive(!std::get<0>(*i)->GetIsActive());

		return false; // should not block other events right now because it is only for testing
	}
};

#include <MetaStuff/include/Meta.h>

namespace meta {

	template <>
	inline auto registerMembers<GameObjectToggler>()
	{
		return std::tuple_cat(
			meta::getMembers<Component>(),
			members(
				member("gameObjectsToToggle", &GameObjectToggler::gameObjectsToToggle)
			)
		);
	}

} // end of namespace meta

