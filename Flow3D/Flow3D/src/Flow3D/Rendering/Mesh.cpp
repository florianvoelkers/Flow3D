#include "Mesh.hpp"

// code from https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h

namespace Flow {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material material)
		: m_Vertices(vertices), m_Indices(indices), m_Textures(textures), m_Material(material)
	{
		SetupMesh();
	}

	Mesh::~Mesh()
	{

	}

	void Mesh::Draw(Shader& shader)
	{
		// bind appropiate textures
		unsigned int diffuseNumber = 1;
		unsigned int specularNumber = 1;
		unsigned int normalNumber = 1;
		unsigned int heightNumber = 1;

		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			/* for without lights
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN
			std::string number;
			std::string name = m_Textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNumber++);
			else if (name == "texture_specular")
				number = std::to_string(specularNumber++); // transfer unsigned int to stream
			else if (name == "texture_normal")
				number = std::to_string(normalNumber++); // transfer unsigned int to stream 
			else if (name == "texture_height")
				number = std::to_string(heightNumber++); // transfer unsigned int to stream

			// set the sample to the correct texture unit
			// glUniform1i(glGetUniformLocation(shader.m_ID, (name + number).c_str()), i); <--- same as below
			shader.SetInt((name + number).c_str(), i);
			*/

			// for shader MultipleLights
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN
			std::string number;
			std::string name = m_Textures[i].type;
			if (name == "texture_diffuse")
				shader.SetInt(("material.texture_diffuse" + number).c_str(), i);
			else if (name == "texture_specular")
				shader.SetInt(("material.texture_specular" + number).c_str(), i);
			else if (name == "texture_normal")
				number = std::to_string(normalNumber++); // transfer unsigned int to stream 
			else if (name == "texture_height")
				number = std::to_string(heightNumber++); // transfer unsigned int to stream

			// bind the texture
			glBindTexture(GL_TEXTURE_2D, m_Textures[i].id);
			
		}
		shader.SetFloat("material.shininess", m_Material.shininess);

		// draw mesh
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// good practice to set everytghing back to defaults once configured
		glActiveTexture(GL_TEXTURE0);
	}

	// initalizes all the buffer objects/arrays
	void Mesh::SetupMesh()
	{
		// create buffers/arrays
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(m_VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// since the memory layout of a struct is sequential for all its items
		// we can pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array
		// which again translates to 3/2 floats which translates to a byte array
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		// vertex texture coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

		// vertex tangent
		//glEnableVertexAttribArray(3);
		//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

		// vertex bitangent
		//glEnableVertexAttribArray(4);
		//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

		glBindVertexArray(0);
	}
}