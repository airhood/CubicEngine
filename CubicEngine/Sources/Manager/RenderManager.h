#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ManagerBase.h"
#include "RenderBase.h"
#include "../Object/Shader.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {
	class RenderManager : public ManagerBase, public RenderBase {
	public:
		explicit RenderManager() = default;
		~RenderManager();

	public:
		void Init() override;

		void SetViewport();

		void Render() override;

		void Exterminate() override;

		void AddRenderer(RenderBase* renderer);

		static const char* vertex_shader;
		static const char* fragment_shader;

	private:
		Shader* shader;

		std::vector<RenderBase*> renderers;
	};
}