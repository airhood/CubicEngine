#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ManagerBase.h"
#include "RenderBase.h"
#include "../Util/Shader.h"

namespace CubicEngine {
	namespace Rendering {
		class RenderManager : public ManagerBase, public Rendering::RenderBase {
		public:
			explicit RenderManager(GLFWwindow* window);
			~RenderManager();

		public:
			void Init() override;
			void SetViewport();
			void Render() override;

			void Exterminate() override;

		private:
			GLFWwindow* window;
		};
	}
}