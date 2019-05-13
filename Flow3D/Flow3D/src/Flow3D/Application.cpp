#include "Application.hpp"

#include "Input.hpp"
#include "Rendering/RenderingEngine.hpp"

#include "Log.hpp"

namespace Flow {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		// missing assert for making sure there is only one instance
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(FLOW_BIND_EVENT_FUNCTION(Application::OnEvent));
		
		m_Input = std::make_unique<Input>();
		m_RenderingEngine = std::make_unique<RenderingEngine>(*m_Window);

		m_StandardShader = std::make_shared<Shader>("resources/shader/Standard.vert", "resources/shader/Standard.frag");

		m_CurrentScene = std::make_unique<Scene>("TestScene", *m_Window);
		m_CurrentScene->OnAttach();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// application loop: at the moment it runs as fast as it can
		// TODO: setting the frame rate / constant frame rate
		double lastTime = glfwGetTime();
		while (m_Running)
		{
			double current = glfwGetTime();
			double elapsed = current - lastTime;
			lastTime = current;

			m_Input->OnUpdate(elapsed);
			m_CurrentScene->OnUpdate(elapsed);

			// scene should be part of the layer stack but it also should be uniquely accessible
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(elapsed);

			m_RenderingEngine->Render(m_CurrentScene->GetRoot(), m_CurrentScene->GetMainCamera(), m_CurrentScene->GetSkybox());
			m_Window->OnUpdate();
		}
	}

	void Application::Quit()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(FLOW_BIND_EVENT_FUNCTION(Application::OnWindowClose));

		m_Input->OnEvent(e);

		// scene should be part of the layer stack but it also should be uniquely accessible
		// will be executed in reverse order so that overlays will receive events first
		// for example an UI button should mark a mouse click event as handled and no further reactions
		// to that event should be triggered
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}

		m_CurrentScene->OnEvent(e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer * overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopLayer(Layer * layer)
	{
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PopOverlay(Layer * overlay)
	{
		m_LayerStack.PopOverlay(overlay);
		overlay->OnDetach();
	}
}