#include "Cube.hpp"

#include "Flow3D/Application.hpp"
#include "Flow3D/Components/Lighting.hpp"

#include "Flow3D/Log.hpp"

namespace Flow {

	Cube::Cube()
		: m_Color(0.0f, 0.0f, 0.0f), m_IsTextured(false), m_TextureInitialized(false)
	{
		SetupCube();
	}

	Cube::Cube(float r, float g, float b)
		: m_Color(Color(r, g, b)), m_IsTextured(false), m_TextureInitialized(false)
	{
		SetupCube();
	}

	Cube::Cube(float r, float g, float b, float a)
		: m_Color(Color(r, g, b, a)), m_IsTextured(false), m_TextureInitialized(false)
	{
		SetupCube();
	}

	Cube::Cube(Color color)
		: m_Color(color), m_IsTextured(false), m_TextureInitialized(false)
	{
		SetupCube();
	}

	// TODO: maybe it is better to set the specular value to 0.2f instead of taking the diffuseTexture
	Cube::Cube(std::shared_ptr<Texture> texture)
		: m_Color(0.0f, 0.0f, 0.0f), m_IsTextured(true), m_DiffuseTexture(texture), m_SpecularTexture(texture), m_TextureInitialized(true)
	{
		SetupCube();
	}

	Cube::Cube(std::shared_ptr<Texture> diffuseTexture, std::shared_ptr<Texture> specularTexture)
		: m_Color(0.0f, 0.0f, 0.0f), m_IsTextured(true), m_DiffuseTexture(diffuseTexture), m_SpecularTexture(specularTexture), m_TextureInitialized(true)
	{
		SetupCube();
	}

	Cube::~Cube()
	{
	}


	void Cube::Draw(Shader& shader)
	{
		if (m_WireframeMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// set data for the shader
		shader.Use();
		if (m_IsTextured)
		{
			shader.SetBool("material.hasSpecularTexture", true);
			glActiveTexture(GL_TEXTURE0 + m_DiffuseTexture->id);
			shader.SetInt("material.diffuse", m_DiffuseTexture->id);
			glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture->id);
			glActiveTexture(GL_TEXTURE1);
			shader.SetInt("material.specular", m_DiffuseTexture->id);
			glBindTexture(GL_TEXTURE_2D, m_SpecularTexture->id);
			// TODO: value should be set externally
			shader.SetFloat("material.shininess", 17);
		}
		else
		{
			shader.SetVec4("color", m_Color.ToVector4f());
		}

		// render cube
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		if (m_WireframeMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// good practice to set everytghing back to defaults once configured
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}

	void Cube::SetIsTextured(bool isTextured) 
	{ 
		m_IsTextured = isTextured;
		if (isTextured)
			SetupCube();		 
	}

	void Cube::SetupCube()
	{
		m_WireframeMode = false;

		// setup the cubes vertices with positions, normals and texture coordinates and indices 
		float vertices[] = {
			// front
			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,

			// right
			 0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,		0.0f, 0.0f,

			 // back
			 -0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
			  0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f,
			  0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
			 -0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 1.0f,

			 // left
			 -0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
			 -0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
			 -0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,

			 // upper
			  0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 0.0f,
			 -0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
			  0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,

			  // bottom
			  -0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 0.0f,
			   0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
			   0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
			  -0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 1.0f
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

		if (m_IsTextured)
		{
			// texture coordinates attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
		}

		glBindVertexArray(0);
	}
}