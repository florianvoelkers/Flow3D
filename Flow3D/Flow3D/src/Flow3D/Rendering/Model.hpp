#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Flow3D/Math.hpp"
#include "Shapes/Cube.hpp"
#include "Shapes/Plane.hpp"

// from https://learnopengl.com/Model-Loading/Model

namespace Flow {

	class Model
	{
	public:
		/* Model Data */
		std::vector<Texture> textures_loaded;
		std::vector<Mesh> meshes;
		std::string directory;
		std::string filepath;
		bool gammaCorrection;

		/* Functions */
		// constrcutor, expects a filepath to a 3D model
		Model(std::string const& path);
		Model(std::shared_ptr<Cube> cube);
		Model(std::shared_ptr<Plane> plane);

		void Draw(Shader shader);

		std::shared_ptr<Cube> GetCube() { return m_Cube; }
		std::shared_ptr<Plane> GetPlane() { return m_Plane; }

	private:
		std::shared_ptr<Cube> m_Cube;
		std::shared_ptr<Plane> m_Plane;

		/* Functions */
		// loads a model with supported assimp extensions from file and stores the resulting meshes in the meshes vector
		void LoadModel(std::string const& path);

		// processes a node in a recursive fashion. Processes each individual mesh located at the node 
		// and repeats this process on its children nodes (if any)
		void ProcessNode(aiNode* node, const aiScene* scene);

		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		
		// checks all material textures of a given type and loads the textures if they're not loaded yet.
		// the required info is returned as a Texture struct
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

		Material LoadMaterial(aiMaterial* mat);
	};
}

