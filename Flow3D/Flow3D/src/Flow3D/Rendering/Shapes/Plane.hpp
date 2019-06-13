#pragma once

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shader.hpp"
#include "Flow3D/Rendering/Texture.hpp"
#include "Flow3D/Color.hpp"

#include "Flow3D/Rendering/RenderingEngine.hpp"

namespace Flow {

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
		Plane(Texture texture);
		Plane(Texture diffuseTexture, Texture specularTexture);

		~Plane();

		void Draw(Shader& shader);
		void SetColor(Color color);

		void SetDiffuseTexture(Texture texture) { m_DiffuseTexture = texture; }
		void SetSpecularTexture(Texture texture) { m_SpecularTexture = texture; }

		bool GetIsTexture() { return m_IsTextured; }
		Color GetColor() { return m_Color; }
		Texture& GetDiffuseTexture() { return m_DiffuseTexture; }
		Texture& GetSpecularTexture() { return m_SpecularTexture; }

	private:
		unsigned int VAO;
		Color m_Color;
		Texture m_DiffuseTexture;
		Texture m_SpecularTexture;
		bool m_IsTextured;

		void SetupPlane();
	};
}

