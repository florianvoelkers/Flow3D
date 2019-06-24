#include "Scene.hpp"

#include "Components/ComponentClasses.cpp"
#include "ResourceManager.hpp"

// basic file operations
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

// metastuff testing
#include <MetaStuff/include/Meta.h>
#include "Person.hpp"
#include <json/json.hpp>
#include <MetaStuff/include/JsonCast.h>

Scene::Scene(std::string name, const Window& window)
	: m_Name(name), m_Window(window)
{
	// The root object will contain all objects present in one scene as it's children and their children and so on.
	m_Root = std::make_unique<GameObject>("root");
	// set a default directional light
	m_Root->AddComponent<DirectionalLight>(*m_Root, Vec3(0.0f), Vec3(0.0f), Vec3(0.0f), Vec3(0.0f));
	SetDirectionalLight(&m_Root->GetComponent<DirectionalLight>());

	// The main camera is used for rendering purposes.
	m_MainCamera = std::make_shared<GameObject>("MainCamera", Vec3(0.0f, 1.5f, 7.0f), Vec3(0.0f, 0.0f, 0.0f));
	m_MainCamera->GetTransform().ConstrainPosition(false, true, false);
	m_MainCamera->AddComponent<FreeCamera>(*m_MainCamera, m_Window);
	AddToScene(m_MainCamera);

	json transformJson = m_MainCamera->GetTransform();
	std::cout << std::setw(4) << transformJson << std::endl;

	std::ofstream myfile;
	myfile.open("camera_transform.json");
	myfile << std::setw(4) << transformJson;
	myfile.close();

	std::cout << "========================\n";

	std::cout << "Serializing Transform 2 from JSON:\n";

	auto transform2 = transformJson.get<Transform>();
	std::cout << "Transform 2 position is " << transform2.GetPosition() << " too!" << '\n';
	
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
	m_Skybox = std::make_unique<Skybox>("resources/skyboxes", "jpg", true);

	std::vector<std::shared_ptr<Texture>> textures = ResourceManager::Get().GetAllTextures();
	std::vector<std::shared_ptr<Shader>> shaders = ResourceManager::Get().GetAllShaders();
	std::vector<std::shared_ptr<Model>> models = ResourceManager::Get().GetAllModels();

	std::shared_ptr<GameObject> sun = std::make_shared<GameObject>("sun", Vec3(0.0f, 100.0f, 0.0f), Vec3(0.0f), Vec3(5.0f));
	sun->AddComponent<DirectionalLight>(*sun, Vec3(-0.2f, -1.0f, -0.3f), Vec3(0.3f), Vec3(0.7f), Vec3(0.7f));
	SetDirectionalLight(&sun->GetComponent<DirectionalLight>());
	AddToScene(sun);

	// do these need to be deleted in here or is it enough that the scenes root object will be deleted in the end?
	std::shared_ptr<GameObject> plane = std::make_shared<GameObject>("plane", Vec3(0.0f, -0.01f, 0.0f), Vec3(-90.0f, 0.0f, 0.0f), Vec3(31.0f));
	plane->AddComponent<Renderable>(*plane, std::make_shared<Model>(std::make_shared<Plane>(textures[3])), shaders.at(0));
	AddToScene(plane);

	std::shared_ptr<GameObject> firstCube = std::make_shared<GameObject>("firstCube", Vec3(0.0f, 1.5f, -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(3.0f));
	firstCube->AddComponent<Renderable>(*firstCube, std::make_shared<Model>(std::make_shared<Cube>(textures[1])), shaders.at(0));
	AddToScene(firstCube);

	std::shared_ptr<GameObject> nose = std::make_shared<GameObject>("nose", Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f), Vec3(0.1f, 1.0f, 0.1f));
	nose->AddComponent<Renderable>(*nose, std::make_shared<Model>(std::make_shared<Cube>(textures[1])), shaders.at(0));
	firstCube->AddChild(nose);

	std::shared_ptr<GameObject> cubeLamp = std::make_shared<GameObject>("cubeLamp", Vec3(0.0f, 0.42f, 0.525f), Vec3(0.0f), Vec3(0.05f));
	cubeLamp->AddComponent<Renderable>(*cubeLamp, std::make_shared<Model>(std::make_shared<Cube>(1.0f, 0.0f, 1.0f)), shaders.at(1));
	cubeLamp->AddComponent<PointLight>(*cubeLamp, Vec3(0.05f), Vec3(0.8f), Vec3(1.0f), Attenuation(1.0f, 0.09f, 0.032f));
	firstCube->AddChild(cubeLamp);
	AddPointLight(&cubeLamp->GetComponent<PointLight>());

	std::shared_ptr<GameObject> grass1 = std::make_shared<GameObject>("grass1", Vec3(-1.0f, 0.5f, 0.51f));
	grass1->AddComponent<Renderable>(*grass1, std::make_shared<Model>(std::make_shared<Plane>(textures[4])), shaders.at(0));
	AddToScene(grass1);

	std::shared_ptr<GameObject> grass2 = std::make_shared<GameObject>("grass2",Vec3(0.0f, 0.5f, 0.51f));
	grass2->AddComponent<Renderable>(*grass2, std::make_shared<Model>(std::make_shared<Plane>(textures[4])), shaders.at(0));
	AddToScene(grass2);

	std::shared_ptr<GameObject> grass3 = std::make_shared<GameObject>("grass3", Vec3(1.0f, 0.5f, 0.51f));
	grass3->AddComponent<Renderable>(*grass3, std::make_shared<Model>(std::make_shared<Plane>(textures[4])), shaders.at(0));
	AddToScene(grass3);

	std::shared_ptr<GameObject> secondCube = std::make_shared<GameObject>("secondCube", Vec3(2.5f, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	secondCube->AddComponent<Renderable>(*secondCube, std::make_shared<Model>(std::make_shared<Cube>(textures[0])), shaders.at(0));
	AddToScene(secondCube);

	std::shared_ptr<GameObject> thirdCube = std::make_shared<GameObject>("thirdCube", Vec3(-2.5f, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	thirdCube->AddComponent<Renderable>(*thirdCube, std::make_shared<Model>(std::make_shared<Cube>(textures[5], textures[6])), shaders.at(0));
	AddToScene(thirdCube);
		
	std::shared_ptr<GameObject> tree = std::make_shared<GameObject>("tree", Vec3(0.0f, 3.0f, 0.0f));
	tree->GetTransform().SetScale(Vec3(0.2f));
	tree->AddComponent<Renderable>(*tree, models[0], shaders.at(2), true);
	AddToScene(tree);

	std::shared_ptr<GameObject> emptyGO = std::make_shared<GameObject>("empty", Vec3(2.0f, 2.0f, 2.0f));
	AddToScene(emptyGO);

		
	std::shared_ptr<GameObject> oldMan = std::make_shared<GameObject>("oldMan", Vec3(0.0f, 0.0f, 2.0f));
	oldMan->GetTransform().SetScale(Vec3(0.01f));
	oldMan->GetTransform().ConstrainScale(true, true, true);
	oldMan->AddComponent<Renderable>(*oldMan, models[1], shaders.at(2), false);
	AddToScene(oldMan);

	std::shared_ptr<GameObject> spotLightLamp = std::make_shared<GameObject>("spotLightLamp", Vec3(-2.5f, 3.0f, 0.0f), Vec3(90.0f, 0.0f, 0.0f), Vec3(0.05f));
	spotLightLamp->AddComponent<Renderable>(*spotLightLamp, std::make_shared<Model>(std::make_shared<Cube>(1.0f, 0.0f, 1.0f)), shaders.at(1));
	std::shared_ptr<GameObject> spotLight = std::make_shared<GameObject>("spotLight");
	spotLightLamp->AddChild(spotLight);
	spotLight->AddComponent<SpotLight>(*spotLight, Vec3(0.0f), Vec3(1.0f), Vec3(1.0f),
		12.5f, 15.0f, Attenuation(1.0f, 0.09f, 0.032f));
	AddSpotLight(&spotLight->GetComponent<SpotLight>());
	AddToScene(spotLightLamp);

		
	std::shared_ptr<GameObject> trex = std::make_shared<GameObject>("trex", Vec3(2.5f, 0.0f, 2.0f));
	trex->GetTransform().SetScale(Vec3(0.2f));
	trex->AddComponent<Renderable>(*trex, models[2], shaders.at(2), false);
	AddToScene(trex);

	std::shared_ptr<GameObject> trex2 = std::make_shared<GameObject>("trex2", Vec3(-2.5f, 0.0f, 2.0f));
	trex2->GetTransform().SetScale(Vec3(0.2f));
	trex2->AddComponent<Rotatable>(*trex2);
	trex2->GetTransform().ConstrainRotation(true, false, false);
	trex2->AddComponent<Renderable>(*trex2, models[2], shaders.at(2), false);
	AddToScene(trex2);

		
	std::shared_ptr<GameObject> house = std::make_shared<GameObject>("house", Vec3(-7.0f, 0.0f, 7.0f), Vec3(0.0f, -90.0f, 0.0f));
	house->GetTransform().SetScale(Vec3(0.02f));
	house->AddComponent<Renderable>(*house, models[3], shaders.at(2), false);
	AddToScene(house);

		
	std::shared_ptr<GameObject> house2 = std::make_shared<GameObject>("house2", Vec3(10.0f, 0.0f, 10.0f), Vec3(0.0f, -90.0f, 0.0f));
	house2->GetTransform().SetScale(Vec3(0.008f));
	house2->AddComponent<Renderable>(*house2, models[4], shaders.at(2), false);
	AddToScene(house2);

	std::shared_ptr<GameObject> stick = std::make_shared<GameObject>("stick", Vec3(0.0f, 0.0f, -1.0f), Vec3(-45.0f, 30.0f, -30.0f), Vec3(0.1f, 0.5f, 0.1f), false);
	stick->AddComponent<Renderable>(*stick, std::make_shared<Model>(std::make_shared<Cube>(textures[3])), shaders.at(0));
	m_MainCamera->AddChild(stick);
		
	/*		
	std::shared_ptr<GameObject> sword = std::make_shared<GameObject>("sword", Vec3(0.2f, -0.1f, -0.5f), Vec3(0.0f, 90.0f, 0.0f));
	sword->GetTransform()->SetScale(Vec3(0.05f));
	sword->AddComponent<Renderable>(*sword, models[5], shaders.at(2), false);
	sword->AddComponent<ComponentToggler>(*sword, sword->GetComponent<Renderable>());
	m_MainCamera->AddChild(sword);
	*/

	// flash light for the camera		
	m_MainCamera->AddComponent<SpotLight>(*m_MainCamera, Vec3(0.0f), Vec3(1.0f), Vec3(1.0f),
		12.5f, 15.0f, Attenuation(1.0f, 0.09f, 0.032f), false);
	AddSpotLight(&m_MainCamera->GetComponent<SpotLight>());
	// add component to toggle flash light; need a better way to disabling lights
	m_MainCamera->AddComponent<GameObjectToggler>(*m_MainCamera);
	m_MainCamera->GetComponent<GameObjectToggler>().AddGameObjectToToggle(std::make_tuple(Application::Get().GetCurrentScene().FindGameObject("trex2"), 
		"trex2", Keycode::C));
	m_MainCamera->AddComponent<ComponentToggler>(*m_MainCamera);
	m_MainCamera->GetComponent<ComponentToggler>().AddComponentToToggle(std::make_tuple(&m_MainCamera->GetComponent<SpotLight>(), Keycode::B));	
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

inline GameObject* Scene::FindGameObject(std::string name)
{
	return m_Root->Find(name);
}

void Scene::SetDirectionalLight(DirectionalLight* directionalLight)
{
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