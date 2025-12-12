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
		std::unordered_map<TextureType, std::vector<int>> availableIndices;
		std::unordered_map<TextureType, int> texture2DArrayNumLayers;

		static std::unordered_map<TextureType, int> init_layer_num;

		void AllocTexture2DArray(TextureType textureType, GLsizei atlasSize, GLsizei numLayers);

		void ResizeTexture2DArrayLayer(TextureType textureType);
		void ResizeTexture2DArrayAtlas(TextureType textureType, GLsizei newAtlasSize);

		GLsizei CalculateMipmapLevels(GLsizei atlasSize);

		void GenerateMipmapForLayer(GLuint texture2DArrayID, GLsizei atlasSize, int layerIndex);
	};
}