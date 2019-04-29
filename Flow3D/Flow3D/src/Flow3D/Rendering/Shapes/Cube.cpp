#include "Cube.hpp"

#include "Flow3D/Log.hpp"
#include "Flow3D/Color.hpp"

namespace Flow {

	Cube::Cube()
		: m_Color(0.0f, 0.0f, 0.0f), m_IsTextured(false)
	{
		SetupCube();
	}

	Cube::Cube(float r, float g, float b)
		: m_Color(Color(r, g, b)), m_IsTextured(false)
	{
		SetupCube();
	}

	Cube::Cube(float r, float g, float b, float a)
		: m_Color(Color(r, g, b, a)), m_IsTextured(false)
	{
		SetupCube();
	}

	Cube::Cube(Color color)
		: m_Color(color), m_IsTextured(false)
	{
		SetupCube();
	}

	Cube::Cube(Texture texture)
		: m_Color(0.0f, 0.0f, 0.0f), m_IsTextured(true), m_Texture(texture)
	{
		SetupCube();
	}

	Cube::~Cube()
	{
		delete m_Shader;
	}


	void Cube::Draw(Mat4 model, Mat4 view, Mat4 projection)
	{
		// set data for the shader
		m_Shader->Use();
		if (m_IsTextured)
		{
			glActiveTexture(GL_TEXTURE0 + m_Texture.id);
			m_Shader->SetInt("texture1", m_Texture.id);
			glBindTexture(GL_TEXTURE_2D, m_Texture.id);
		}

		m_Shader->SetMat4("model", model);
		m_Shader->SetMat4("view", view);
		m_Shader->SetMat4("projection", projection);

		// render cube
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	void Cube::SetColor(Color color)
	{
		m_Color = color;
	}

	void Cube::SetupCube()
	{
		// setup the cubes vertices and indices 
		float vertices[] = {
			// front
			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,

			// right
			 0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

			 // back
			 -0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
			  0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
			  0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
			 -0.5f,  0.5f, -0.5f,	1.0f, 1.0f,

			 // left
			 -0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
			 -0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
			 -0.5f,  0.5f, -0.5f,	0.0f, 1.0f,

			 // upper
			  0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
			 -0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
			  0.5f,  0.5f, -0.5f,	1.0f, 1.0f,

			  // bottom
			  -0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
			   0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
			   0.5f, -0.5f,  0.5f,	1.0f, 1.0f,
			  -0.5f, -0.5f,  0.5f,	0.0f, 1.0f
		};

		unsigned int indices[] = {
			// front
			0, 1, 2,
			0, 2, 3,

			// right
			4, 5, 6,
			4, 6, 7,

			// back
			8, 9, 10,
			8, 10, 11,

			// left
			12, 13, 14,
			12, 14, 15,

			// upper
			16, 17, 18,
			16, 18, 19,

			// bottom
			20, 21, 22,
			20, 22, 23
		};

		// use the standard shader for textures or color
		if (m_IsTextured) {
			m_Shader = new Shader("resources/shader/Basic3DTextured.vert", "resources/shader/Textured.frag");
		}
		else
		{
			m_Shader = new Shader("resources/shader/Basic3D.vert", "resources/shader/Colored.frag");
		}

		// set up buffers and configure vertex attributes
		unsigned int VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		if (m_IsTextured)
		{
			// texture coordinates attribute
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
		else
		{
			m_Shader->Use();
			m_Shader->SetVec4("color", m_Color.ToVector4f());
		}


	}
}