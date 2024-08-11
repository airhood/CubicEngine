#include "RenderManager.h"

using namespace CubicEngine::Rendering;

RenderManager::~RenderManager() {
	Exterminate();
}

void RenderManager::Init() {
	shader = new Shader("Sources/vertexShader.glsl", "Sources/fragmentShader.glsl");

	auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	};
	glfwSetFramebufferSizeCallback(CORE->window, framebuffer_size_callback);

	glClearColor(0, 0, 0, 0);
}

void RenderManager::SetViewport() {

}

void RenderManager::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glfwSwapBuffers(CORE->window);
	glfwPollEvents();
}

void RenderManager::Exterminate() {

}