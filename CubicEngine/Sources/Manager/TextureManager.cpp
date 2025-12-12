#include "TextureManager.h"
#include <iostream>
#include <format>

using namespace CubicEngine;

static const std::string source = "TextureManager.cpp";

std::unordered_map<TextureType, int> TextureManager::init_layer_num = {
	{TextureType::ALBEDO, 1},
	{TextureType::NORMAL, 1},
	{TextureType::METALLIC, 1},
	{TextureType::ROUGHNESS, 1},
	{TextureType::AO, 1},
	{TextureType::EMISSION, 1},

	{TextureType::SPRITE, 1},

	{TextureType::SHADOW_MAP, 1},
	{TextureType::SHADOW_CUBE, 1},

	{TextureType::GBUFFER_DEPTH, 1},
	{TextureType::GBUFFER_NORMAL, 1},

	{TextureType::IRRADIANCE_MAP, 1},
	{TextureType::PREFILTER_MAP, 1},
	{TextureType::BRDF_LUT, 1},

	{TextureType::POSTFX_0, 1},
	{TextureType::POSTFX_1, 1}
};

TextureManager::~TextureManager() {
	Exterminate();
}

void TextureManager::Init() {
	for (int i = 0; i < 16; i++) {
		TextureType textureType = static_cast<TextureType>(i);
		AllocTexture2DArray(textureType, 128, init_layer_num[textureType]);
		for (int i = init_layer_num[textureType] - 1; i >= 0; i--) {
			texture2DPools[textureType].push_back(nullptr);
			availableIndices[textureType].push_back(i);
		}
		texture2DArrayNumLayers[textureType] = init_layer_num[textureType];
	}
}

void TextureManager::Exterminate() {

}

void TextureManager::RegisterTexture2D(Texture2D* texture) {
	TextureType textureType = texture->GetTextureType();
	int layer_idx = availableIndices[textureType].back();
	availableIndices[textureType].pop_back();
	texture->layerIndex = layer_idx;
	texture2DPools[textureType][layer_idx] = texture;

	GLsizei atlas_size = texture2DAtlasSize[textureType];

	auto max = [](int a, int b) {
		if (a > b) return a;
		return b;
		};

	if (texture->width() > atlas_size || texture->height() > atlas_size) {
		ResizeTexture2DArrayAtlas(textureType, max(texture->width(), texture->height()));
	}

	GLuint& textureArrayID = texture2DArrayIDs[textureType];
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayID);

	glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
					0,
					0, 0, layer_idx,
					texture->width(), texture->height(), 1,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					texture->data_raw);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		Logger::Log(LogLevel::ERROR,
			std::format("[TextureManager] glTexSubImage3D failed: {}", error),
			source);
	}

	GenerateMipmapForLayer(texture2DArrayIDs[textureType], atlas_size, layer_idx);

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

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		Logger::Log(LogLevel::ERROR,
			std::format("[TextureManager] glTexSubImage3D failed: {}", error),
			source);
	}

	GLsizei atlas_size = texture2DAtlasSize[textureType];

	GenerateMipmapForLayer(texture2DArrayIDs[textureType], atlas_size, layerIndex);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void TextureManager::ReleaseTexture2D(TextureType textureType, int layerIndex) {
	texture2DPools[textureType][layerIndex] = nullptr;
	availableIndices[textureType].push_back(layerIndex);
}

GLuint TextureManager::GetTexture2DArrayID(TextureType textureType) {
	return texture2DArrayIDs[textureType];
}

void TextureManager::AllocTexture2DArray(TextureType textureType, GLsizei atlasSize, GLsizei numLayers) {
	GLint maxLayers;
	glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &maxLayers);
	if (numLayers > maxLayers) {
		Logger::Log(LogLevel::ERROR, std::format("[TextureManager] New layer count exceeds OpenGL max limit of {}.", maxLayers), source);
		return;
	}
	
	GLuint& textureArrayID = texture2DArrayIDs[textureType];
	glGenTextures(1, &textureArrayID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayID);

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, CalculateMipmapLevels(atlasSize), GL_RGBA8, atlasSize, atlasSize, numLayers);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	texture2DAtlasSize[textureType] = atlasSize;
}

void TextureManager::ResizeTexture2DArrayLayer(TextureType textureType) {
	GLuint oldTextureID = texture2DArrayIDs[textureType];
	if (oldTextureID == 0) {
		Logger::Log(LogLevel::ERROR, "[TextureManager] Cannot resize a non-existent texture array.", source);
		return;
	}

	GLsizei atlasSize = texture2DAtlasSize[textureType];

	GLsizei oldNumLayers = texture2DArrayNumLayers[textureType];
	GLsizei newNumLayers = oldNumLayers * 2;
	
	GLint maxLayers;
	glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &maxLayers);
	if (newNumLayers > maxLayers) {
		Logger::Log(LogLevel::ERROR, std::format("[TextureManager] New layer count exceeds OpenGL max limit of {}.", maxLayers), source);
		return;
	}

	GLuint newTextureID;
	glGenTextures(1, &newTextureID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, newTextureID);

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, CalculateMipmapLevels(atlasSize), GL_RGBA8, atlasSize, atlasSize, newNumLayers);

	glCopyImageSubData(
		oldTextureID, GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0,
		newTextureID, GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0,
		atlasSize, atlasSize, oldNumLayers
	);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	texture2DArrayIDs[textureType] = newTextureID;
	texture2DArrayNumLayers[textureType] = newNumLayers;

	glDeleteTextures(1, &oldTextureID);
}

void TextureManager::ResizeTexture2DArrayAtlas(TextureType textureType, GLsizei newAtlasSize) {
	GLuint oldTextureID = texture2DArrayIDs[textureType];
	if (oldTextureID == 0) {
		Logger::Log(LogLevel::ERROR, "[TextureManager] Cannot resize a non-existent texture array.", source);
		return;
	}

	GLsizei oldAtlasSize = texture2DAtlasSize[textureType];
	GLsizei numLayers = texture2DArrayNumLayers[textureType];

	if (newAtlasSize <= oldAtlasSize) {
		Logger::Log(LogLevel::WARNING, "[TextureManager] New atlas size is not larger than the old one.", source);
		return;
	}

	GLint maxTextureSize;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
	if (newAtlasSize > maxTextureSize) {
		Logger::Log(LogLevel::ERROR, std::format("[TextureManager] New atlas size exceeds OpenGL max texture size of {}.", maxTextureSize), source);
		return;
	}

	GLuint newTextureID;
	glGenTextures(1, &newTextureID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, newTextureID);

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, CalculateMipmapLevels(newAtlasSize), GL_RGBA8, newAtlasSize, newAtlasSize, numLayers);

	glCopyImageSubData(
		oldTextureID, GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0,
		newTextureID, GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0,
		oldAtlasSize, oldAtlasSize, numLayers
	);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	
	texture2DArrayIDs[textureType] = newTextureID;
	texture2DAtlasSize[textureType] = newAtlasSize;

	glDeleteTextures(1, &oldTextureID);
}

GLsizei TextureManager::CalculateMipmapLevels(GLsizei atlasSize) {
	return static_cast<GLsizei>(floor(log2(atlasSize))) + 1;
}

void TextureManager::GenerateMipmapForLayer(GLuint texture2DArrayID, GLsizei atlasSize, int layerIndex) {
	GLuint readFBO, drawFBO;
	glGenFramebuffers(1, &readFBO);
	glGenFramebuffers(1, &drawFBO);

	GLsizei currentSize = atlasSize;
	int numMipmapLevels = CalculateMipmapLevels(atlasSize);

	for (int level = 0; level < numMipmapLevels - 1; level++) {
		int nextLevel = level + 1;
		GLsizei nextSize = std::max(1, currentSize / 2);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, readFBO);
		glFramebufferTextureLayer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			texture2DArrayID, level, layerIndex);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFBO);
		glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			texture2DArrayID, nextLevel, layerIndex);

		if (glCheckFramebufferStatus(GL_READ_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			Logger::Log(LogLevel::ERROR, "[TextureManager] Read framebuffer is not complete!", source);
			break;
		}
		if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			Logger::Log(LogLevel::ERROR, "[TextureManager] Draw framebuffer is not complete!", source);
			break;
		}

		glBlitFramebuffer(
			0, 0, currentSize, currentSize,
			0, 0, nextSize, nextSize,
			GL_COLOR_BUFFER_BIT,
			GL_LINEAR
		);

		currentSize = nextSize;
	}

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &readFBO);
	glDeleteFramebuffers(1, &drawFBO);
}