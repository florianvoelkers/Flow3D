#include "Plane.hpp"

namespace Flow {

	Plane::Plane()
		: m_Color(0.0f, 0.0f, 0.0f), m_IsTextured(false)
	{
		SetupPlane();
	}

	Plane::Plane(float r, float g, float b)
		: m_Color(Color(r, g, b)), m_IsTextured(false)
	{
		SetupPlane();
	}

	Plane::Plane(float r, float g, float b, float a)
		: m_Color(Color(r, g, b, a)), m_IsTextured(false)
	{
		SetupPlane();
	}

	Plane::Plane(Color color)
		: m_Color(color), m_IsTextured(false)
	{
		SetupPlane();
	}

	Plane::Plane(Texture texture)
		: m_Color(0.0f, 0.0f, 0.0f), m_IsTextured(true), m_Texture(texture)
	{
		SetupPlane();
	}

	Plane::~Plane()
	{
		delete m_Shader;
	}

	void Plane::Draw(Mat4 model, Mat4 view, Mat4 projection)
	{
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

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Plane::SetColor(Color color)
	{
		m_Color = color;
	}

	void Plane::SetupPlane()
	{

		float vertices[] = {
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f // top left
		};

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		if (m_IsTextured) {
			m_Shader = new Shader("resources/shader/Basic3DTextured.vert", "resources/shader/Textured.frag");
		}
		else
		{
			m_Shader = new Shader("resources/shader/Basic3D.vert", "resources/shader/Colored.frag");
		}

		unsigned int VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		if (m_IsTextured)
		{
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
