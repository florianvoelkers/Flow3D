#pragma once

#include "Flow3D/Math.hpp"

#include "Flow3D/Rendering/Shader.hpp"
#include "Flow3D/Rendering/Texture.hpp"
#include "Flow3D/Color.hpp"

namespace Flow {

	class Cube {

	public:
		Cube();

		Cube(float r, float g, float b);
		Cube(float r, float g, float b, float a);
		Cube(Color color);
		Cube(Texture texture);

		~Cube();

		void Draw(Mat4 model, Mat4 view, Mat4 projection);
		void SetColor(Color color);

	private:
		Shader* m_Shader;
		unsigned int VAO;
		Color m_Color;
		Texture m_Texture;
		bool m_IsTextured;

		void SetupCube();
	};
}

