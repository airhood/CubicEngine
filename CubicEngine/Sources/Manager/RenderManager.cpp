#include "RenderManager.h"
#include "../Component/Renderer.h"
#include <algorithm>

using namespace CubicEngine;

const char* RenderManager::vertex_shader = "Sources/Shader/vertexShader.glsl";
const char* RenderManager::fragment_shader = "Sources/Shader/fragmentShader.glsl";

RenderManager::~RenderManager() {
	Exterminate();
}

void RenderManager::Init() {

}

void RenderManager::SetViewport() {

}

void RenderManager::Render() {
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderCamera(camera);

	glfwSwapBuffers(CORE->window);
	glfwPollEvents();
}

void RenderManager::RenderCamera(Camera* camera) {
	for (auto& renderer : renderers) {
		renderer->Render(camera);
	}
}

void RenderManager::Exterminate() {

}

void RenderManager::SetCamera(Camera* camera) {
	this->camera = camera;
}

void RenderManager::AddRenderer(Renderer* renderer) {
	renderers.push_back(renderer);
	OnRenderOrderChanged();
}

void RenderManager::RemoveRenderer(Renderer* renderer) {
	renderers.erase(std::remove(renderers.begin(), renderers.end(), renderer));
}

void RenderManager::OnRenderOrderChanged() {
	auto compare = [](Renderer* a, Renderer* b) -> bool {
		return a->GetRenderOrder() < b->GetRenderOrder();
	};

	std::sort(renderers.begin(), renderers.end(), compare);
}