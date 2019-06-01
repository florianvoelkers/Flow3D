#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Input.hpp"
#include "Rendering/RenderingEngine.hpp"
#include "Scene.hpp"
#include "ImGui/ImGuiLayer.hpp"

#include "Window.hpp"

namespace Flow {

	// This class manages the application. All systems will be started in the constructor,
	// it controls the application in the Run-Loop, forwards events, handles exiting the application and
	// holds references to the most important systems. There can only be one instance of an application
	// which will be created outside of the engine.
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Quit();

		void OnEvent(Event& e);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		inline GameObject& GetMainCamera() { m_CurrentScene->GetMainCamera(); }
		inline Scene& GetCurrentScene() { return *m_CurrentScene.get(); }
		const std::vector<GameObject*>& GetAllGameObjects() const { return m_CurrentScene->GetRoot().GetChildren(); }
		inline const std::shared_ptr<Shader> GetStandardShader() { return m_StandardShader; }
		inline const unsigned int GetRenderTexture() const { return m_RenderingEngine->GetRenderTexture(); }

	private:
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		std::unique_ptr <Input> m_Input;
		std::unique_ptr <RenderingEngine> m_RenderingEngine;
		std::unique_ptr<Scene> m_CurrentScene;
		std::shared_ptr<Shader> m_StandardShader;
		std::unique_ptr<ImGuiLayer> m_ImGui;

		bool OnWindowClose(WindowCloseEvent& e);	
		bool OnKeyPressed(KeyPressedEvent& e);
	};

	// to be defined in client
	Application* CreateApplication();
}
