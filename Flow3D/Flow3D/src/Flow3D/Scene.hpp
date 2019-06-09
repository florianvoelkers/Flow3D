#pragma once

#include "Window.hpp"
#include "GameObject.hpp"
#include "Rendering/Skybox.hpp"
#include "Flow3D/Components/Lighting.hpp"

namespace Flow {

	// The scene represents a game world, you can have several scenes which can be switched in the application.
	// It is made up of GameObjects (1 GameObject root and its children) with components.
	class Scene
	{
	public:
		Scene(std::string name, const Window& window);
		~Scene();

		void AddToScene(GameObject* gameObject);

		void OnAttach();
		void OnDetach();
		void OnUpdate(double deltaTime);
		void OnEvent(Event& event);

		inline GameObject* FindGameObject(std::string name);

		inline std::string GetName() { return m_Name; };
		inline GameObject& GetRoot() { return *m_Root; } // is this correct?
		inline GameObject& GetMainCamera() { return *m_MainCamera; }
		inline Skybox& GetSkybox() { return *m_Skybox; } // is this correct?

		void SetDirectionalLight(DirectionalLight* directionalLight);
		inline DirectionalLight& GetDirectionalLight() { return *m_DirectionalLight; }

		void AddPointLight(PointLight* pointLight);
		void RemovePointLight(PointLight* pointLight);
		inline std::vector<PointLight*> GetPointLights() { return m_PointLights; }

		void AddSpotLight(SpotLight* spotLight);
		void RemoveSpotLight(SpotLight* spotLight);
		inline std::vector<SpotLight*> GetSpotLights() { return m_SpotLights; }

	private:
		const Window& m_Window;
		GameObject* m_Root;
		std::string m_Name;
		GameObject* m_MainCamera;
		std::unique_ptr<Skybox> m_Skybox;

		DirectionalLight* m_DirectionalLight;
		std::vector<PointLight*> m_PointLights;
		std::vector<SpotLight*> m_SpotLights;

		// TODO: Members directional light, other properties
	};
}