#pragma once

#include <string>
#include <unordered_map>
#include "../../Object/Texture2D.h"
#include "../../Object/AudioClip.h"
#include "../../Object/Texture.h"

namespace CubicEngine {
	class AssetLoader {
	public:
		static Texture2D* LoadTexture2D(const std::string& path, TextureType textureType = TextureType::ALBEDO);
		static AudioClip* LoadAudioClip(const std::string& path);
		
	private:
		static std::unordered_map<std::string, Texture2D*> texture2DCache;
		static std::unordered_map<std::string, AudioClip*> audioClipCache;
	};
}