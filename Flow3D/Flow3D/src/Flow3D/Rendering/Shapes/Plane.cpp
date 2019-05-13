#include "Plane.hpp"

#include "Flow3D/Application.hpp"
#include "Flow3D/Components/Lighting.hpp"

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
		: m_Color(0.0f, 0.0f, 0.0f), m_IsTextured(true), m_DiffuseTexture(texture), m_SpecularTexture(texture)
	{
		SetupPlane();
	}

	Plane::Plane(Texture diffuseTexture, Texture specularTexture)
		: m_Color(0.0f, 0.0f, 0.0f), m_IsTextured(true), m_DiffuseTexture(diffuseTexture), m_SpecularTexture(specularTexture)
	{
		SetupPlane();
	}

	Plane::~Plane()
	{
	}

	void Plane::Draw(Mat4 model, Mat4 view, Mat4 projection, RenderingEngine& renderingEngine)
	{
		// set data for the shader
		m_Shader->Use();
		if (m_IsTextured)
		{
			m_Shader->SetBool("material.hasSpecularTexture", true);
			glActiveTexture(GL_TEXTURE0 + m_DiffuseTexture.id);
			m_Shader->SetInt("material.diffuse", m_DiffuseTexture.id);
			glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture.id);
			glActiveTexture(GL_TEXTURE1);
			m_Shader->SetInt("material.specular", m_DiffuseTexture.id);
			glBindTexture(GL_TEXTURE_2D, m_SpecularTexture.id);
			// TODO: value should be set externally
			m_Shader->SetFloat("material.shininess", 17);
		}

		m_Shader->SetMat4("model", model);
		m_Shader->SetMat4("view", view);
		m_Shader->SetMat4("projection", projection);

		m_Shader->SetVec3("viewPos", renderingEngine.GetViewPosition());
		// directional light
		DirectionalLight& directionalLight = Application::Get().GetCurrentScene().GetDirectionalLight();
		m_Shader->SetVec3("dirLight.direction", directionalLight.GetDirection());
		m_Shader->SetVec3("dirLight.ambient", directionalLight.GetAmbientIntensity());
		m_Shader->SetVec3("dirLight.diffuse", directionalLight.GetDiffuseIntensity());
		m_Shader->SetVec3("dirLight.specular", directionalLight.GetSpecularIntensity());

		std::vector<PointLight*> pointLights = Application::Get().GetCurrentScene().GetPointLights();
		std::string uniform;
		m_Shader->SetInt("numberOfPointLights", (int)pointLights.size());
		for (unsigned int i = 0; i < pointLights.size(); i++)
		{
			uniform += std::string("pointLights[") + std::to_string(i) + std::string("].");
			std::string shaderString = uniform + std::string("position");
			m_Shader->SetVec3(shaderString, pointLights[i]->GetTransform()->m_Position);
			shaderString = uniform + std::string("ambient");
			m_Shader->SetVec3(shaderString, pointLights[i]->GetAmbientIntensity());
			shaderString = uniform + std::string("diffuse");
			m_Shader->SetVec3(shaderString, pointLights[i]->GetDiffuseIntensity());
			shaderString = uniform + std::string("specular");
			m_Shader->SetVec3(shaderString, pointLights[i]->GetSpecularIntensity());
			shaderString = uniform + std::string("constant");
			m_Shader->SetFloat(shaderString, pointLights[i]->GetAttenuation().GetConstant());
			shaderString = uniform + std::string("linear");
			m_Shader->SetFloat(shaderString, pointLights[i]->GetAttenuation().GetLinear());
			shaderString = uniform + std::string("quadratic");
			m_Shader->SetFloat(shaderString, pointLights[i]->GetAttenuation().GetExponent());
			uniform = "";
		}

		std::vector<SpotLight*> spotLights = Application::Get().GetCurrentScene().GetSpotLights();
		m_Shader->SetInt("numberOfSpotLights", (int)spotLights.size());
		for (unsigned int i = 0; i < spotLights.size(); i++)
		{
			uniform += std::string("spotLights[") + std::to_string(i) + std::string("].");
			std::string shaderString = uniform + std::string("position");
			m_Shader->SetVec3(shaderString, spotLights[i]->GetTransform()->m_Position);
			shaderString = uniform + std::string("direction");
			m_Shader->SetVec3(shaderString, spotLights[i]->GetDirection());
			shaderString = uniform + std::string("cutOff");
			m_Shader->SetFloat(shaderString, spotLights[i]->GetCutoff());
			shaderString = uniform + std::string("outerCutOff");
			m_Shader->SetFloat(shaderString, spotLights[i]->GetOuterCutoff());
			shaderString = uniform + std::string("ambient");
			m_Shader->SetVec3(shaderString, spotLights[i]->GetAmbientIntensity());
			shaderString = uniform + std::string("diffuse");
			m_Shader->SetVec3(shaderString, spotLights[i]->GetDiffuseIntensity());
			shaderString = uniform + std::string("specular");
			m_Shader->SetVec3(shaderString, spotLights[i]->GetSpecularIntensity());
			shaderString = uniform + std::string("constant");
			m_Shader->SetFloat(shaderString, spotLights[i]->GetAttenuation().GetConstant());
			shaderString = uniform + std::string("linear");
			m_Shader->SetFloat(shaderString, spotLights[i]->GetAttenuation().GetLinear());
			shaderString = uniform + std::string("quadratic");
			m_Shader->SetFloat(shaderString, spotLights[i]->GetAttenuation().GetExponent());
			uniform = "";
		}

		// render plane
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Plane::SetColor(Color color)
	{
		m_Color = color;
	}

	void Plane::SetupPlane()
	{
		// setup vertices and indices for drawing a plane
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f // top left
		};

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		if (m_IsTextured) {
			m_Shader = Application::Get().GetStandardShader();
		}
		else
		{
			m_Shader = std::make_shared<Shader>("resources/shader/Basic3D.vert", "resources/shader/Colored.frag");
		}

		// setup buffers and confgiure vertex attributes
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
		else
		{
			m_Shader->Use();
			m_Shader->SetVec4("color", m_Color.ToVector4f());
		}
	}

}
