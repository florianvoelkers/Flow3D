#include "Scene.hpp"

#include "Components/FreeCamera.hpp"
#include "Components/RenderableCube.hpp"
#include "Components/RenderablePlane.hpp"
#include "Components/Renderable.hpp"
#include "Components/Lighting.hpp"

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
		delete m_Skybox;
		delete m_MainCamera;
		delete m_Root;		
	}

	void Scene::AddToScene(GameObject* gameObject)
	{
		m_Root->AddChild(gameObject);
	}

	void Scene::OnAttach()
	{
		m_Skybox = new Skybox("resources/skyboxes", "jpg");

		// TODO: load scene data from file; until then manually create scene objects here
		Texture containerTexture("resources/textures/container.jpg", "diffuse", true);
		Texture brickTexture("resources/textures/brickwall.jpg", "diffuse", true);
		Texture wallTexture("resources/textures/wall.jpg", "diffuse", true);
		Texture metalFloorTexture("resources/textures/metal.png", "diffuse", true);
		Texture grassTexture("resources/textures/grass.png", "diffuse", true);
		Texture container2Diffuse("resources/textures/container2.png", "diffuse", true);
		Texture container2Specular("resources/textures/container2_specular.png", "specular", true);

		Shader* modelShader = new Shader("resources/shader/Standard.vert", "resources/shader/Standard.frag");

		// do these need to be deleted in here or is it enough that the scenes root object will be deleted in the end?
		GameObject* plane = new GameObject(Vec3(0.0f, -0.01f, 0.0f), Vec3(-90.0f, 0.0f, 0.0f), Vec3(31.0f));
		plane->AddComponent<RenderablePlane>(plane, new Plane(metalFloorTexture));
		AddToScene(plane);

		GameObject* firstCube = new GameObject(Vec3(0.0f, 1.5f, -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(3.0f));
		firstCube->AddComponent<RenderableCube>(firstCube, new Cube(brickTexture));
		AddToScene(firstCube);

		GameObject* grass1 = new GameObject(Vec3(-1.0f, 0.5f, 0.51f));
		grass1->AddComponent<RenderablePlane>(grass1, new Plane(grassTexture));
		AddToScene(grass1);

		GameObject* grass2 = new GameObject(Vec3(0.0f, 0.5f, 0.51f));
		grass1->AddComponent<RenderablePlane>(grass2, new Plane(grassTexture));
		AddToScene(grass2);

		GameObject* grass3 = new GameObject(Vec3(1.0f, 0.5f, 0.51f));
		grass1->AddComponent<RenderablePlane>(grass3, new Plane(grassTexture));
		AddToScene(grass3);

		GameObject* secondCube = new GameObject(Vec3(2.5f, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		firstCube->AddComponent<RenderableCube>(secondCube, new Cube(containerTexture));
		AddToScene(secondCube);

		GameObject* thirdCube = new GameObject(Vec3(-2.5f, 0.5f, 0.0f));
		firstCube->AddComponent<RenderableCube>(thirdCube, new Cube(container2Diffuse, container2Specular));
		AddToScene(thirdCube);

		Model* treeModel = new Model("resources/models/Tree/Tree.obj");
		GameObject* tree = new GameObject(Vec3(0.0f, 3.0f, 0.0f));
		tree->GetTransform()->SetScale(Vec3(0.2f));
		tree->AddComponent<Renderable>(tree, treeModel, modelShader, true);
		AddToScene(tree);

		Model* oldManModel = new Model("resources/models/man/muro.obj");
		GameObject* oldMan = new GameObject(Vec3(0.0f, 0.0f, 2.0f));
		oldMan->GetTransform()->SetScale(Vec3(0.01f));
		oldMan->AddComponent<Renderable>(oldMan, oldManModel, modelShader, false);
		AddToScene(oldMan);

		GameObject* spotLight = new GameObject(Vec3(-2.5f, 3.0f, 0.0f), Vec3(0.0f), Vec3(0.05f));
		spotLight->AddComponent<RenderableCube>(spotLight, new Cube(1.0f, 1.0f, 1.0f));
		spotLight->AddComponent<SpotLight>(spotLight, Vec3(0.0f), Vec3(1.0f), Vec3(1.0f), DIRECTIONS::down,
			glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)), Attenuation(1.0f, 0.09f, 0.032f));
		AddSpotLight(&spotLight->GetComponent<SpotLight>());
		AddToScene(spotLight);

		Model* trexModel = new Model("resources/models/trex/trex.fbx");
		GameObject* trex = new GameObject(Vec3(2.5f, 0.0f, 2.0f), Vec3(0.0f, -90.0f, 0.0f));
		trex->GetTransform()->SetScale(Vec3(0.2f));
		trex->AddComponent<Renderable>(trex, trexModel, modelShader, false);
		AddToScene(trex);

		GameObject* trex2 = new GameObject(Vec3(-2.5f, 0.0f, 2.0f), Vec3(0.0f, 90.0f, 0.0f));
		trex2->GetTransform()->SetScale(Vec3(0.2f));
		trex2->AddComponent<Renderable>(trex2, trexModel, modelShader, false);
		AddToScene(trex2);

		Model* houseModel = new Model("resources/models/old_house/house.obj");
		GameObject* house = new GameObject(Vec3(-7.0f, 0.0f, 7.0f), Vec3(0.0f, -90.0f, 0.0f));
		house->GetTransform()->SetScale(Vec3(0.02f));
		house->AddComponent<Renderable>(house, houseModel, modelShader, false);
		AddToScene(house);

		Model* houseModel2 = new Model("resources/models/house/house.obj");
		GameObject* house2 = new GameObject(Vec3(10.0f, 0.0f, 10.0f), Vec3(0.0f, -90.0f, 0.0f));
		house2->GetTransform()->SetScale(Vec3(0.008f));
		house2->AddComponent<Renderable>(house2, houseModel2, modelShader, false);
		AddToScene(house2);

		GameObject* cubeLamp = new GameObject(Vec3(0.0f, 2.75f, 0.625f), Vec3(0.0f), Vec3(0.05f));
		cubeLamp->AddComponent<RenderableCube>(cubeLamp, new Cube(1.0f, 1.0f, 1.0f));
		cubeLamp->AddComponent<PointLight>(cubeLamp, Vec3(0.05f), Vec3(0.8f), Vec3(1.0f), Attenuation(1.0f, 0.09f, 0.032f));
		AddPointLight(&cubeLamp->GetComponent<PointLight>());
		AddToScene(cubeLamp);

		GameObject* sun = new GameObject(Vec3(0.0f, 100.0f, 0.0f), Vec3(0.0f), Vec3(5.0f));
		sun->AddComponent<RenderableCube>(sun, new Cube(0.9765f, 0.8431f, 0.1098f));
		sun->AddComponent<DirectionalLight>(sun, Vec3(-0.2f, -1.0f, -0.3f), Vec3(0.1f), Vec3(0.3f), Vec3(0.3f));
		SetDirectionalLight(&sun->GetComponent<DirectionalLight>());
		AddToScene(sun);

		Model* swordModel = new Model("resources/models/sword/Sword.obj");
		GameObject* sword = new GameObject(Vec3(0.2f, -0.1f, -0.5f), Vec3(0.0f, 90.0f, -42.0f));
		sword->GetTransform()->SetScale(Vec3(0.05f));
		sword->AddComponent<Renderable>(sword, swordModel, modelShader, false);
		m_MainCamera->AddChild(sword);

		// flash light for the camera		
		m_MainCamera->AddComponent<SpotLight>(m_MainCamera, Vec3(0.0f), Vec3(1.0f), Vec3(1.0f), DIRECTIONS::front,
			glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)), Attenuation(1.0f, 0.09f, 0.032f));
		AddSpotLight(&m_MainCamera->GetComponent<SpotLight>());
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

}