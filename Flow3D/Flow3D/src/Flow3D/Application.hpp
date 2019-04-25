#pragma once

#include "Core.hpp"
#include "LayerStack.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Input.hpp"
#include "Rendering/RenderingEngine.hpp"
#include "Scene.hpp"

#include "Window.hpp"

namespace Flow {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Quit();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		inline GameObject& GetMainCamera() { m_CurrentScene->GetMainCamera(); }

	private:
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		std::unique_ptr <Input> m_Input;
		std::unique_ptr <RenderingEngine> m_RenderingEngine;

		bool OnWindowClose(WindowCloseEvent& e);

		// TODO: temporary for test
		std::unique_ptr<Scene> m_CurrentScene;
	};

	// to be defined in client
	Application* CreateApplication();
}
