#include "Texture.h"

#include <unordered_map>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include "Math.h"

static std::unordered_map<std::string, int> cache;

std::vector<Texture> Texture::textures;

int Texture::load(const char * file_path) {
	int & texture_id = cache[file_path];

	// If the cache already contains this Texture simply return it
	if (texture_id != 0 && textures.size() > 0) return texture_id;

	// Otherwise, create new Texture and load it from disk
	texture_id        = textures.size();
	Texture & texture = textures.emplace_back();

	texture.data = stbi_load(file_path, &texture.width, &texture.height, &texture.channels, STBI_rgb_alpha);
	texture.channels = 4;
	
	// Check if the Texture is valid
	if (texture.data == nullptr || texture.width == 0 || texture.height == 0) {
		printf("WARNING: Failed to load Texture '%s'!\n", file_path);

		texture.width  = 1;
		texture.height = 1;
		texture.data = new unsigned char[4] { 255, 0, 255, 255 };
	}

	return texture_id;
}
