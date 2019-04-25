#pragma once

#include "Layer.hpp"
#include "Window.hpp"
#include "GameObject.hpp"

namespace Flow {

	// the scene represents a game world, you can have several scenes which can be switched in the application
	// it is made up of GameObjects (1 GameObject root and its children) with components
	class Scene : public Layer
	{
	public:
		Scene(std::string name, const Window& window);
		~Scene();

		void AddToScene(GameObject* gameObject);

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(double deltaTime) override;
		void OnEvent(Event& event) override;

		inline std::string GetName() { return m_Name; };
		inline GameObject& GetRoot() { return *m_Root; } // is this correct?
		inline GameObject& GetMainCamera() { return *m_MainCamera; }

	private:
		const Window* m_Window;
		GameObject* m_Root;
		std::string m_Name;
		GameObject* m_MainCamera;

		// TODO: Members directional light, other properties
	};
}