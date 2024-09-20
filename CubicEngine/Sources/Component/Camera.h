#pragma once

#include "../CubicEngine.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <typeinfo>

#include "Component.h"
#include "Transform.h"

namespace CubicEngine {
	namespace Rendering {
		class Camera : public Component {
			component();
		public:
			glm::mat4 GetViewMatrix();
		private:

		};
	}
}