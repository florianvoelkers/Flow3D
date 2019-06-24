#pragma once

// code from https://learnopengl.com/Advanced-OpenGL/Cubemaps

#include <string>
#include <vector>

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shader.hpp"
#include "Flow3D/Rendering/Texture.hpp"

class Skybox
{
public:
	Skybox(std::string skyboxDirectory, std::string filetype, bool show);
	~Skybox();

	void Draw(Mat4 view, Mat4 projection) const;

	inline const bool IsShown() const { return m_Show; }
	const void ToggleShow() { m_Show = !m_Show; }

private:
	unsigned int VAO;
	Shader* m_Shader;
	unsigned int m_CubemapTexture;
	bool m_Show;

	void SetupCube(std::string skyboxDirectory, std::string filetype);
	unsigned int LoadCubemap(std::vector<std::string> faces);

};

