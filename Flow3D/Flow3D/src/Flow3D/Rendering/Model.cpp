#include "Model.hpp"

Model::Model(std::string path)
	: name("name")
{
	LoadModel(path);
	filepath = path;
	std::size_t start = path.find_last_of("/") + 1;
	std::size_t end = path.find(".");
	name = path.substr(start, end - start);
}

Model::Model(std::shared_ptr<Cube> cube) : m_Cube(cube), name("name") {}
Model::Model(std::shared_ptr<Plane> plane) : m_Plane(plane), name("name") {}

void Model::Draw(Shader& shader)
{
	if (m_Cube != nullptr)
		m_Cube->Draw(shader);
	else if (m_Plane != nullptr)
		m_Plane->Draw(shader);
	else
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
	}				
}

void Model::LoadModel(std::string const & path)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	// retrieve the directory path of the filepath
	directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode * node, const aiScene * scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	// data to fill
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	bool hasTangents = (bool)mesh->mTangents;

	// walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		Vec3 vector;

		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		// normals
		if (mesh->mNormals)
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}
		// else -> CalculateNormals() ???
		else
			vertex.normal = Vec3(0.0f, 0.0f, 0.0f); // better calculate that

		// texture coordinates
		if (mesh->mTextureCoords[0])
		{
			Vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. Always take the first coordinates because
			// there could be multiple texture coordinates for a vertex.
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else
			vertex.texCoords = Vec2(0.0f, 0.0f);

		// tangent
		if (mesh->mTangents)
		{
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.tangent = vector;
		}			
		else
			vertex.tangent = Vec3(0.0f, 0.0f, 0.0f); // better calculate that

		// bitangent
		if (mesh->mBitangents)
		{
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector;
		}
		else
			vertex.bitangent = Vec3(0.0f, 0.0f, 0.0f); // better calculate that
			
		vertices.push_back(vertex);
	}

	// no idea if useful or working
	if (!hasTangents)
	{
		std::vector<Vec3> calculatedTangents;
		calculatedTangents.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			calculatedTangents.push_back(Vec3(0.0f));

		for (unsigned int i = 0; i < indices.size(); i+= 3)
		{
			int i0 = indices[i];
			int i1 = indices[i + 1];
			int i2 = indices[i + 2];
				
			Vec3 edge1 = vertices[i1].position - vertices[i0].position;
			Vec3 edge2 = vertices[i2].position - vertices[i0].position;

			float deltaU1 = vertices[i1].texCoords.x - vertices[i0].texCoords.x;
			float deltaU2 = vertices[i2].texCoords.x - vertices[i0].texCoords.x;
			float deltaV1 = vertices[i1].texCoords.y - vertices[i0].texCoords.y;
			float deltaV2 = vertices[i2].texCoords.y - vertices[i0].texCoords.y;

			float dividend = (deltaU1 * deltaV2 - deltaU2 * deltaV1);
			float f = dividend == 0.0f ? 0.0f : 1.0f / dividend;

			Vec3 tangent = Vec3(0.0f);
			tangent.x = f * (deltaV2 * edge1.x - deltaV1 * edge2.x);
			tangent.y = f * (deltaV2 * edge1.y - deltaV1 * edge2.y);
			tangent.z = f * (deltaV2 * edge1.z - deltaV1 * edge2.z);

			calculatedTangents[i0] = tangent;
			calculatedTangents[i1] = tangent;
			calculatedTangents[i2] = tangent;
		}

		for (unsigned int i = 0; i < calculatedTangents.size(); i++)
		{
			calculatedTangents[i] = calculatedTangents[i].Normalize();
		}
	}

	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// add materials
	Material meshMaterial = LoadMaterial(material);

	// 1. diffuse maps
	std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	if (specularMaps.size())
	{
		meshMaterial.hasSpecularTexture = false;
	}
	// 3. normal maps
	std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures, meshMaterial);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{	// if texture hasn't been loaded yet, load it
			std::string filename = std::string(str.C_Str());
			filename = directory + '/' + filename;
			Texture texture(filename, typeName, false);
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	return textures;
}

Material Model::LoadMaterial(aiMaterial * mat)
{
	Material material;
	aiColor3D color(0.0f, 0.0f, 0.0f);
	float shininess;

	mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
	material.diffuse = Vec3(color.r, color.g, color.b);

	mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
	material.ambient = Vec3(color.r, color.g, color.b);

	mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
	material.specular = Vec3(color.r, color.g, color.b);

	mat->Get(AI_MATKEY_SHININESS, shininess);
	material.shininess = shininess;

	// a shininess of 0 lead to black pixels all over models, so it needed changing
	if (material.shininess <= 0)
		material.shininess = 17.1f;

	return material;
}