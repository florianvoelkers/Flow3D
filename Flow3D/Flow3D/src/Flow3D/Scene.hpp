#pragma once

#include "Layer.hpp"
#include "GameObject.hpp"

namespace Flow {

	// the scene represents a game world, you can have several scenes which can be switched in the application
	// it is made up of GameObjects (1 GameObject root and its children) with components
	class Scene : public Layer
	{
	public:
		Scene(std::string name);
		~Scene();

		void AddToScene(GameObject* gameObject);

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(double deltaTime) override;
		void OnEvent(Event& event) override;

		inline std::string GetName() { return m_Name; };
	private:
		std::unique_ptr<GameObject> m_Root;
		std::string m_Name;

		// TODO: Members for a main camera, directional light, other properties
	};
}