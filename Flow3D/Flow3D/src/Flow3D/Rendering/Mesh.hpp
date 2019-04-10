#pragma once

#include "Flow3D/Math.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include <vector>

namespace Flow {

	struct Vertex {
		Vec3 position;
		Vec3 normal;
		Vec2 texCoords;
		Vec3 tangent;
		Vec3 bitangent;
	};

	class Mesh {
	public:
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<Texture> m_Textures;
		unsigned int m_VAO;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		~Mesh();

		void Draw(Shader& shader);

	private:
		unsigned int VBO, EBO;

		void SetupMesh();
	};
}
