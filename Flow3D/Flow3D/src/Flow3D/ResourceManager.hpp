#pragma once

#include "Rendering/Shader.hpp"
#include "Rendering/Texture.hpp"
#include "Rendering/Model.hpp"

namespace Flow {

	enum class ResourceType {
		Shader, Texture, Model
	};

	class ResourceManager
	{
	public:

		ResourceManager();;

		inline static ResourceManager& Get() { return *s_Instance; }
		
		void AddTexture(std::shared_ptr<Texture> texture) { textures.push_back(texture); }
		void RemoveTexture(int index) { textures.erase(textures.begin() + index); }

		void AddShader(std::shared_ptr<Shader> shader) { shaders.push_back(shader); }
		void RemoveShader(int index) { shaders.erase(shaders.begin() + index); }

		void AddModel(std::shared_ptr<Model> model) { models.push_back(model); }
		void RemoveModel(int index) { models.erase(models.begin() + index); }

		std::vector<std::shared_ptr<Texture>> GetAllTextures() { return textures; }
		std::vector<std::shared_ptr<Shader>> GetAllShaders() { return shaders; }
		std::vector<std::shared_ptr<Model>> GetAllModels() { return models; }
		
	private:
		static ResourceManager* s_Instance;

		std::vector<std::shared_ptr<Shader>> shaders;
		std::vector<std::shared_ptr<Texture>> textures;
		std::vector<std::shared_ptr<Model>> models;
	};
}