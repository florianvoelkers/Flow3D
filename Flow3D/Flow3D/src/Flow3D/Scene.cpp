#include "Scene.hpp"

#include "ResourceManager.hpp"
#include "Components/ComponentManager.cpp"

Scene::Scene(std::string name, const Window& window)
	: m_Name(name), m_Window(window)
{
	// The root object will contain all objects present in one scene as it's children and their children and so on.
	m_Root = std::make_unique<GameObject>("root");
}

Scene::~Scene()
{	
	m_PointLights.clear();
	m_SpotLights.clear();
}

void Scene::AddToScene(std::shared_ptr<GameObject> gameObject)
{
	m_Root->AddChild(gameObject);
}

void Scene::OnAttach()
{
	//m_Skybox = std::make_unique<Skybox>("resources/skyboxes", "jpg", true);
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

GameObject* Scene::FindGameObject(std::string name)
{
	return m_Root->Find(name);
}

void Scene::SetMainCamera(GameObject* mainCamera)
{
	if (m_MainCamera != nullptr)
		m_MainCamera->GetComponent<FreeCamera>().m_IsActive = false;		

	m_MainCamera = mainCamera;
}

void Scene::SetDirectionalLight(DirectionalLight* directionalLight)
{
	if (m_DirectionalLight != nullptr)
		m_DirectionalLight->m_SetAsSceneLight = false;

	m_DirectionalLight = directionalLight;
}

void Scene::AddPointLight(PointLight* pointLight)
{
	m_PointLights.push_back(pointLight);
}

void Scene::RemovePointLight(PointLight* pointLight)
{
	m_PointLights.erase(std::remove(m_PointLights.begin(), m_PointLights.end(), pointLight));
}

void Scene::AddSpotLight(SpotLight* spotLight)
{
	m_SpotLights.push_back(spotLight);
}

void Scene::RemoveSpotLight(SpotLight* spotLight)
{
	m_SpotLights.erase(std::remove(m_SpotLights.begin(), m_SpotLights.end(), spotLight));
}
