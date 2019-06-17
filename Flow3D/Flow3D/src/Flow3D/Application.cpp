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

		// TODO: load scene data from file; until then manually create scene objects here
		textures.push_back(std::make_shared<Texture>("resources/textures/container.jpg", "diffuse", true));					// 0
		textures.push_back(std::make_shared<Texture>("resources/textures/brickwall.jpg", "diffuse", true));					// 1
		textures.push_back(std::make_shared<Texture>("resources/textures/wall.jpg", "diffuse", true));						// 2
		textures.push_back(std::make_shared<Texture>("resources/textures/metal.png", "diffuse", true));						// 3
		textures.push_back(std::make_shared<Texture>("resources/textures/grass.png", "diffuse", true));						// 4
		textures.push_back(std::make_shared<Texture>("resources/textures/container2.png", "diffuse", true));				// 5
		textures.push_back(std::make_shared<Texture>("resources/textures/container2_specular.png", "specular", true));		// 6		

		shaders.push_back(std::make_shared<Shader>("resources/shader/Standard.vert", "resources/shader/Standard.frag", "Standard"));
		shaders.push_back(std::make_shared<Shader>("resources/shader/Basic3D.vert", "resources/shader/Colored.frag", "Colored"));
		shaders.push_back(std::make_shared<Shader>("resources/shader/Standard.vert", "resources/shader/Standard.frag", "Models"));

		models.push_back(std::make_shared<Model>("resources/models/Tree/Tree.obj"));
		models.push_back(std::make_shared<Model>("resources/models/man/muro.obj"));
		models.push_back(std::make_shared<Model>("resources/models/trex/trex.fbx"));
		models.push_back(std::make_shared<Model>("resources/models/old_house/house.obj"));
		models.push_back(std::make_shared<Model>("resources/models/house/house.obj"));
		models.push_back(std::make_shared<Model>("resources/models/sword/Sword.obj"));

		m_CurrentScene = std::make_unique<Scene>("TestScene", *m_Window);
		m_CurrentScene->OnAttach();

		m_ImGui = std::make_unique<ImGuiLayer>();
		m_ImGui->OnAttach();

		
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// application loop: at the moment it runs as fast as it can
		// TODO: setting the frame rate / constant frame rate
		double lastTime = glfwGetTime();

		// for counting frames, but GLFW limits the fps to 60 because of VSYNC to avoid screen tearing
		unsigned int numberOfFrames = 0;
		double lastSecond = lastTime;
		while (m_Running)
		{
			double current = glfwGetTime();
			double elapsed = current - lastTime;
			lastTime = current;

			numberOfFrames++;
			if (current - lastSecond >= 1.0)
			{
				m_ImGui->GetLogger().AddLog("fps: %d\n", numberOfFrames);
				numberOfFrames = 0;
				lastSecond += 1.0f;
			}

			m_Input->OnUpdate(elapsed);
			m_CurrentScene->OnUpdate(elapsed);
			m_RenderingEngine->Render(m_CurrentScene->GetRoot(), m_CurrentScene->GetMainCamera(), m_CurrentScene->GetSkybox());
			m_ImGui->OnUpdate(elapsed);
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
		dispatcher.Dispatch<KeyPressedEvent>(FLOW_BIND_EVENT_FUNCTION(Application::OnKeyPressed));

		m_ImGui->OnEvent(e);
		m_Input->OnEvent(e);		
		m_CurrentScene->OnEvent(e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == (int)Keycode::Escape)
			m_Running = false;

		if (e.GetKeyCode() == (int)Keycode::F10)
		{
			bool receiveEvents = m_ImGui->GetReceiveEvents();
			m_Window->ShowMouse(!receiveEvents);
			m_ImGui->ToggleReceiveEvents();
		}			

		return false; // returns false because other functions should be able to receive those events as well
 	}
}
