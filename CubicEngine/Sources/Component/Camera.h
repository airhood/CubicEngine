#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <typeinfo>
#include "../Manager/RenderBase.h"
// Component.h & Transform.h included in GameObject.h
// Cannot directly include Transform.h because it's incomplete
#include "../Object/GameObject.h"

namespace CubicEngine {
	class Camera : public Component, RenderBase {
	public:
		Camera() = default;

		void Render() override;

		glm::mat4 GetViewMatrix();
	private:

	};
}