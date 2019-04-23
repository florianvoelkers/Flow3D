#include "Scene.hpp"

namespace Flow {

	Scene::Scene(std::string name) 
		: m_Name(name), Layer("Scene")
	{
		m_Root = std::make_unique<GameObject>();
	}

	Scene::~Scene(){}

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
		// render everything after it is updated
		m_Root->Render();
	}

	void Scene::OnEvent(Event& event)
	{
		m_Root->OnEvent(event);
	}
}