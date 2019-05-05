#pragma once

// code from https://learnopengl.com/Advanced-OpenGL/Cubemaps

#include <string>
#include <vector>

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shader.hpp"
#include "Flow3D/Rendering/Texture.hpp"

namespace Flow {

	class Skybox
	{
	public:
		Skybox(std::string skyboxDirectory, std::string filetype);
		~Skybox();

		void Draw(Mat4 view, Mat4 projection) const;
	private:
		unsigned int VAO;
		Shader* m_Shader;
		unsigned int m_CubemapTexture;

		void SetupCube(std::string skyboxDirectory, std::string filetype);
		unsigned int LoadCubemap(std::vector<std::string> faces);

	};
}
