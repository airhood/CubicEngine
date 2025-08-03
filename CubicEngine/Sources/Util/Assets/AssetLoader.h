#pragma once

#include <string>
#include <unordered_map>
#include "../../Object/Texture2D.h"

namespace CubicEngine {
	class AssetLoader {
	public:
		const Texture2D* LoadTexture(const std::string& path);
		
	private:
		std::unordered_map<std::string, Texture2D*> textureCache;
	};
}