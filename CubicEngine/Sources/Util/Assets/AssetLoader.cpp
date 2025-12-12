#include "AssetLoader.h"
#include <stb_image.h>
#include "../Logger.h"
#include "../../Core/EngineCore.h"
#include <fmod.hpp>

using namespace CubicEngine;

static const std::string source = "AssetLoader.cpp";

std::unordered_map<std::string, Texture2D*> AssetLoader::texture2DCache = std::unordered_map<std::string, Texture2D*>();
std::unordered_map<std::string, AudioClip*> AssetLoader::audioClipCache = std::unordered_map<std::string, AudioClip*>();

Texture2D* AssetLoader::LoadTexture2D(const std::string& path, TextureType textureType) {
	auto it = texture2DCache.find(path);
	if (it != texture2DCache.end()) {
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
    tex->SetTextureType(textureType);
    tex->Load(data);
    tex->Apply();

    stbi_image_free(data);

    texture2DCache[path] = tex;
    return tex;
}

AudioClip* AssetLoader::LoadAudioClip(const std::string& path) {
    auto it = audioClipCache.find(path);
    if (it != audioClipCache.end()) {
        return it->second;
    }

    FMOD::System* system = CORE->GET(AudioManager)->GetFMODSystem();
    FMOD::Sound* sound(nullptr);
    FMOD_RESULT result = system->createSound(path.c_str(), FMOD_LOOP_OFF, 0, &sound);
    if (result != FMOD_OK) {
        Logger::Log(LogLevel::ERROR, "[AssetLoader] FMOD create sound failed.", source);
        return nullptr;
    }

    AudioClip* audioClip = new AudioClip();
    audioClip->sound = sound;

    audioClipCache[path] = audioClip;

    return audioClip;
}