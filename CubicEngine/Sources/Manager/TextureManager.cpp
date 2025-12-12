#include "TextureManager.h"
#include <iostream>
#include <format>
#include "../Object/Texture2D.h"

using namespace CubicEngine;

static const std::string source = "TextureManager.cpp";

TextureArray::TextureArray(int numLayers, GLsizei atlasSize) {
	this->numLayers = numLayers;
	this->atlasSize = atlasSize;
	for (int i = numLayers - 1; i >= 0; i--) {
		textures.push_back(nullptr);
		availableIndices.push_back(i);
	}
}

TextureManager::~TextureManager() {
	Exterminate();
}

void TextureManager::Init() {
	for (int i = init_size - 1; i >= 0; i--) {
		texture2Ds.push_back(nullptr);
		availableIndices.push_back(i);
	}
}

void TextureManager::Exterminate() {

}

void TextureManager::AllocTexture2D(Texture2D* texture) {
	int gl_format;
	switch (texture->_format) {
		case TextureFormat::RGBA:
			gl_format = GL_RGBA;
			break;
		case TextureFormat::RGB:
			gl_format = GL_RGB;
			break;
		case TextureFormat::GRAYSCALE:
			gl_format = GL_R8;
			break;
		default:
			return;
	}
	
	if (texture->gl_textureID == 0) {
		glGenTextures(1, &texture->gl_textureID);
	}

	auto max = [](int a, int b) {
		if (a > b) return a;
		return b;
		};

	glBindTexture(GL_TEXTURE_2D, texture->gl_textureID);
	glTexImage2D(GL_TEXTURE_2D, CalculateMipmapLevels(max(texture->width(), texture->height())), gl_format, texture->_width, texture->_height, 0, gl_format, GL_UNSIGNED_BYTE, texture->data_raw);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	int id = availableIndices.back();
	availableIndices.pop_back();

	texture2Ds[id] = texture;
	
	texture->textureSystemID = id;
}

void TextureManager::UpdateTexture2D(int id) {
	Texture2D* texture = texture2Ds[id];

	switch (texture->bindType) {
		case TextureBindType::INDIVIDUAL:
			if (texture == nullptr) {
				Logger::Log(LogLevel::ERROR, "[TextureManager] Invalid texture2d internal id.", source);
				return;
			}

			int gl_format;
			switch (texture->_format) {
				case TextureFormat::RGBA:
					gl_format = GL_RGBA;
					break;
				case TextureFormat::RGB:
					gl_format = GL_RGB;
					break;
				case TextureFormat::GRAYSCALE:
					gl_format = GL_R8;
					break;
				default:
					Logger::Log(LogLevel::ERROR, std::format("[TextureManager] Invalid TextureBindType {}", static_cast<int>(texture->bindType)), source);
					return;
			}

			glBindTexture(GL_TEXTURE_2D, texture->gl_textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, gl_format, texture->_width, texture->_height, 0, gl_format, GL_UNSIGNED_BYTE, texture->data_raw);

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
			
			break;
		case TextureBindType::ATLAS:
			if (texture->textureArray == nullptr) {
				Logger::Log(LogLevel::ERROR, "[TextureManager] Failed top release Texture2D. textureArray is null.", source);
				return;
			}
			TextureArrayUpdateTexture2D(texture->textureArray, texture->layerIndex);
			break;
		default:
			Logger::Log(LogLevel::ERROR, std::format("[TextureManager] Invalid TextureBindType {}", static_cast<int>(texture->bindType)), source);
			return;
	}
}

void TextureManager::ReleaseTexture2D(int id) {
	Texture2D* texture = texture2Ds[id];

	if (texture->bindType == TextureBindType::ATLAS) {
		if (texture->textureArray == nullptr) {
			Logger::Log(LogLevel::ERROR, "[TextureManager] Failed top release Texture2D. textureArray is null.", source);
			return;
		}
		TextureArrayUnregisterTexture2D(texture->textureArray, texture->layerIndex);
	}

	if (texture == nullptr) {
		Logger::Log(LogLevel::ERROR, "[TextureManager] Invalid texture2d internal id.", source);
		return;
	}

	GLuint& textureID = texture->gl_textureID;

	glDeleteTextures(1, &textureID);
	texture->gl_textureID = 0;

	texture2Ds[id] = nullptr;
	availableIndices.push_back(id);
}

TextureArray* TextureManager::AllocTextureArray(TextureType textureType, GLsizei initAtlasSize, int numLayers) {
	TextureArray* textureArray = new TextureArray(numLayers, initAtlasSize);
	textureArray->textureType = textureType;
	
	GLint maxLayers;
	glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &maxLayers);
	if (numLayers > maxLayers) {
		Logger::Log(LogLevel::ERROR, std::format("[TextureManager] New layer count exceeds OpenGL max limit of {}.", maxLayers), source);
		return nullptr;
	}

	GLuint textureArrayID;
	glGenTextures(1, &textureArrayID);
	textureArray->textureArrayID = textureArrayID;

	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayID);

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, CalculateMipmapLevels(initAtlasSize), GL_RGBA8, initAtlasSize, initAtlasSize, numLayers);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	return textureArray;
}

void TextureManager::TextureArrayRegisterTexture2D(TextureArray* textureArray, Texture2D* texture) {
	TextureType textureType = texture->GetTextureType();

	if (textureType != textureArray->textureType) {
		Logger::Log(LogLevel::ERROR, "[TextureManager] Cannot register texture to TextureArray with different TextureType.", source);
		return;
	}

	int layer_idx = textureArray->availableIndices.back();
	textureArray->availableIndices.pop_back();
	texture->layerIndex = layer_idx;
	textureArray->textures[layer_idx] = texture;

	GLsizei atlas_size = textureArray->atlasSize;

	auto max = [](int a, int b) {
		if (a > b) return a;
		return b;
		};

	if (texture->width() > atlas_size || texture->height() > atlas_size) {
		ResizeTexture2DArrayAtlas(textureArray, max(texture->width(), texture->height()));
	}

	GLuint& textureArrayID = textureArray->textureArrayID;
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
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
		return;
	}

	GenerateMipmapForLayer(textureArray, atlas_size, layer_idx);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	texture->textureArray = textureArray;
	texture->bindType = TextureBindType::ATLAS;
}

void TextureManager::TextureArrayUpdateTexture2D(TextureArray* textureArray, int layerIndex) {
	Texture2D* tex = textureArray->textures[layerIndex];
	TextureType textureType = textureArray->textureType;

	GLuint& textureArrayID = textureArray->textureArrayID;
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayID);

	glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
		0,
		0, 0, layerIndex,
		tex->width(), tex->height(), 1,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		textureArray->textures[layerIndex]->data_raw);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		Logger::Log(LogLevel::ERROR,
			std::format("[TextureManager] glTexSubImage3D failed: {}", error),
			source);
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
		return;
	}

	GenerateMipmapForLayer(textureArray, textureArray->atlasSize, layerIndex);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void TextureManager::TextureArrayUnregisterTexture2D(TextureArray* textureArray, int layerIndex) {
	Texture* texture = textureArray->textures[layerIndex];

	textureArray->textures[layerIndex] = nullptr;
	textureArray->availableIndices.push_back(layerIndex);
	
	texture->textureArray = nullptr;
}

void TextureManager::ResizeTexture2DStorage() {
	int oldSize = texture2Ds.size();
	int newSize = oldSize * 2;

	std::vector<int> newVec;
	for (int i = newSize - 1; i >= oldSize; i--) {
		texture2Ds.push_back(nullptr);
		newVec.push_back(i);
	}
	for (int i = 0; i < availableIndices.size(); i++) {
		newVec.push_back(availableIndices[i]);
	}

	availableIndices = newVec;
}

void TextureManager::ResizeTexture2DArrayLayer(TextureArray* textureArray) {
	TextureType textureType = textureArray->textureType;

	GLuint oldTextureID = textureArray->textureArrayID;
	if (oldTextureID == 0) {
		Logger::Log(LogLevel::ERROR, "[TextureManager] Cannot resize a non-existent texture array.", source);
		return;
	}

	GLsizei atlasSize = textureArray->atlasSize;

	GLsizei oldNumLayers = textureArray->numLayers;
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

	textureArray->textureArrayID = newTextureID;
	textureArray->numLayers = newNumLayers;

	glDeleteTextures(1, &oldTextureID);

	std::vector<int> newVec;
	for (int i = newNumLayers - 1; i >= oldNumLayers; i--) {
		newVec.push_back(i);
	}
	for (int i = 0; i < oldNumLayers; i++) {
		newVec.push_back(textureArray->availableIndices[i]);
	}

	textureArray->availableIndices = newVec;
}

void TextureManager::ResizeTexture2DArrayAtlas(TextureArray* textureArray, GLsizei newAtlasSize) {
	TextureType textureType = textureArray->textureType;

	GLuint oldTextureID = textureArray->textureArrayID;
	if (oldTextureID == 0) {
		Logger::Log(LogLevel::ERROR, "[TextureManager] Cannot resize a non-existent texture array.", source);
		return;
	}

	GLsizei oldAtlasSize = textureArray->atlasSize;
	GLsizei numLayers = textureArray->numLayers;

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
	
	textureArray->textureArrayID = newTextureID;
	textureArray->atlasSize = newAtlasSize;

	glDeleteTextures(1, &oldTextureID);
}

GLsizei TextureManager::CalculateMipmapLevels(GLsizei atlasSize) {
	return static_cast<GLsizei>(floor(log2(atlasSize))) + 1;
}

void TextureManager::GenerateMipmapForLayer(TextureArray* textureArray, GLsizei atlasSize, int layerIndex) {
	GLuint textureArrayID = textureArray->textureArrayID;
	
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
			textureArrayID, level, layerIndex);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFBO);
		glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			textureArrayID, nextLevel, layerIndex);

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