#pragma once

#include <string>

namespace Flow {

	class Texture {
	public:
		unsigned int id;
		std::string type;
		std::string path;

		Texture();
		Texture(std::string path, std::string typeName);
		~Texture();

	private:
		unsigned int LoadTextureFromFile(const char* path);
	};
}