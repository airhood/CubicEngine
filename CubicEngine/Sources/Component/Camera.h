#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
// Component.h & Transform.h included in GameObject.h
// Cannot directly include Transform.h because it's incomplete
#include "../Component/Component.h"

namespace CubicEngine {
	class GameObject;

	class Camera : public Component {
	public:
		Camera() = default;
		~Camera() = default;

		void Destroy() override;

		void* Clone_Obj() override;
		Component* Clone_Comp() override;
		Camera* Clone();

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewProjectionMatrix();

		float fov, aspectRatio, nearPlane, farPlane;

	};
}