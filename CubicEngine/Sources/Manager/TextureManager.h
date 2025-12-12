#pragma once

#include <unordered_map>
#include <vector>
#include "../Core/EngineCore.h"
#include <GL/glew.h>
#include "../Object/Texture.h"

namespace CubicEngine {

	class Texture;
	class Texture2D;

	class TextureArray {
		friend class TextureManager;
		friend class Renderer;
		friend class Renderer2D;
		friend class MeshRenderer;
	private:
		TextureArray(int numLayers, GLsizei atlasSize);

		TextureType textureType;
		GLuint textureArrayID;
		std::vector<Texture2D*> textures;
		std::vector<int> availableIndices;
		int numLayers;
		GLsizei atlasSize;
	};

	class TextureManager : public ManagerBase {
	public:
		explicit TextureManager() = default;
		~TextureManager();

		void Init() override;

		void Exterminate() override;

		void AllocTexture2D(Texture2D* texture);
		void UpdateTexture2D(int id);
		void ReleaseTexture2D(int id);

		TextureArray* AllocTextureArray(TextureType textureType, GLsizei initAtlasSize = 128, int numLayers = 2);
		void TextureArrayRegisterTexture2D(TextureArray* textureArray, Texture2D* texture);
		void TextureArrayUpdateTexture2D(TextureArray* textureArray, int layerIndex);
		void TextureArrayUnregisterTexture2D(TextureArray* textureArray, int layerIndex);

	private:
		std::vector<Texture2D*> texture2Ds;
		std::vector<int> availableIndices;

		int init_size = 16;

		void ResizeTexture2DStorage();

		void ResizeTexture2DArrayLayer(TextureArray* textureArray);
		void ResizeTexture2DArrayAtlas(TextureArray* textureArray, GLsizei newAtlasSize);

		static GLsizei CalculateMipmapLevels(GLsizei atlasSize);

		void GenerateMipmapForLayer(TextureArray* textureArray, GLsizei atlasSize, int layerIndex);
	};
}