#pragma once

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shader.hpp"
#include "Flow3D/Rendering/Texture.hpp"
#include "Flow3D/Color.hpp"

#include "Flow3D/Rendering/RenderingEngine.hpp"

// Constructor: Plane(float r, float g, float b, (optional) float a) or Plane(Color color)
// or Plane(Texture diffuseTexture, (optional)Texture specularTexture)
// This class will draw a plane depending on model, view and projection
// it provides several possibilites for declaration, e.g. with a texture, color or nothing
class Plane {

public:
	Plane();

	Plane(float r, float g, float b);
	Plane(float r, float g, float b, float a);
	Plane(Color color);
	Plane(std::shared_ptr<Texture> texture);
	Plane(std::shared_ptr<Texture> diffuseTexture, std::shared_ptr<Texture> specularTexture);

	~Plane();

	void Draw(Shader& shader);

	void SetIsTextured(bool isTextured);
	void SetTextureInitialized(bool textureInitialized) { m_TextureInitialized = textureInitialized; }
	void SetColor(Color color) { m_Color = color; }
	void SetDiffuseTexture(std::shared_ptr<Texture> texture) { m_DiffuseTexture = texture; }
	void SetSpecularTexture(std::shared_ptr<Texture> texture) { m_SpecularTexture = texture; }
	void SetWireframeMode(bool wireframeMode) { m_WireframeMode = wireframeMode; }

	bool GetIsTextured() { return m_IsTextured; }
	Color GetColor() { return m_Color; }
	Texture& GetDiffuseTexture() { return *m_DiffuseTexture; }
	Texture& GetSpecularTexture() { return *m_SpecularTexture; }
	bool GetTextureInitialized() { return m_TextureInitialized; }
	bool GetWireframeMode() { return m_WireframeMode; }

	bool m_IsTextured;
	Color m_Color;

private:
	unsigned int VAO;	
	std::shared_ptr<Texture> m_DiffuseTexture;
	std::shared_ptr<Texture> m_SpecularTexture;	
	bool m_TextureInitialized;
	bool m_WireframeMode;

	void SetupPlane();
};

#include <MetaStuff/include/Meta.h>

namespace meta {

	template <>
	inline auto registerMembers<Plane>()
	{
		return members(
			member("m_IsTextured", &Plane::m_IsTextured),
			member("m_Color", &Plane::m_Color)
		);
	}

} // end of namespace meta

