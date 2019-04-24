#include "Scene.hpp"

namespace Flow {

	Scene::Scene(std::string name) 
		: m_Name(name), Layer("Scene")
	{
		m_Root = new GameObject();
	}

	Scene::~Scene()
	{
		delete m_Root;
	}

	void Scene::AddToScene(GameObject* gameObject)
	{
		m_Root->AddChild(gameObject);
	}

	void Scene::OnAttach()
	{

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