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
	Skybox(std::string skyboxDirectory, std::string filetype, std::string name, bool show);
	~Skybox();

	void Draw(Mat4 view, Mat4 projection) const;

	inline const bool IsShown() const { return m_Show; }
	void SetShown(bool shown) { m_Show = shown; }
	const void ToggleShow() { m_Show = !m_Show; }

	inline const std::string GetName() const { return m_Name; }
	inline const std::string GetDirectory() const { return m_Directory; }
	inline const std::string GetFiletype() const { return m_Filetype; }

	bool m_Show;
	std::string m_Name;
	std::string m_Directory;
	std::string m_Filetype;

private:
	unsigned int VAO;
	Shader* m_Shader;
	unsigned int m_CubemapTexture;	

	void SetupCube(std::string skyboxDirectory, std::string filetype);
	unsigned int LoadCubemap(std::vector<std::string> faces);

};

