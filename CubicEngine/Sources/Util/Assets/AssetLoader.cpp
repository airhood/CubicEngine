#include "AssetLoader.h"
#include <stb_image.h>

using namespace CubicEngine;

const Texture2D* AssetLoader::LoadTexture(const std::string& path) {
	auto it = textureCache.find(path);
	if (it != textureCache.end()) {
		return it->second;
	}

    int w, h, channels;
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 4);
    if (!data) throw std::runtime_error("Failed to load texture");

    Texture2D* tex = new Texture2D(w, h);
    tex->Load(data);
    tex->Apply();

    stbi_image_free(data);

    textureCache[path] = tex;
    return tex;
}