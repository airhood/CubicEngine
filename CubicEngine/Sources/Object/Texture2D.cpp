#include "Texture2D.h"
#include <algorithm>
#include "../Util/Logger.h"
#include "../Core/EngineCore.h"

using namespace CubicEngine;

static const std::string source = "Texture2D.cpp";

Texture2D::Texture2D(int width, int height) {
	_width = width;
	_height = height;
	data = new Color[width * height];

	CORE->GET(TextureManager)->RegisterTexture2D(this);
}

void* Texture2D::Clone_Obj() const {
	return Clone();
}

Texture2D* Texture2D::Clone() const {
	Texture2D* texture2d = new Texture2D(_width, _height);
	texture2d->data = new Color[_width * _height];
	for (int i = 0; i < (_width * _height); i++) {
		texture2d->data[i] = data[i];
	}
	texture2d->_format = _format;
	texture2d->cpuMemorySyncState = cpuMemorySyncState;

	int channelCount;
	switch (_format) {
		case TextureFormat::RGBA:
			channelCount = 4;
			break;
		case TextureFormat::RGB:
			channelCount = 3;
			break;
		case TextureFormat::GRAYSCALE:
			channelCount = 1;
			break;
		default:
			return nullptr;
	}

	size_t dataSize = static_cast<size_t>(_width * _height * channelCount);

	texture2d->data_raw = new unsigned char[dataSize];
	std::memcpy(texture2d->data_raw, data_raw, dataSize);

	return texture2d;
}

int Texture2D::width() const {
	return _width;
}

int Texture2D::height() const {
	return _height;
}

void Texture2D::SetPixel(int x, int y, Color color) const {
	if (!cpuMemorySyncState) {
		Logger::Log(LogLevel::ERROR, "Texture modify is only available when cpuMemorySyncState is activated", source);
		return;
	}
	data[y * _width + x] = color;
}

Color Texture2D::GetPixel(int x, int y) const {
	if (!cpuMemorySyncState) {
		Logger::Log(LogLevel::ERROR, "Texture modify is only available when cpuMemorySyncState is activated", source);
		return Color();
	}
	return data[y * _width + x];
}

void Texture2D::Apply() {
	if (cpuMemorySyncState) {
		unsigned char* textureData = ConvertData();
		delete[] data_raw;
		data_raw = textureData;
	}
	Load();
}

void Texture2D::Load(unsigned char* load_data) {
	int channelCount;
	int gl_format;
	switch (_format) {
		case TextureFormat::RGBA:
			channelCount = 4;
			gl_format = GL_RGBA;
			break;
		case TextureFormat::RGB:
			channelCount = 3;
			gl_format = GL_RGB;
			break;
		case TextureFormat::GRAYSCALE:
			channelCount = 1;
			gl_format = GL_R8;
			break;
		default:
			return;
	}

	size_t dataSize = static_cast<size_t>(_width * _height * channelCount);

	if (data_raw) {
		delete[] data_raw;
	}

	data_raw = new unsigned char[dataSize];
	std::memcpy(data_raw, load_data, dataSize);

	if (cpuMemorySyncState) {
		SyncMemory();
	}

	CORE->GET(TextureManager)->UpdateTexture2D(textureType, layerIndex);
}

void Texture2D::Release() {
	CORE->GET(TextureManager)->ReleaseTexture2D(textureType, layerIndex);
	_width = 0;
	_height = 0;
}

void Texture2D::Load() {
	int gl_format;
	switch (_format) {
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

	CORE->GET(TextureManager)->UpdateTexture2D(textureType, layerIndex);
}

unsigned char* Texture2D::ConvertData() const {
	int channel;
	switch (_format) {
		case TextureFormat::RGBA:
			channel = 4;
			break;
		case TextureFormat::RGB:
			channel = 3;
			break;
		case TextureFormat::GRAYSCALE:
			channel = 1;
			break;
		default:
			return nullptr;
	}

	unsigned char* textureData = new unsigned char[_width * _height * channel];

	for (int i = 0; i < _width * _height; ++i) {
		textureData[i * 4] = static_cast<unsigned char>(std::clamp(data[i].r * 255.0f, 0.0f, 255.0f));
		textureData[i * 4 + 1] = static_cast<unsigned char>(std::clamp(data[i].g * 255.0f, 0.0f, 255.0f));
		textureData[i * 4 + 2] = static_cast<unsigned char>(std::clamp(data[i].b * 255.0f, 0.0f, 255.0f));
		textureData[i * 4 + 3] = static_cast<unsigned char>(std::clamp(data[i].a * 255.0f, 0.0f, 255.0f));
	}

	return textureData;
}

void Texture2D::SyncMemory() {
	if (data_raw == nullptr) return;
	for (int i = 0; i < _width * _height; i++) {
		data[i].r = data_raw[i * 4] / 255.0f;
		data[i].g = data_raw[i * 4 + 1] / 255.0f;
		data[i].b = data_raw[i * 4 + 2] / 255.0f;
		data[i].a = data_raw[i * 4 + 3] / 255.0f;
	}
}