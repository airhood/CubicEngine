#include "Texture.h"

using namespace CubicEngine;

TextureFormat Texture::format() const {
	return _format;
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

void Texture::Bind(int unit) const {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, gl_textureID);
}