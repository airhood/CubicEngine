#pragma once

#include <string>
#include <unordered_map>
#include "../../Object/Texture2D.h"
#include "../../Object/AudioClip.h"

namespace CubicEngine {
	class AssetLoader {
	public:
		static const Texture2D* LoadTexture(const std::string& path);
		static const AudioClip* LoadAudioClip(const std::string& path);
		
	private:
		static std::unordered_map<std::string, Texture2D*> textureCache;
	};
}