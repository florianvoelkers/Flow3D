#pragma once

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shader.hpp"
#include "Flow3D/Rendering/Texture.hpp"
#include "Flow3D/Color.hpp"

namespace Flow {

	// This class will draw a plane depending on model, view and projection
	// it provides several possibilites for declaration, e.g. with a texture, color or nothing
	class Plane {

	public:
		Plane();

		Plane(float r, float g, float b);
		Plane(float r, float g, float b, float a);
		Plane(Color color);
		Plane(Texture texture);

		~Plane();

		void Draw(Mat4 model, Mat4 view, Mat4 projection);
		void SetColor(Color color);

	private:
		Shader* m_Shader;
		unsigned int VAO;
		Color m_Color;
		Texture m_Texture;
		bool m_IsTextured;

		void SetupPlane();
	};
}

