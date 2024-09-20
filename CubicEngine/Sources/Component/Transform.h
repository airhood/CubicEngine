#pragma once

#include "../CubicEngine.h"

#include "glm.hpp"
#include "Component.h"

namespace CubicEngine {
	class Transform : public Component {
		component();
	public:
		Transform();
		~Transform() override = default;

		void Destroy() override;

		void* Clone_Obj() override;
		Transform* Clone();

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::vec3 GetWorldPosition();
		glm::vec3 GetWorldRotation();
		glm::vec3 GetWorldScale();
		void SetWorldPosition(glm::vec3);
		void SetWorldRotation(glm::vec3);
		void SetWorldScale(glm::vec3);

		glm::vec3 front();
		glm::vec3 up();
		glm::vec3 right();

		std::string ToString();

		const glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);

		Transform* parent() { return _parent; }

	private:
		friend class GameObject;
		Transform* _parent;
	};
}