#include "Texture2D.h"
#include <algorithm>

using namespace CubicEngine;

Texture2D::Texture2D(int width, int height) {
	_width = width;
	_height = height;
	data = new Color[width * height];
}

void* Texture2D::Clone_Obj() {
	return Clone();
}

Texture2D* Texture2D::Clone() {
	Texture2D* texture2d = new Texture2D();
	texture2d->_width = _width;
	texture2d->_height = _height;
	texture2d->data = new Color[_width * _height];
	for (int i = 0; i < (_width * _height); i++) {
		texture2d->data[i] = data[i];
	}
	texture2d->_format = _format;
	texture2d->cpuMemorySyncState = cpuMemorySyncState;

	return texture2d;
}

void Texture2D::SetPixel(int x, int y, Color color) const {
	if (!cpuMemorySyncState) {
		// TODO: throw error
		return;
	}
	data[y * _width + x] = color;
}

Color Texture2D::GetPixel(int x, int y) const {
	if (!cpuMemorySyncState) {
		// TODO: throw error
		return Color();
	}
	return data[y * _width + x];
}

void Texture2D::Apply() {
	Load(ConvertData());
}

void Texture2D::Load(unsigned char* data) {
	if (gl_textureID != 0) Release();
	
	glGenTextures(1, &gl_textureID);
	glBindTexture(GL_TEXTURE_2D, gl_textureID);

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

	glTexImage2D(GL_TEXTURE_2D, 0, gl_format, _width, _height, 0, gl_format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::Release() {
	glDeleteTextures(1, &gl_textureID);
	gl_textureID = 0;
	_width = 0;
	_height = 0;
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