#pragma once

#include "Texture.h"

namespace CubicEngine {
	class Texture2D : public Texture {
	public:
		Texture2D(int width, int height);
		
		void SetPixel(int x, int y, Color color) const;
		Color GetPixel(int x, int y) const;

		void Apply() override;

		void Load(unsigned char* data);

		void Release();

	private:
		int _width;
		int _height;

		unsigned char* ConvertData() const;
	};
}