#pragma once

#include <string>

namespace Flow {

	// Constructor: Texture(std::string path, std::string typeName, bool flip)
	// holds data and functionality for textures
	class Texture {
	public:
		unsigned int id;
		std::string type;
		std::string path;

		Texture();
		Texture(std::string path, std::string typeName, bool flip);
		~Texture();

		static unsigned char* LoadData(std::string path, int& width, int& height, int& nrChannels, int req_comp);
		static void FreeImageData(unsigned char *data);

	private:
		unsigned int LoadTextureFromFile(const char* path);
		bool m_Flip;
	};
}