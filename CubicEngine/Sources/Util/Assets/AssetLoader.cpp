#include "AssetLoader.h"
#include <stb_image.h>
#include "../Logger.h"

using namespace CubicEngine;

static const std::string source = "AssetLoader.cpp";

std::unordered_map<std::string, Texture2D*> AssetLoader::textureCache = std::unordered_map<std::string, Texture2D*>();

const Texture2D* AssetLoader::LoadTexture(const std::string& path) {
	auto it = textureCache.find(path);
	if (it != textureCache.end()) {
		return it->second;
	}

    stbi_set_flip_vertically_on_load(true);

    int w, h, channels;
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 4);
    if (!data) {
        Logger::Log(LogLevel::ERROR, "Failed to load texture", source);
        return nullptr;
    }

    Texture2D* tex = new Texture2D(w, h);
    tex->Load(data);
    tex->Apply();

    stbi_image_free(data);

    textureCache[path] = tex;
    return tex;
}

const AudioClip* AssetLoader::LoadAudioClip(const std::string& path) {

}