#pragma once

#include "../CubicEngine.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ManagerBase.h"
#include "RenderBase.h"
#include "../Util/Shader.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {
	namespace Rendering {
		class RenderManager : public ManagerBase, public Rendering::RenderBase {
		public:
			explicit RenderManager() = default;
			~RenderManager();

		public:
			void Init() override;
			void SetViewport();
			void Render() override;

			void Exterminate() override;

		private:
			Shader* shader;
		};
	}
}