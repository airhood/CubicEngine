#pragma once

#include "glm.hpp"
#include "Component.h"

namespace CubicEngine {
	class Transform : public Component {
	public:
		Transform() = default;
		~Transform() override = default;

		void Destroy() override;

		void* Clone_Obj() override;
		Transform* Clone();

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::vec3 GetWorldPos();
		void SetWorldPos(glm::vec3);

		glm::vec3 front();
		glm::vec3 up();
		glm::vec3 right();

		const glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
	};
}