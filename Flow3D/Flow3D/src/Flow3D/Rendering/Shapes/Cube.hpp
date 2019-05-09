#pragma once

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shader.hpp"
#include "Flow3D/Rendering/Texture.hpp"
#include "Flow3D/Color.hpp"

#include "Flow3D/Rendering/RenderingEngine.hpp"

namespace Flow {

	// This class will draw a cube depending on model, view and projection
	// it provides several possibilites for declaration, e.g. with a texture, color or nothing
	class Cube {

	public:
		Cube();

		Cube(float r, float g, float b);
		Cube(float r, float g, float b, float a);
		Cube(Color color);
		Cube(Texture texture);
		Cube(Texture diffuseTexture, Texture specularTexture);

		~Cube();

		void Draw(Mat4 model, Mat4 view, Mat4 projection, RenderingEngine& renderingEngine);
		void SetColor(Color color);

	private:
		Shader* m_Shader;
		unsigned int VAO;
		Color m_Color;
		Texture m_DiffuseTexture;
		Texture m_SpecularTexture;
		bool m_IsTextured;

		void SetupCube();
	};
}

