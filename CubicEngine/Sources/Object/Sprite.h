#pragma once

#include "Object.h"
#include "Texture2D.h"

namespace CubicEngine {
	class Sprite : public Object {
	public:
		Sprite() = default;
		~Sprite();

		void Destroy() override;
		
		void* Clone_Obj() override;

		Sprite* Clone();

		Texture2D* texture;
	};
}