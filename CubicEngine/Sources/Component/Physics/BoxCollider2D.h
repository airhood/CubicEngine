#pragma once

#include "../Component.h"
#include <glm.hpp>

namespace CubicEngine {
	class BoxCollider2D : public Component {
	public:
		BoxCollider2D() = default;
		~BoxCollider2D() = default;

		void Destroy() override;

		void* Clone_Obj() const override;
		Component* Clone_Comp() const override;
		BoxCollider2D* Clone() const;

	public:
		bool enable_interaction = true;

		glm::vec2 size;
		glm::vec2 offset;
	};
}