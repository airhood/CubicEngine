#pragma once

#include "../Component.h"
#include <glm.hpp>

namespace CubicEngine {
	class CircleCollider : public Component {
	public:
		CircleCollider() = default;
		~CircleCollider() = default;

		void Destroy() override;

		void* Clone_Obj() const override;
		Component* Clone_Comp() const override;
		CircleCollider* Clone() const;

	public:
		bool enable_interaction = true;

		float radius;
		glm::vec2 offset;
	};
}