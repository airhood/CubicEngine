#include "Texture.h"

using namespace CubicEngine;

TextureFormat Texture::format() const {
	return _format;
}

void Texture::SetTextureType(TextureType textureType) {
	// TODO: OnTypeChange()
	this->textureType = textureType;
}

TextureType Texture::GetTextureType() const {
	return textureType;
}

void Texture::setCPUMemorySyncState(bool state) {
	cpuMemorySyncState = state;
	if (state) {
		SyncMemory();
	}
}

bool Texture::getCPUMemorySyncState() const {
	return cpuMemorySyncState;
}