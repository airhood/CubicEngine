#pragma once

#include <unordered_map>
#include <vector>
#include "../Object/Texture2D.h"
#include "../Core/EngineCore.h"
#include <GL/glew.h>

namespace CubicEngine {
	class TextureManager : public ManagerBase {
	public:
		explicit TextureManager() = default;
		~TextureManager();

		void Init() override;

		void Exterminate() override;

		void RegisterTexture2D(Texture2D* texture);

		void UpdateTexture2D(TextureType textureType, int layerIndex);

		void ReleaseTexture2D(TextureType textureType, int layerIndex);

		GLuint GetTexture2DArrayID(TextureType textureType);

	private:
		std::unordered_map<TextureType, std::vector<Texture2D*>> texture2DPools;
		std::unordered_map<TextureType, GLuint> texture2DArrayIDs;
		std::unordered_map<TextureType, GLsizei> texture2DAtlasSize;

		void AllocTexture2DArray(TextureType textureType, GLsizei atlas_size, GLsizei num_layers);
	};
}