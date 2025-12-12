#include "TextureManager.h"

using namespace CubicEngine;

TextureManager::~TextureManager() {
	Exterminate();
}

void TextureManager::Init() {
	for (int i = 0; i < 16; i++) {
		AllocTexture2DArray(static_cast<TextureType>(i), 2048, 10);
	}
}

void TextureManager::Exterminate() {

}

void TextureManager::RegisterTexture2D(Texture2D* texture) {
	int layer_idx = texture2DPools[texture->GetTextureType()].size();
	texture->layerIndex = layer_idx;
	texture2DPools[texture->GetTextureType()].push_back(texture);

	GLsizei atlas_size = texture2DAtlasSize[texture->GetTextureType()];

	GLuint& textureArrayID = texture2DArrayIDs[texture->GetTextureType()];
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayID);

	glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
					0,
					0, 0, layer_idx,
					atlas_size, atlas_size, 1,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					texture->data_raw);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void TextureManager::UpdateTexture2D(TextureType textureType, int layerIndex) {
	Texture2D* tex = texture2DPools[textureType][layerIndex];

	GLuint& textureArrayID = texture2DArrayIDs[textureType];
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayID);

	glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
					0,
					0, 0, layerIndex,
					tex->width(), tex->height(), 1,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					texture2DPools[textureType][layerIndex]->data_raw);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void TextureManager::ReleaseTexture2D(TextureType textureType, int layerIndex) {

}

GLuint TextureManager::GetTexture2DArrayID(TextureType textureType) {
	return texture2DArrayIDs[textureType];
}

void TextureManager::AllocTexture2DArray(TextureType textureType, GLsizei atlas_size, GLsizei num_layers) {
	GLuint& textureArrayID = texture2DArrayIDs[textureType];
	glGenTextures(1, &textureArrayID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayID);

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, atlas_size, atlas_size, num_layers);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture2DAtlasSize[textureType] = atlas_size;

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}