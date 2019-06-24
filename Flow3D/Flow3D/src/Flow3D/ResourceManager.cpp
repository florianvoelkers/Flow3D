#include "ResourceManager.hpp"

ResourceManager* ResourceManager::s_Instance = nullptr;

ResourceManager::ResourceManager()
{
	// assert for making sure there is only one instance
	s_Instance = this;

	// TODO: load scene data from file; until then manually create scene objects here
	textures.push_back(std::make_shared<Texture>("resources/textures/container.jpg", "diffuse", true));					// 0
	textures.push_back(std::make_shared<Texture>("resources/textures/brickwall.jpg", "diffuse", true));					// 1
	textures.push_back(std::make_shared<Texture>("resources/textures/wall.jpg", "diffuse", true));						// 2
	textures.push_back(std::make_shared<Texture>("resources/textures/metal.png", "diffuse", true));						// 3
	textures.push_back(std::make_shared<Texture>("resources/textures/grass.png", "diffuse", true));						// 4
	textures.push_back(std::make_shared<Texture>("resources/textures/container2.png", "diffuse", true));				// 5
	textures.push_back(std::make_shared<Texture>("resources/textures/container2_specular.png", "specular", true));		// 6		

	shaders.push_back(std::make_shared<Shader>("resources/shader/Standard.vert", "resources/shader/Standard.frag", "Standard"));
	shaders.push_back(std::make_shared<Shader>("resources/shader/Basic3D.vert", "resources/shader/Colored.frag", "Colored"));
	shaders.push_back(std::make_shared<Shader>("resources/shader/Standard.vert", "resources/shader/Standard.frag", "Models"));

	models.push_back(std::make_shared<Model>("resources/models/Tree/Tree.obj"));
	models.push_back(std::make_shared<Model>("resources/models/man/muro.obj"));
	models.push_back(std::make_shared<Model>("resources/models/trex/trex.fbx"));
	models.push_back(std::make_shared<Model>("resources/models/old_house/house.obj"));
	models.push_back(std::make_shared<Model>("resources/models/house/house.obj"));
	models.push_back(std::make_shared<Model>("resources/models/sword/Sword.obj"));
}