#include "Application.hpp"

#include "Input.hpp"
#include "Rendering/RenderingEngine.hpp"
#include "Log.hpp"
#include "Serializer.hpp"

#include "Collision/BoundingSphere.hpp"
#include "Collision/AABB.hpp"
#include "Collision/PlaneCollider.hpp"

Application* Application::s_Instance = nullptr;

Application::Application()
{
	// missing assert for making sure there is only one instance
	s_Instance = this;

	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(FLOW_BIND_EVENT_FUNCTION(Application::OnEvent));
		
	m_Input = std::make_unique<Input>();
	m_RenderingEngine = std::make_unique<RenderingEngine>(*m_Window);

	m_NextObjectID = -1;

	m_ResourceManager = std::make_unique<ResourceManager>();

	m_CurrentScene = std::make_unique<Scene>("Geisterbahn");
	m_CurrentScene->OnAttach();
	Serializer::Deserialize(*m_CurrentScene);
	Serializer::LoadSceneNames();

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

void Application::CreateAndSetNewScene(std::string name)
{
	m_CurrentScene = std::make_unique<Scene>(name);
	m_CurrentScene->OnAttach();
	Serializer::Deserialize(*m_CurrentScene);
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

int Application::GetNextObjectID()
{
	m_NextObjectID++;
	return m_NextObjectID;
}

