#include "Serializer.hpp"

#include "Flow3D/Components/FreeCamera.hpp"
#include "Flow3D/Components/GameObjectToggler.hpp"
#include "Flow3D/Components/ComponentToggler.hpp"
#include "Flow3D/Components/Lighting.hpp"
#include "Flow3D/Components/Renderable.hpp"
#include "Flow3D/Components/Rotatable.hpp"
#include "Flow3D/ResourceManager.hpp"


void Serializer::Serialize(Scene & scene)
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

void Serializer::Deserialize()
{
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
