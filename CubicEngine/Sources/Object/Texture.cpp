#include "Texture.h"

using namespace CubicEngine;

Format Texture::format() const {
	return _format;
}

void Texture::setCPUMemorySyncState(bool state) {
	cpuMemorySyncState = state;
}

bool Texture::getCPUMemorySyncState() const {
	return cpuMemorySyncState;
}