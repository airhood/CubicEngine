#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ManagerBase.h"
#include "RenderBase.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {

	class Renderer;

	class RenderManager : public ManagerBase, public RenderBase {
	public:
		explicit RenderManager() = default;
		~RenderManager();

	public:
		void Init() override;

		void SetViewport();

		void Render() override;

		void Exterminate() override;

		void AddRenderer(Renderer* renderer);

		void OnRenderOrderChanged();

		static const char* vertex_shader;
		static const char* fragment_shader;

	private:
		std::vector<Renderer*> renderers;
	};
}