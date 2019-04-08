#pragma once

#include "Core.hpp"
#include "LayerStack.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"

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

	private:
		static Application* s_Instance;

		bool m_Running = true;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& e);
	};

	// to be defined in client
	Application* CreateApplication();
}
