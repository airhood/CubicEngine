#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <typeinfo>
// Component.h & Transform.h included in GameObject.h
// Cannot directly include Transform.h because it's incomplete
#include "../Object/GameObject.h"

namespace CubicEngine {
	class Camera : public Component {
	public:
		Camera() = default;

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewProjectionMatrix();

		float fov, aspectRatio, nearPlane, farPlane;

	};
}