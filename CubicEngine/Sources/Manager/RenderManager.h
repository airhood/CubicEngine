#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "CoreBase.h"
#include "RenderBase.h"

namespace CubicEngine {
	namespace Rendering {
		class RenderManager : public CoreBase, Rendering::RenderBase {
		public:
			explicit RenderManager() = default;
			~RenderManager();

		public:
			void Init() override;
			void SetViewport();
			void Render() override;

			void Exterminate() override;
		};
	}
}