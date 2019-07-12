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

	BoundingSphere sphere1(Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	BoundingSphere sphere2(Vec3(0.0f, 3.0f, 0.0f), 1.0f);
	BoundingSphere sphere3(Vec3(0.0f, 0.0f, 2.0f), 1.0f);
	BoundingSphere sphere4(Vec3(1.0f, 0.0f, 0.0f), 1.0f);

	IntersectData sphere1IntersectSphere2 = sphere1.IntersectBoundingSphere(sphere2);
	IntersectData sphere1IntersectSphere3 = sphere1.IntersectBoundingSphere(sphere3);
	IntersectData sphere1IntersectSphere4 = sphere1.IntersectBoundingSphere(sphere4);

	std::cout << "Sphere1 intersect Sphere2: " << sphere1IntersectSphere2.GetDoesIntersect()
		<< ", Distance: " << sphere1IntersectSphere2.GetDistance() << std::endl;
	std::cout << "Sphere1 intersect Sphere3: " << sphere1IntersectSphere3.GetDoesIntersect()
		<< ", Distance: " << sphere1IntersectSphere3.GetDistance() << std::endl;
	std::cout << "Sphere1 intersect Sphere4: " << sphere1IntersectSphere4.GetDoesIntersect()
		<< ", Distance: " << sphere1IntersectSphere4.GetDistance() << std::endl;

	AABB aabb1(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
	AABB aabb2(Vec3(1.0f, 1.0f, 1.0f), Vec3(2.0f, 2.0f, 2.0f));
	AABB aabb3(Vec3(1.0f, 0.0f, 0.0f), Vec3(2.0f, 1.0f, 1.0f));
	AABB aabb4(Vec3(0.0f, 0.0f, -2.0f), Vec3(1.0f, 1.0f, -1.0f));
	AABB aabb5(Vec3(0.0f, 0.5f, 0.0f), Vec3(1.0f, 1.5f, 1.0f));

	IntersectData aabb1Intersectaabb2 = aabb1.IntersectAABB(aabb2);
	IntersectData aabb1Intersectaabb3 = aabb1.IntersectAABB(aabb3);
	IntersectData aabb1Intersectaabb4 = aabb1.IntersectAABB(aabb4);
	IntersectData aabb1Intersectaabb5 = aabb1.IntersectAABB(aabb5);

	std::cout << "AABB1 intersect AABB2: " << aabb1Intersectaabb2.GetDoesIntersect()
		<< ", Distance: " << aabb1Intersectaabb2.GetDistance() << std::endl;
	std::cout << "AABB1 intersect AABB3: " << aabb1Intersectaabb3.GetDoesIntersect()
		<< ", Distance: " << aabb1Intersectaabb3.GetDistance() << std::endl;
	std::cout << "AABB1 intersect AABB4: " << aabb1Intersectaabb4.GetDoesIntersect()
		<< ", Distance: " << aabb1Intersectaabb4.GetDistance() << std::endl;
	std::cout << "AABB1 intersect AABB5: " << aabb1Intersectaabb5.GetDoesIntersect()
		<< ", Distance: " << aabb1Intersectaabb5.GetDistance() << std::endl;

	PlaneCollider planeCollider(Vec3(0.0f, 1.0f, 0.0f), 0.0f);
	PlaneCollider plane2(Vec3(2.0f, 0.0f, 1.0f), 0.0f);
	PlaneCollider plane3(Vec3(0.0f, 1.0f, 0.0f), -2.0f);
	PlaneCollider plane4(Vec3(-1.0f, 1.0f, 2.0f), 3.0f);
	PlaneCollider plane5(Vec3(1.0f, 0.0f, 0.5f), 3.0f);

	IntersectData plane1IntersectPlane2 = planeCollider.IntersectPlane(plane2);
	IntersectData plane1IntersectPlane3 = planeCollider.IntersectPlane(plane3);
	IntersectData plane1IntersectPlane4 = planeCollider.IntersectPlane(plane4);
	IntersectData plane1IntersectPlane5 = planeCollider.IntersectPlane(plane5);

	std::cout << "Plane1 intersect Plane2: " << plane1IntersectPlane2.GetDoesIntersect()
		<< ", Distance: " << plane1IntersectPlane2.GetDistance() << std::endl;
	std::cout << "Plane1 intersect Plane3: " << plane1IntersectPlane3.GetDoesIntersect()
		<< ", Distance: " << plane1IntersectPlane3.GetDistance() << std::endl;
	std::cout << "Plane1 intersect Plane4: " << plane1IntersectPlane4.GetDoesIntersect()
		<< ", Distance: " << plane1IntersectPlane4.GetDistance() << std::endl;
	std::cout << "Plane1 intersect Plane5: " << plane1IntersectPlane5.GetDoesIntersect()
		<< ", Distance: " << plane1IntersectPlane5.GetDistance() << std::endl;

	IntersectData plane1IntersectSphere1 = planeCollider.IntersectSphere(sphere1);
	IntersectData plane1IntersectSphere2 = planeCollider.IntersectSphere(sphere2);
	IntersectData plane1IntersectSphere3 = planeCollider.IntersectSphere(sphere3);
	IntersectData plane1IntersectSphere4 = planeCollider.IntersectSphere(sphere4);

	std::cout << "Plane1 intersect Sphere1: " << plane1IntersectSphere1.GetDoesIntersect()
		<< ", Distance: " << plane1IntersectSphere1.GetDistance() << std::endl;
	std::cout << "Plane1 intersect Sphere2: " << plane1IntersectSphere2.GetDoesIntersect()
		<< ", Distance: " << plane1IntersectSphere2.GetDistance() << std::endl;
	std::cout << "Plane1 intersect Sphere3: " << plane1IntersectSphere3.GetDoesIntersect()
		<< ", Distance: " << plane1IntersectSphere3.GetDistance() << std::endl;
	std::cout << "Plane1 intersect Sphere4: " << plane1IntersectSphere4.GetDoesIntersect()
		<< ", Distance: " << plane1IntersectSphere4.GetDistance() << std::endl;

	IntersectData sphere1IntersectAABB1 = sphere1.IntersectAABB(aabb1);
	IntersectData sphere2IntersectAABB1 = sphere2.IntersectAABB(aabb1);
	IntersectData sphere3IntersectAABB1 = sphere3.IntersectAABB(aabb1);
	IntersectData sphere4IntersectAABB1 = sphere4.IntersectAABB(aabb1);

	std::cout << "Sphere1 intersect AABB1: " << sphere1IntersectAABB1.GetDoesIntersect()
		<< ", Distance: " << sphere1IntersectAABB1.GetDistance() << std::endl;
	std::cout << "Sphere2 intersect AABB1: " << sphere2IntersectAABB1.GetDoesIntersect()
		<< ", Distance: " << sphere2IntersectAABB1.GetDistance() << std::endl;
	std::cout << "Sphere3 intersect AABB1: " << sphere3IntersectAABB1.GetDoesIntersect()
		<< ", Distance: " << sphere3IntersectAABB1.GetDistance() << std::endl;
	std::cout << "Sphere4 intersect AABB1: " << sphere4IntersectAABB1.GetDoesIntersect()
		<< ", Distance: " << sphere4IntersectAABB1.GetDistance() << std::endl;

	IntersectData planeIntersectsAABB1 = planeCollider.IntersectAABB(aabb1);
	IntersectData planeIntersectsAABB2 = planeCollider.IntersectAABB(aabb2);
	IntersectData planeIntersectsAABB3 = planeCollider.IntersectAABB(aabb3);
	IntersectData planeIntersectsAABB4 = planeCollider.IntersectAABB(aabb4);
	IntersectData planeIntersectsAABB5 = planeCollider.IntersectAABB(aabb5);

	std::cout << "Plane intersect AABB1: " << planeIntersectsAABB1.GetDoesIntersect()
		<< ", Distance: " << planeIntersectsAABB1.GetDistance() << std::endl;
	std::cout << "Plane intersect AABB2: " << planeIntersectsAABB2.GetDoesIntersect()
		<< ", Distance: " << planeIntersectsAABB2.GetDistance() << std::endl;
	std::cout << "Plane intersect AABB3: " << planeIntersectsAABB3.GetDoesIntersect()
		<< ", Distance: " << planeIntersectsAABB3.GetDistance() << std::endl;
	std::cout << "Plane intersect AABB4: " << planeIntersectsAABB4.GetDoesIntersect()
		<< ", Distance: " << planeIntersectsAABB4.GetDistance() << std::endl;
	std::cout << "Plane intersect AABB5: " << planeIntersectsAABB5.GetDoesIntersect()
		<< ", Distance: " << planeIntersectsAABB5.GetDistance() << std::endl;
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

