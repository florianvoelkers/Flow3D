#include "Scene.hpp"

#include "Components/FreeCamera.hpp"
#include "Components/RenderableCube.hpp"
#include "Components/RenderablePlane.hpp"

namespace Flow {

	Scene::Scene(std::string name, const Window& window)
		: m_Name(name), m_Window(&window), Layer("Scene")
	{
		// The root object will contain all objects present in one scene as it's children and their children and so on.
		m_Root = new GameObject();

		// The main camera is used for rendering purposes.
		m_MainCamera = new GameObject(Vec3(0.0f, 1.0f, 5.0f));
		m_MainCamera->AddComponent<FreeCamera>(m_MainCamera, *m_Window);
		AddToScene(m_MainCamera);
	}

	Scene::~Scene()
	{
		delete m_Root;
		delete m_MainCamera;
	}

	void Scene::AddToScene(GameObject* gameObject)
	{
		m_Root->AddChild(gameObject);
	}

	void Scene::OnAttach()
	{
		// TODO: load scene data from file; until then manually create scene objects here
		Texture containerTexture("resources/textures/container.jpg", "diffuse");
		Texture brickTexture("resources/textures/brickwall.jpg", "diffuse");
		Texture wallTexture("resources/textures/wall.jpg", "diffuse");

		// do these need to be deleted in here or is it enough that the scenes root object will be deleted in the end?
		GameObject* plane = new GameObject(Vec3(0.0f, -0.01f, 0.0f), Vec3(90.0f, 0.0f, 0.0f), Vec3(17.0f));
		plane->AddComponent<RenderablePlane>(plane, new Plane(wallTexture));
		AddToScene(plane);

		GameObject* firstCube = new GameObject(Vec3(0.0f, 1.5f, -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(3.0f));
		firstCube->AddComponent<RenderableCube>(firstCube, new Cube(brickTexture));
		AddToScene(firstCube);

		GameObject* secondCube = new GameObject(Vec3(2.5f, 0.5f, 0.0f));
		firstCube->AddComponent<RenderableCube>(secondCube, new Cube(containerTexture));
		AddToScene(secondCube);

		GameObject* thirdCube = new GameObject(Vec3(-2.5f, 0.5f, 0.0f));
		firstCube->AddComponent<RenderableCube>(thirdCube, new Cube(containerTexture));
		AddToScene(thirdCube);
	}

	void Scene::OnDetach()
	{
	}

	void Scene::OnUpdate(double deltaTime)
	{
		m_Root->OnUpdate(deltaTime);
	}

	void Scene::OnEvent(Event& event)
	{
		m_Root->OnEvent(event);
	}
}