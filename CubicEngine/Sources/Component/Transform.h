#pragma once

#include <glm.hpp>
#include "Component.h"

namespace CubicEngine {
	class Transform : public Component {
	public:
		Transform();
		~Transform() override = default;

		void Destroy() override;

		void* Clone_Obj() const override;
		Component* Clone_Comp() const override;
		Transform* Clone() const;

		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::vec3 GetWorldPosition();
		glm::vec3 GetWorldRotation();
		glm::vec3 GetWorldScale();
		void SetWorldPosition(glm::vec3);
		void SetWorldRotation(glm::vec3);
		void SetWorldScale(glm::vec3);

		glm::mat4 RotationMatrix() const;

		glm::vec3 Forward() const;
		glm::vec3 Up() const;
		glm::vec3 Right() const;

		std::string ToString();

		const glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);

		Transform* parent() { return _parent; }

	private:
		friend class GameObject;
		Transform* _parent;

		friend class Renderer;
		friend class Renderer2D;
		friend class MeshRenderer;
		glm::mat4 GetModelMatrix() const;
	};
}