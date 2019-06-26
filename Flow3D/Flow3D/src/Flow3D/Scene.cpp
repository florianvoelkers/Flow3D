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
#include <Windows.h>

Scene::Scene(std::string name, const Window& window)
	: m_Name(name), m_Window(window)
{
	// The root object will contain all objects present in one scene as it's children and their children and so on.
	m_Root = std::make_unique<GameObject>("root");
	// set a default directional light
	m_Root->AddComponent<DirectionalLight>(m_Root.get(), Vec3(0.0f), Vec3(0.0f), Vec3(0.0f), Vec3(0.0f));
	SetDirectionalLight(&m_Root->GetComponent<DirectionalLight>());

	// The main camera is used for rendering purposes.
	m_MainCamera = std::make_shared<GameObject>("MainCamera", Vec3(0.0f, 1.5f, 7.0f), Vec3(0.0f, 0.0f, 0.0f));
	m_MainCamera->GetTransform().ConstrainPosition(false, true, false);
	m_MainCamera->AddComponent<FreeCamera>(m_MainCamera.get(), m_Window);
	AddToScene(m_MainCamera);	
	
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
	sun->AddComponent<DirectionalLight>(sun.get(), Vec3(-0.2f, -1.0f, -0.3f), Vec3(0.3f), Vec3(0.7f), Vec3(0.7f));
	SetDirectionalLight(&sun->GetComponent<DirectionalLight>());
	AddToScene(sun);

	// do these need to be deleted in here or is it enough that the scenes root object will be deleted in the end?
	std::shared_ptr<GameObject> plane = std::make_shared<GameObject>("plane", Vec3(0.0f, -0.01f, 0.0f), Vec3(-90.0f, 0.0f, 0.0f), Vec3(31.0f));
	plane->AddComponent<Renderable>(plane.get(), std::make_shared<Model>(std::make_shared<Plane>(textures[3])), shaders.at(0));
	AddToScene(plane);

	std::shared_ptr<GameObject> firstCube = std::make_shared<GameObject>("firstCube", Vec3(0.0f, 1.5f, -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(3.0f));
	firstCube->AddComponent<Renderable>(firstCube.get(), std::make_shared<Model>(std::make_shared<Cube>(textures[1])), shaders.at(0));
	AddToScene(firstCube);

	std::shared_ptr<GameObject> nose = std::make_shared<GameObject>("nose", Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f), Vec3(0.1f, 1.0f, 0.1f));
	nose->AddComponent<Renderable>(nose.get(), std::make_shared<Model>(std::make_shared<Cube>(textures[1])), shaders.at(0));
	firstCube->AddChild(nose);

	std::shared_ptr<GameObject> cubeLamp = std::make_shared<GameObject>("cubeLamp", Vec3(0.0f, 0.42f, 0.525f), Vec3(0.0f), Vec3(0.05f));
	cubeLamp->AddComponent<Renderable>(cubeLamp.get(), std::make_shared<Model>(std::make_shared<Cube>(1.0f, 0.0f, 1.0f)), shaders.at(1));
	cubeLamp->AddComponent<PointLight>(cubeLamp.get(), Vec3(0.05f), Vec3(0.8f), Vec3(1.0f), Attenuation(1.0f, 0.09f, 0.032f));
	firstCube->AddChild(cubeLamp);
	AddPointLight(&cubeLamp->GetComponent<PointLight>());

	std::shared_ptr<GameObject> grass1 = std::make_shared<GameObject>("grass1", Vec3(-1.0f, 0.5f, 0.51f));
	grass1->AddComponent<Renderable>(grass1.get(), std::make_shared<Model>(std::make_shared<Plane>(textures[4])), shaders.at(0));
	AddToScene(grass1);

	std::shared_ptr<GameObject> grass2 = std::make_shared<GameObject>("grass2",Vec3(0.0f, 0.5f, 0.51f));
	grass2->AddComponent<Renderable>(grass2.get(), std::make_shared<Model>(std::make_shared<Plane>(textures[4])), shaders.at(0));
	AddToScene(grass2);

	std::shared_ptr<GameObject> grass3 = std::make_shared<GameObject>("grass3", Vec3(1.0f, 0.5f, 0.51f));
	grass3->AddComponent<Renderable>(grass3.get(), std::make_shared<Model>(std::make_shared<Plane>(textures[4])), shaders.at(0));
	AddToScene(grass3);

	std::shared_ptr<GameObject> secondCube = std::make_shared<GameObject>("secondCube", Vec3(2.5f, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	secondCube->AddComponent<Renderable>(secondCube.get(), std::make_shared<Model>(std::make_shared<Cube>(textures[0])), shaders.at(0));
	AddToScene(secondCube);

	std::shared_ptr<GameObject> thirdCube = std::make_shared<GameObject>("thirdCube", Vec3(-2.5f, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	thirdCube->AddComponent<Renderable>(thirdCube.get(), std::make_shared<Model>(std::make_shared<Cube>(textures[5], textures[6])), shaders.at(0));
	AddToScene(thirdCube);
		
	std::shared_ptr<GameObject> tree = std::make_shared<GameObject>("tree", Vec3(0.0f, 3.0f, 0.0f));
	tree->GetTransform().SetScale(Vec3(0.2f));
	tree->AddComponent<Renderable>(tree.get(), models[0], shaders.at(2), true);
	AddToScene(tree);

	std::shared_ptr<GameObject> emptyGO = std::make_shared<GameObject>("empty", Vec3(2.0f, 2.0f, 2.0f));
	AddToScene(emptyGO);
		
	std::shared_ptr<GameObject> oldMan = std::make_shared<GameObject>("oldMan", Vec3(0.0f, 0.0f, 2.0f));
	oldMan->GetTransform().SetScale(Vec3(0.01f));
	oldMan->GetTransform().ConstrainScale(true, true, true);
	oldMan->AddComponent<Renderable>(oldMan.get(), models[1], shaders.at(2), false);
	AddToScene(oldMan);

	std::shared_ptr<GameObject> spotLightLamp = std::make_shared<GameObject>("spotLightLamp", Vec3(-2.5f, 3.0f, 0.0f), Vec3(90.0f, 0.0f, 0.0f), Vec3(0.05f));
	spotLightLamp->AddComponent<Renderable>(spotLightLamp.get(), std::make_shared<Model>(std::make_shared<Cube>(1.0f, 0.0f, 1.0f)), shaders.at(1));
	std::shared_ptr<GameObject> spotLight = std::make_shared<GameObject>("spotLight");
	spotLightLamp->AddChild(spotLight);
	spotLight->AddComponent<SpotLight>(spotLight.get(), Vec3(0.0f), Vec3(1.0f), Vec3(1.0f),
		12.5f, 15.0f, Attenuation(1.0f, 0.09f, 0.032f));
	AddSpotLight(&spotLight->GetComponent<SpotLight>());
	AddToScene(spotLightLamp);

		
	std::shared_ptr<GameObject> trex = std::make_shared<GameObject>("trex", Vec3(2.5f, 0.0f, 2.0f));
	trex->GetTransform().SetScale(Vec3(0.2f));
	trex->AddComponent<Renderable>(trex.get(), models[2], shaders.at(2), false);
	AddToScene(trex);

	std::shared_ptr<GameObject> trex2 = std::make_shared<GameObject>("trex2", Vec3(-2.5f, 0.0f, 2.0f));
	trex2->GetTransform().SetScale(Vec3(0.2f));
	trex2->AddComponent<Rotatable>(trex2.get());
	trex2->GetTransform().ConstrainRotation(true, false, false);
	trex2->AddComponent<Renderable>(trex2.get(), models[2], shaders.at(2), false);
	AddToScene(trex2);
		
	std::shared_ptr<GameObject> house = std::make_shared<GameObject>("house", Vec3(-7.0f, 0.0f, 7.0f), Vec3(0.0f, -90.0f, 0.0f));
	house->GetTransform().SetScale(Vec3(0.02f));
	house->AddComponent<Renderable>(house.get(), models[3], shaders.at(2), false);
	AddToScene(house);
		
	std::shared_ptr<GameObject> house2 = std::make_shared<GameObject>("house2", Vec3(10.0f, 0.0f, 10.0f), Vec3(0.0f, -90.0f, 0.0f));
	house2->GetTransform().SetScale(Vec3(0.008f));
	house2->AddComponent<Renderable>(house2.get(), models[4], shaders.at(2), false);
	AddToScene(house2);

	std::shared_ptr<GameObject> stick = std::make_shared<GameObject>("stick", Vec3(0.0f, 0.0f, -1.0f), Vec3(-45.0f, 30.0f, -30.0f), Vec3(0.1f, 0.5f, 0.1f), false);
	stick->AddComponent<Renderable>(stick.get(), std::make_shared<Model>(std::make_shared<Cube>(textures[3])), shaders.at(0));
	m_MainCamera->AddChild(stick);
		
	/*		
	std::shared_ptr<GameObject> sword = std::make_shared<GameObject>("sword", Vec3(0.2f, -0.1f, -0.5f), Vec3(0.0f, 90.0f, 0.0f));
	sword->GetTransform()->SetScale(Vec3(0.05f));
	sword->AddComponent<Renderable>(sword.get(), models[5], shaders.at(2), false);
	sword->AddComponent<ComponentToggler>(sword.get(), sword->GetComponent<Renderable>());
	m_MainCamera->AddChild(sword);
	*/

	// flash light for the camera		
	m_MainCamera->AddComponent<SpotLight>(m_MainCamera.get(), Vec3(0.0f), Vec3(1.0f), Vec3(1.0f),
		12.5f, 15.0f, Attenuation(1.0f, 0.09f, 0.032f), false);
	AddSpotLight(&m_MainCamera->GetComponent<SpotLight>());
	// add component to toggle flash light; need a better way to disabling lights
	m_MainCamera->AddComponent<GameObjectToggler>(m_MainCamera.get());
	m_MainCamera->GetComponent<GameObjectToggler>().AddGameObjectToToggle(std::make_tuple(Application::Get().GetCurrentScene().FindGameObject("trex2"), 
		"trex2", Keycode::C));
	m_MainCamera->AddComponent<ComponentToggler>(m_MainCamera.get());
	m_MainCamera->GetComponent<ComponentToggler>().AddComponentToToggle(std::make_tuple(&m_MainCamera->GetComponent<SpotLight>(), Keycode::B));	

	// test saving the scene after initialization
	json rootAsJSON = *m_Root.get();
	std::cout << std::setw(4) << rootAsJSON << std::endl;

	std::ofstream myfile;

	json FreeCameraJSON = m_MainCamera->GetComponent<FreeCamera>();
	myfile.open("FreeCamera.json");
	myfile << std::setw(4) << FreeCameraJSON;
	myfile.close();

	auto freeCameraCopy = FreeCameraJSON.get<FreeCamera>();
	std::cout << "freeCameraCopy zoom is " << freeCameraCopy.GetZoom() << std::endl;

	json componentTogglerJSON = m_MainCamera->GetComponent<ComponentToggler>();
	myfile.open("componentToggler.json");
	myfile << std::setw(4) << componentTogglerJSON;
	myfile.close();

	json GameObjectTogglerJSON = m_MainCamera->GetComponent<GameObjectToggler>();
	myfile.open("GameObjectToggler.json");
	myfile << std::setw(4) << GameObjectTogglerJSON;
	myfile.close();

	json SpotLightJSON = m_MainCamera->GetComponent<SpotLight>();
	myfile.open("SpotLight.json");
	myfile << std::setw(4) << SpotLightJSON;
	myfile.close();

	json PointLightJSON = cubeLamp->GetComponent<PointLight>();
	myfile.open("PointLight.json");
	myfile << std::setw(4) << PointLightJSON;
	myfile.close();

	json DirectionalLightJSON = sun->GetComponent<DirectionalLight>();
	myfile.open("DirectionalLight.json");
	myfile << std::setw(4) << DirectionalLightJSON;
	myfile.close();

	json stickRenderable = stick->GetComponent<Renderable>();
	myfile.open("stickRenderable.json");
	myfile << std::setw(4) << stickRenderable;
	myfile.close();

	json stickRenderableShader = stick->GetComponent<Renderable>().GetShader();
	myfile.open("stickRenderableShader.json");
	myfile << std::setw(4) << stickRenderableShader;
	myfile.close();

	if (stick->GetComponent<Renderable>().GetModel().GetCube() != nullptr)
	{
		json stickRenderableModelCube = *stick->GetComponent<Renderable>().GetModel().GetCube().get();
		myfile.open("stickRenderableModelCube.json");
		myfile << std::setw(4) << stickRenderableModelCube;
		myfile.close();

		if (stick->GetComponent<Renderable>().GetModel().GetCube()->GetIsTextured())
		{
			json stickRenderableDiffuseTexture = stick->GetComponent<Renderable>().GetModel().GetCube()->GetDiffuseTexture();
			myfile.open("stickRenderableDiffuseTexture.json");
			myfile << std::setw(4) << stickRenderableDiffuseTexture;
			myfile.close();

			json stickRenderableSpecularTexture = stick->GetComponent<Renderable>().GetModel().GetCube()->GetSpecularTexture();
			myfile.open("stickRenderableSpecularTexture.json");
			myfile << std::setw(4) << stickRenderableSpecularTexture;
			myfile.close();
		}
	}

	json planeRenderable = plane->GetComponent<Renderable>();
	myfile.open("planeRenderable.json");
	myfile << std::setw(4) << planeRenderable;
	myfile.close();

	json planeRenderableShader = plane->GetComponent<Renderable>().GetShader();
	myfile.open("planeRenderableShader.json");
	myfile << std::setw(4) << planeRenderableShader;
	myfile.close();

	if (plane->GetComponent<Renderable>().GetModel().GetPlane() != nullptr)
	{
		json planeRenderableModelPlane = *plane->GetComponent<Renderable>().GetModel().GetPlane().get();
		myfile.open("stickRenderableModelPlane.json");
		myfile << std::setw(4) << planeRenderableModelPlane;
		myfile.close();

		if (plane->GetComponent<Renderable>().GetModel().GetPlane()->GetIsTextured())
		{
			json planeRenderableDiffuseTexture = plane->GetComponent<Renderable>().GetModel().GetPlane()->GetDiffuseTexture();
			myfile.open("planeRenderableDiffuseTexture.json");
			myfile << std::setw(4) << planeRenderableDiffuseTexture;
			myfile.close();

			json planeRenderableSpecularTexture = plane->GetComponent<Renderable>().GetModel().GetPlane()->GetSpecularTexture();
			myfile.open("stickRenderableSpecularTexture.json");
			myfile << std::setw(4) << planeRenderableSpecularTexture;
			myfile.close();
		}
	}

	CreateDirectory("serialization", NULL);
	std::string directory = "serialization/" + m_Name;
	CreateDirectory(directory.c_str(), NULL);
	directory = directory + "/";
	std::string filename = m_Root->GetName();
	directory = directory + m_Root->GetName();
	CreateDirectory(directory.c_str(), NULL);
	filename.append(".json");
	std::string path = directory + "/" + filename;
	myfile.open(path.c_str());
	myfile << std::setw(4) << rootAsJSON;
	myfile.close();

	const std::vector<std::shared_ptr<GameObject>>& rootChildren = m_Root->GetChildren();
	SerializeChildren(rootChildren, directory, myfile);
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

void Scene::SerializeChildren(const std::vector<std::shared_ptr<GameObject>>& rootChildren, std::string directory, std::ofstream& myfile)
{
	for (unsigned int i = 0; i < rootChildren.size(); i++)
	{
		std::string newDirectory = directory + "/" + rootChildren[i]->GetName();
		CreateDirectory(newDirectory.c_str(), NULL);
		std::string filename = rootChildren[i]->GetName();
		filename.append(".json");
		std::string path = newDirectory + "/" + filename;
		myfile.open(path.c_str());
		json childAsJson = *rootChildren[i].get();
		myfile << std::setw(4) << childAsJson;
		myfile.close();

		if (rootChildren[i]->GetChildren().size())
			SerializeChildren(rootChildren[i]->GetChildren(), newDirectory, myfile);

	}
}
