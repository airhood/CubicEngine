#pragma once

#include "Object.h"
#include "Texture2D.h"
#include <glm.hpp>

namespace CubicEngine {
	class Sprite : public Object {
	public:
		Sprite() = default;
		~Sprite();

		void Destroy() override;
		
		void* Clone_Obj() const override;

		Sprite* Clone() const;

	public:
		Texture2D* texture;

		glm::vec2 pivot = glm::vec2(0.0f, 0.0f);

		int pixelsPerUnit = 100;
	};
}