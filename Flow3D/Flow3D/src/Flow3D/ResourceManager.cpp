#include "ResourceManager.hpp"

ResourceManager* ResourceManager::s_Instance = nullptr;

ResourceManager::ResourceManager()
{
	// assert for making sure there is only one instance
	s_Instance = this;	
}

std::shared_ptr<Texture> ResourceManager::FindTexture(std::string path)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (path == textures[i]->path)
			return textures[i];
	}
	return nullptr;
}

std::shared_ptr<Shader> ResourceManager::FindShader(std::string name)
{
	for (unsigned int i = 0; i < shaders.size(); i++)
	{
		if (name == shaders[i]->m_Name)
			return shaders[i];
	}
	return nullptr;
}

std::shared_ptr<Model> ResourceManager::FindModel(std::string path)
{
	for (unsigned int i = 0; i < models.size(); i++)
	{
		if (path == models[i]->filepath)
			return models[i];
	}
	return nullptr;
}

std::shared_ptr<Skybox> ResourceManager::FindSkybox(std::string name)
{
	for (unsigned int i = 0; i < skyboxes.size(); i++)
	{
		if (name == skyboxes[i]->GetName())
			return skyboxes[i];
	}
	return nullptr;
}
