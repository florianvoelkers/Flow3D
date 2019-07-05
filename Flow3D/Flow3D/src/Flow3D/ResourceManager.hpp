#pragma once

#include "Rendering/Shader.hpp"
#include "Rendering/Texture.hpp"
#include "Rendering/Model.hpp"
#include "Rendering/Skybox.hpp"

enum class ResourceType {
	Shader, Texture, Model
};

class ResourceManager
{
public:

	ResourceManager();

	inline static ResourceManager& Get() { return *s_Instance; }
		
	void AddTexture(std::shared_ptr<Texture> texture) { textures.push_back(texture); }
	void RemoveTexture(int index) { textures.erase(textures.begin() + index); }
	std::shared_ptr<Texture> FindTexture(std::string path);

	void AddShader(std::shared_ptr<Shader> shader) { shaders.push_back(shader); }
	void RemoveShader(int index) { shaders.erase(shaders.begin() + index); }
	std::shared_ptr<Shader> FindShader(std::string name);

	void AddModel(std::shared_ptr<Model> model) { models.push_back(model); }
	void RemoveModel(int index) { models.erase(models.begin() + index); }
	std::shared_ptr<Model> FindModel(std::string path);

	void AddSkybox(std::shared_ptr<Skybox> skybox) { skyboxes.push_back(skybox); }
	void RemoveSkybox(int index) { skyboxes.erase(skyboxes.begin() + index); }
	std::shared_ptr<Skybox> FindSkybox(std::string name);

	void AddSceneName(std::string sceneName) { sceneNames.push_back(sceneName); }

	std::vector<std::shared_ptr<Texture>> GetAllTextures() { return textures; }
	std::vector<std::shared_ptr<Shader>> GetAllShaders() { return shaders; }
	std::vector<std::shared_ptr<Model>> GetAllModels() { return models; }
	std::vector<std::shared_ptr<Skybox>> GetAllSkyboxes() { return skyboxes; }
	std::vector<std::string> GetAllSceneNames() { return sceneNames; }
		
private:
	static ResourceManager* s_Instance;

	std::vector<std::shared_ptr<Shader>> shaders;
	std::vector<std::shared_ptr<Texture>> textures;
	std::vector<std::shared_ptr<Model>> models;
	std::vector<std::shared_ptr<Skybox>> skyboxes;
	std::vector<std::string> sceneNames; 
};