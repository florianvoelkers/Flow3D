#include "Serializer.hpp"

#include "Flow3D/Components/FreeCamera.hpp"
#include "Flow3D/Components/GameObjectToggler.hpp"
#include "Flow3D/Components/ComponentToggler.hpp"
#include "Flow3D/Components/Lighting.hpp"
#include "Flow3D/Components/Renderable.hpp"
#include "Flow3D/Components/Rotatable.hpp"
#include "Flow3D/ResourceManager.hpp"

#include <io.h>     // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <filesystem>


void Serializer::Serialize(Scene& scene)
{
	GameObject& rootObject = scene.GetRoot();
	json rootAsJSON = rootObject;

	std::ofstream myfile;

	CreateDirectory("serialization", NULL);
	std::string directory = "serialization/" + scene.GetName();
	CreateDirectory(directory.c_str(), NULL);
	directory = directory + "/";
	std::string filename = rootObject.GetName();
	directory = directory + filename;
	CreateDirectory(directory.c_str(), NULL);
	filename.append(".json");
	std::string path = directory + "/" + filename;
	myfile.open(path.c_str());
	myfile << std::setw(4) << rootAsJSON;
	myfile.close();

	const std::vector<std::shared_ptr<GameObject>>& rootChildren = rootObject.GetChildren();
	SerializeChildren(rootChildren, directory, myfile);
}

void Serializer::Deserialize(Scene& scene)
{
	std::string sceneName = scene.GetName();
	std::string serializationDirectory = "serialization\\" + sceneName;
	GameObject& root = scene.GetRoot();
	if (std::experimental::filesystem::exists(serializationDirectory.c_str()))
	{		
		std::string rootDirectory = serializationDirectory + "\\root";
		if (std::experimental::filesystem::exists(rootDirectory.c_str()))
		{
			std::vector<const char*> allComponentNames = Application::Get().GetAllComponentNames();
			// find the children of the root object -> all GameObjects in the scene
			std::vector<std::string> rootDirectories = get_directories(rootDirectory);
			for (unsigned int i = 0; i < rootDirectories[i].size(); i++)
			{
				std::size_t lastBackSlashPosition = rootDirectories[i].find_last_of("\\");
				std::string gameObjectName = rootDirectories[i].substr(lastBackSlashPosition + 1);
				
				// load json of the GameObject
				std::string filepath = rootDirectories[i] + "\\" + gameObjectName + ".json";
				std::ifstream gameObjectFile(filepath);
				json gameObjectJson;
				gameObjectFile >> gameObjectJson;
				
				// Create GameObject and add it to root
				auto gameObjectFromJson = gameObjectJson.get<GameObject>();
				std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(gameObjectFromJson.m_Name, 
					gameObjectFromJson.m_Transform.m_Position, gameObjectFromJson.m_Transform.m_Orientation, 
					gameObjectFromJson.m_Transform.m_Scale, gameObjectFromJson.m_IsActive);
				gameObject->GetTransform().SetIsCamera(gameObjectFromJson.m_Transform.GetIsCamera());
				gameObject->GetTransform().ConstrainPosition(gameObjectFromJson.m_Transform.constrainPositionX, gameObjectFromJson.m_Transform.constrainPositionY,
					gameObjectFromJson.m_Transform.constrainPositionZ);
				gameObject->GetTransform().ConstrainRotation(gameObjectFromJson.m_Transform.constrainRotationX, gameObjectFromJson.m_Transform.constrainRotationY,
					gameObjectFromJson.m_Transform.constrainRotationZ);
				gameObject->GetTransform().ConstrainScale(gameObjectFromJson.m_Transform.constrainScaleX, gameObjectFromJson.m_Transform.constrainScaleY,
					gameObjectFromJson.m_Transform.constrainScaleZ);
				root.AddChild(gameObject);

				// Check for components and add them to the GameObject
				std::string componentsDirectory = rootDirectories[i] + "\\" + gameObjectName + "_components";
				if (std::experimental::filesystem::exists(componentsDirectory.c_str()))
				{
					for (unsigned int j = 0; j < allComponentNames.size(); j++)
					{
						std::string componentFilepath = componentsDirectory + "\\" + allComponentNames[j] + ".json";
						if (std::experimental::filesystem::exists(componentFilepath))
						{
							// maybe check if the file is empty?
							std::ifstream componentFile(componentFilepath);
							json componentAsJson;
							componentFile >> componentAsJson;
							
							/*
							if (allComponentNames[j] == "Rotatable")
							{
								
								auto rotatable = componentAsJson.get<Rotatable>();
								gameObject->AddComponent<Rotatable>(gameObject.get(), rotatable.GetEnabled());
								
							}*/
							if (allComponentNames[j] == "FreeCamera")
							{
								/*
								auto freeCamera = componentAsJson.get<FreeCamera>();
								gameObject->AddComponent<FreeCamera>(gameObject.get(), Application::Get().GetWindow(), freeCamera.GetEnabled());
								FreeCamera freeCameraComponent = gameObject->GetComponent<FreeCamera>();
								freeCameraComponent.SetMovementSpeed(freeCamera.GetMovementSpeed());
								freeCameraComponent.SetMouseSensitivity(freeCamera.GetMouseSensitivity());
								freeCameraComponent.SetZoom(freeCamera.GetZoom());
								freeCameraComponent.SetZNear(freeCamera.GetZNear());
								freeCameraComponent.SetZFar(freeCamera.GetZFar());
								*/
							}
							else if (allComponentNames[j] == "Renderable")
							{
								auto renderable = componentAsJson.get<Renderable>();
								unsigned int shaderID = GetShaderID(componentsDirectory);
								if (shaderID == 0)
								{
									FLOW_CORE_ERROR("Shader not found");
									break;
								}
								std::string modelFilepath = GetModelFilepath(componentsDirectory);
								if (modelFilepath.empty())
								{
									// is cube or plane or error
									std::string cubeDirectory = componentsDirectory + "\\Model\\Cube";
									std::string planeDirectory = componentsDirectory + "\\Model\\Plane";
									if (std::experimental::filesystem::exists(cubeDirectory))
									{
										std::string cubePath = cubeDirectory + "\\cube.json";
										std::ifstream cubeFile(cubePath);
										json cubeAsJson;
										cubeFile >> cubeAsJson;
										auto cube = cubeAsJson.get<Cube>();
										if (cube.GetIsTextured())
										{
											// Get the textures
											std::string texturesDirectory = cubeDirectory + "\\Textures";
											unsigned int diffuseTextureID;
											unsigned int specularTextureID;
											if (std::experimental::filesystem::exists(texturesDirectory))
											{
												diffuseTextureID = GetTextureID(texturesDirectory, "diffuse");
												specularTextureID = GetTextureID(texturesDirectory, "specular");
											}
											else
											{
												FLOW_CORE_ERROR("no textures found");
												break;
											}

											gameObject->AddComponent<Renderable>(gameObject.get(),
												std::make_shared<Model>(std::make_shared<Cube>(ResourceManager::Get().FindTexture(diffuseTextureID),
													ResourceManager::Get().FindTexture(specularTextureID))),
												ResourceManager::Get().FindShader(shaderID), renderable.GetBlending(), renderable.GetEnabled());
										}
										else
										{
											gameObject->AddComponent<Renderable>(gameObject.get(),
												std::make_shared<Model>(std::make_shared<Cube>(cube.GetColor())), ResourceManager::Get().FindShader(shaderID),
												renderable.GetBlending(), renderable.GetEnabled());
										}
									}
									else if (std::experimental::filesystem::exists(planeDirectory))
									{
										std::string planePath = planeDirectory + "\\plane.json";
										std::ifstream planeFile(planePath);
										json planeAsJson;
										planeFile >> planeAsJson;
										auto plane = planeAsJson.get<Plane>();
										if (plane.GetIsTextured())
										{
											// Get the textures
											std::string texturesDirectory = planeDirectory + "\\Textures";
											unsigned int diffuseTextureID;
											unsigned int specularTextureID;
											if (std::experimental::filesystem::exists(texturesDirectory))
											{
												diffuseTextureID = GetTextureID(texturesDirectory, "diffuse");
												specularTextureID = GetTextureID(texturesDirectory, "specular");
											}
											else
											{
												FLOW_CORE_ERROR("no textures found");
												break;
											}

											gameObject->AddComponent<Renderable>(gameObject.get(), 
												std::make_shared<Model>(std::make_shared<Plane>(ResourceManager::Get().FindTexture(diffuseTextureID),
													ResourceManager::Get().FindTexture(specularTextureID))), 
												ResourceManager::Get().FindShader(shaderID), renderable.GetBlending(), renderable.GetEnabled());
										}
										else
										{
											gameObject->AddComponent<Renderable>(gameObject.get(), 
												std::make_shared<Model>(std::make_shared<Plane>(plane.GetColor())), ResourceManager::Get().FindShader(shaderID),
												renderable.GetBlending(), renderable.GetEnabled());
										}
									}
									else
										FLOW_CORE_ERROR("Model not found");
								}
								else
								{
									gameObject->AddComponent<Renderable>(gameObject.get(), ResourceManager::Get().FindModel(modelFilepath), 
										ResourceManager::Get().FindShader(shaderID), renderable.GetBlending(), renderable.GetEnabled());
								}								
							}
							else if (allComponentNames[j] == "DirectionalLight")
							{
								auto directionalLight = componentAsJson.get<DirectionalLight>();
								gameObject->AddComponent<DirectionalLight>(gameObject.get(), directionalLight.m_Direction,
									directionalLight.m_Ambient, directionalLight.m_Diffuse, directionalLight.m_Specular, directionalLight.GetEnabled());
								scene.SetDirectionalLight(&gameObject->GetComponent<DirectionalLight>());
							}
							else if (allComponentNames[j] == "PointLight")
							{
								auto pointLight = componentAsJson.get<PointLight>();
								gameObject->AddComponent<PointLight>(gameObject.get(), pointLight.m_Ambient, pointLight.m_Diffuse, pointLight.m_Specular,
									pointLight.GetAttenuation(), pointLight.GetEnabled());
								scene.AddPointLight(&gameObject->GetComponent<PointLight>());
							}
							else if (allComponentNames[j] == "SpotLight")
							{							
								auto spotLight = componentAsJson.get<SpotLight>();
								gameObject->AddComponent<SpotLight>(gameObject.get(), spotLight.m_Ambient, spotLight.m_Diffuse, spotLight.m_Specular,
									spotLight.m_Cutoff, spotLight.m_OuterCutoff, spotLight.GetAttenuation(), spotLight.GetEnabled());
								scene.AddSpotLight(&gameObject->GetComponent<SpotLight>());								
							}								
							else if (allComponentNames[j] == "ComponentToggler")
							{
								auto componentToggler = componentAsJson.get<ComponentToggler>();
								gameObject->AddComponent<ComponentToggler>(gameObject.get(), componentToggler.GetEnabled());
								gameObject->GetComponent<ComponentToggler>().componentsToToggle = componentToggler.componentsToToggle;
							}
							else if (allComponentNames[j] == "GameObjectToggler")
							{
								auto gameObjectToggler = componentAsJson.get<GameObjectToggler>();
								gameObject->AddComponent<GameObjectToggler>(gameObject.get(), gameObjectToggler.GetEnabled());
								gameObject->GetComponent<GameObjectToggler>().gameObjectsToToggle = gameObjectToggler.gameObjectsToToggle;
							}
						}
					}
				}

				// after all components are added the ComponentToggler needs to add its entries
				ComponentToggler& componentToggler = gameObject->GetComponent<ComponentToggler>();
				if (&componentToggler != nullptr)
				{					
					std::vector<std::tuple<std::string, int>>& componentsToToggle = componentToggler.componentsToToggle;

					const std::vector<std::shared_ptr<Component>>& components = gameObject->GetComponents();
					std::vector<std::string> componentNames;
					for (unsigned int j = 0; j < components.size(); j++)
					{
						Component& component = *components[j];
						std::string componentName = component.GetName();
						componentNames.push_back(componentName);
					}

					for (unsigned int j = 0; j < componentsToToggle.size(); j++)
					{
						std::string componentName = std::get<0>(componentsToToggle[j]);
						Keycode keycode = static_cast<Keycode>(std::get<1>(componentsToToggle[j]));

						for (unsigned int k = 0; k < componentNames.size(); k++)
						{
							if (componentName == componentNames[k])
								componentToggler.AddComponentToToggle(std::make_tuple(components[k].get(), keycode), true);
						}
					}
					
				}
				
				

				// recursively for children, create them and add them to the GameObject
			}	

			// after all GameObjects are created the GameObjectToggler needs to add its entries
		}
	}
}

void Serializer::SerializeChildren(const std::vector<std::shared_ptr<GameObject>>& rootChildren, std::string directory, std::ofstream & myfile)
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

		// Serialize all components of the GameObject
		const std::vector<std::shared_ptr<Component>>& components = rootChildren[i]->GetComponents();
		FLOW_CORE_INFO("name of the go is {0}", rootChildren[i]->GetName());
		std::string componentDirectory = newDirectory + "/" + rootChildren[i]->GetName() + "_components";
		if (components.size() > 0)
			CreateDirectory(componentDirectory.c_str(), NULL);

		for (unsigned int j = 0; j < components.size(); j++)
		{
			const std::string componentName = components[j]->GetName();
			std::string componentFileName = componentName;
			componentFileName.append(".json");
			std::string componentPath = componentDirectory + "/" + componentFileName;
			myfile.open(componentPath.c_str());

			if (componentName == "FreeCamera")
			{
				json componentAsJson = *dynamic_cast<FreeCamera*>(components[j].get());
				myfile << std::setw(4) << componentAsJson;
				myfile.close();
			}
			else if (componentName == "GameObjectToggler")
			{
				json componentAsJson = *dynamic_cast<GameObjectToggler*>(components[j].get());
				myfile << std::setw(4) << componentAsJson;
				myfile.close();
			}
			else if (componentName == "ComponentToggler")
			{
				json componentAsJson = *dynamic_cast<ComponentToggler*>(components[j].get());
				myfile << std::setw(4) << componentAsJson;
				myfile.close();
			}
			else if (componentName == "DirectionalLight")
			{
				json componentAsJson = *dynamic_cast<DirectionalLight*>(components[j].get());
				myfile << std::setw(4) << componentAsJson;
				myfile.close();
			}
			else if (componentName == "PointLight")
			{
				json componentAsJson = *dynamic_cast<PointLight*>(components[j].get());
				myfile << std::setw(4) << componentAsJson;
				myfile.close();
			}
			else if (componentName == "SpotLight")
			{
				json componentAsJson = *dynamic_cast<SpotLight*>(components[j].get());
				myfile << std::setw(4) << componentAsJson;
				myfile.close();
			}
			else if (componentName == "Renderable")
			{
				Renderable& renderableComponent = *dynamic_cast<Renderable*>(components[j].get());
				json componentAsJson = renderableComponent;
				myfile << std::setw(4) << componentAsJson;
				myfile.close();

				std::string shaderDirectory = componentDirectory + "/Shader";
				CreateDirectory(shaderDirectory.c_str(), NULL);
				std::string shaderPath = shaderDirectory + "/shader.json";
				myfile.open(shaderPath.c_str());
				json shaderAsJson = renderableComponent.GetShader();
				myfile << std::setw(4) << shaderAsJson;
				myfile.close();

				std::string modelDirectory = componentDirectory + "/Model";
				CreateDirectory(modelDirectory.c_str(), NULL);
				std::string modelPath = modelDirectory + "/model.json";
				myfile.open(modelPath.c_str());
				Model& model = renderableComponent.GetModel();
				json modelAsJson = model;
				myfile << std::setw(4) << modelAsJson;
				myfile.close();

				if (model.GetCube() != nullptr)
				{
					std::string cubeDirectory = modelDirectory + "/Cube";
					CreateDirectory(cubeDirectory.c_str(), NULL);
					std::string cubePath = cubeDirectory + "/cube.json";
					Cube& cube = *model.GetCube().get();
					json cubeAsJson = cube;
					myfile.open(cubePath.c_str());
					myfile << std::setw(4) << cubeAsJson;
					myfile.close();

					if (cube.GetIsTextured())
					{
						std::string texturesDirectory = cubeDirectory + "/Textures";
						CreateDirectory(texturesDirectory.c_str(), NULL);

						std::string diffuseTexturePath = texturesDirectory + "/diffuse.json";
						json diffuseAsJson = cube.GetDiffuseTexture();
						myfile.open(diffuseTexturePath);
						myfile << std::setw(4) << diffuseAsJson;
						myfile.close();

						std::string specularTexturePath = texturesDirectory + "/specular.json";
						json specularAsJson = cube.GetSpecularTexture();
						myfile.open(specularTexturePath);
						myfile << std::setw(4) << specularAsJson;
						myfile.close();
					}
				}
				else if (model.GetPlane() != nullptr)
				{
					std::string planeDirectory = modelDirectory + "/Plane";
					CreateDirectory(planeDirectory.c_str(), NULL);
					std::string planePath = planeDirectory + "/plane.json";
					Plane& plane = *model.GetPlane().get();
					json planeAsJson = plane;
					myfile.open(planePath.c_str());
					myfile << std::setw(4) << planeAsJson;
					myfile.close();

					if (plane.GetIsTextured())
					{
						std::string texturesDirectory = planeDirectory + "/Textures";
						CreateDirectory(texturesDirectory.c_str(), NULL);

						std::string diffuseTexturePath = texturesDirectory + "/diffuse.json";
						json diffuseAsJson = plane.GetDiffuseTexture();
						myfile.open(diffuseTexturePath);
						myfile << std::setw(4) << diffuseAsJson;
						myfile.close();

						std::string specularTexturePath = texturesDirectory + "/specular.json";
						json specularAsJson = plane.GetSpecularTexture();
						myfile.open(specularTexturePath);
						myfile << std::setw(4) << specularAsJson;
						myfile.close();
					}
				}
			}
		}

		if (rootChildren[i]->GetChildren().size() > 0)
			SerializeChildren(rootChildren[i]->GetChildren(), newDirectory, myfile);
	}
}

std::vector<std::string> Serializer::get_directories(const std::string & s)
{
	std::vector<std::string> r;
	for (auto& p : std::experimental::filesystem::recursive_directory_iterator(s))
		if (p.status().type() == std::experimental::filesystem::file_type::directory)
			r.push_back(p.path().string());

	std::vector<std::string> directSubDirectories;
	for (unsigned int i = 0; i < r.size(); i++)
	{
		std::size_t sizeOfCurrentDirectoryName = s.size();
		std::size_t stringPosition = r[i].find(s);
		std::size_t slashAfterRoot = r[i].find("\\", stringPosition + sizeOfCurrentDirectoryName + 2); // +2 because of the backslash and the offest
		if (static_cast<int>(slashAfterRoot) < 0)
			directSubDirectories.push_back(r[i]);
	}
	return directSubDirectories;
}

unsigned int Serializer::GetShaderID(const std::string& componentsDirectory)
{
	// get shader
	std::string shaderDirectory = componentsDirectory + "\\Shader";
	if (std::experimental::filesystem::exists(shaderDirectory))
	{
		std::string shaderPath = shaderDirectory + "\\Shader.json";
		if (std::experimental::filesystem::exists(shaderPath))
		{
			std::ifstream shaderFile(shaderPath);
			json shaderAsJson;
			shaderFile >> shaderAsJson;
			auto shader = shaderAsJson.get<Shader>();
			return shader.m_ID;
		}
	}
	return 0;
}

std::string Serializer::GetModelFilepath(const std::string & componentsDirectory)
{
	// Get Model
	std::string modelDirectory = componentsDirectory + "\\Model";
	if (std::experimental::filesystem::exists(modelDirectory))
	{
		std::string modelPath = modelDirectory + "\\model.json";
		if (std::experimental::filesystem::exists(modelPath))
		{
			std::ifstream modelFile(modelPath);
			json modelAsJson;
			modelFile >> modelAsJson;
			auto model = modelAsJson.get<Model>();
			return model.filepath;
		}
	}
	return "";
}

unsigned int Serializer::GetTextureID(const std::string& texturesDirectory, const std::string& type)
{
	std::string texturePath = texturesDirectory + "\\" + type + ".json";
	if (std::experimental::filesystem::exists(texturePath))
	{
		std::ifstream textureFile(texturePath);
		json textureAsJson;
		textureFile >> textureAsJson;
		auto texture = textureAsJson.get<Texture>();
		return texture.id;
	}

	return 0;
}
