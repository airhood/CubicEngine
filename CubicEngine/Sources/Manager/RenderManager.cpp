#include "RenderManager.h"

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

	// TODO: calculate render order. Layer->major, Render order->minor



	glfwSwapBuffers(CORE->window);
	glfwPollEvents();
}

void RenderManager::Exterminate() {

}

void RenderManager::AddRenderer(RenderBase* renderer) {
	renderers.push_back(renderer);
}