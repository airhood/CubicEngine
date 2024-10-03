#include "RenderManager.h"

using namespace CubicEngine::Rendering;

const char* RenderManager::vertex_shader = "Sources/Shader/vertexShader.glsl";
const char* RenderManager::fragment_shader = "Sources/Shader/fragmentShader.glsl";

RenderManager::~RenderManager() {
	Exterminate();
}

void RenderManager::Init() {
	shader = new Shader(vertex_shader, fragment_shader);
}

void RenderManager::SetViewport() {

}

void RenderManager::Render() {

	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers(CORE->window);
	glfwPollEvents();
}

void RenderManager::Exterminate() {

}