#pragma once

#include <string>

// Constructor: Texture(std::string path, std::string typeName, bool flip)
// holds data and functionality for textures
class Texture {
public:
	unsigned int id;
	std::string type;
	std::string path;
	std::string name;
	bool textureLoaded = false;
	bool m_Flip;

	Texture();
	Texture(std::string path, std::string typeName, bool flip);
	~Texture();

	bool GetFlipped() { return m_Flip; }

	static unsigned char* LoadData(std::string path, int& width, int& height, int& nrChannels, int req_comp);
	static void FreeImageData(unsigned char *data);

private:
	unsigned int LoadTextureFromFile(const char* path);
	
};

#include <MetaStuff/include/Meta.h>

namespace meta {

	template <>
	inline auto registerMembers<Texture>()
	{
		return members(
			member("id", &Texture::id),
			member("type", &Texture::type),
			member("path", &Texture::path),
			member("m_Flip", &Texture::m_Flip)
		);
	}

} // end of namespace meta