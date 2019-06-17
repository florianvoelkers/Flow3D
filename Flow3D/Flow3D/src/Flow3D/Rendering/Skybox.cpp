#include "Skybox.hpp"

// code from https://learnopengl.com/Advanced-OpenGL/Cubemaps

#include "Flow3D/Log.hpp"

namespace Flow {

	Skybox::Skybox(std::string skyboxDirectory, std::string filetype, bool show)
		: m_Show(show)
	{
		SetupCube(skyboxDirectory, filetype);
	}

	Skybox::~Skybox()
	{
		delete m_Shader;
	}

	void Skybox::Draw(Mat4 view, Mat4 projection) const
	{
		if (m_Show)
		{
			m_Shader->Use();
			m_Shader->SetInt("skybox", 0);

			glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
			Mat3 viewWithoutTranslation = glm::mat3(view.mat);
			view = Mat4(viewWithoutTranslation.mat); // remove translation from the view matrix
			m_Shader->SetMat4("view", view);
			m_Shader->SetMat4("projection", projection);
			// skybox cube
			glBindVertexArray(VAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubemapTexture);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			glDepthFunc(GL_LESS); // set depth function back to default
		}
	}

	void Skybox::SetupCube(std::string skyboxDirectory, std::string filetype)
	{
		m_Shader = new Shader("resources/shader/Skybox.vert", "resources/shader/Skybox.frag", "Skybox");

		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		// setup the skybox vertex objects
		unsigned int vbo;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &vbo);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		std::vector<std::string> faces
		{
			skyboxDirectory + "/right." + filetype,
			skyboxDirectory + "/left." + filetype,
			skyboxDirectory + "/top." + filetype,
			skyboxDirectory + "/bottom." + filetype,
			skyboxDirectory + "/front." + filetype,
			skyboxDirectory + "/back." + filetype,
		};
		m_CubemapTexture = LoadCubemap(faces);
	}

	unsigned int Skybox::LoadCubemap(std::vector<std::string> faces)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char *data = Texture::LoadData(faces[i], width, height, nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				Texture::FreeImageData(data);
			}
			else
			{
				FLOW_CORE_ERROR("Cubemap texture failed to load at path: {0}", faces[i]);
				Texture::FreeImageData(data);
			}			
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}
}


