#define APPLICATION_CPP

#include "Application.h"

using namespace CubicEngine;
using namespace CubicEngine::Core;

Application::Application() {

}

Application::~Application() {

}

void Application::Init() {
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Mac OS only

	window = glfwCreateWindow(resolution.width, resolution.height, title.c_str(), NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	};
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return;
	}
	
	glfwSwapInterval(1);

	CORE->window = window;
	CORE->Init();
}

void Application::Start() {
	CORE->Start();
}

void Application::Quit() {
	CORE->Quit();
	glfwTerminate();
}

void Application::SetResolution(int width, int height) {
	resolution.width = width;
	resolution.height = height;
}

void Application::SetResolution(Resolution resolution) {
	this->resolution = resolution;
}

void Application::ApplyResolution() {
	glfwSetWindowSize(window, resolution.width, resolution.height);
	glViewport(0, 0, resolution.width, resolution.height);
}

Resolution Application::GetResolution() {
	return resolution;
}

int Application::GetResolutionWidth() {
	return resolution.width;
}

int Application::GetResolutionHeight() {
	return resolution.height;
}

void Application::SetFPS(int fps) {
	this->fps = fps;
}

int Application::GetFPS() {
	return fps;
}

void Application::SetTitle(std::string title) {
	this->title = title;
	glfwSetWindowTitle(window, title.c_str());
}

std::string Application::GetTitle() {
	return title;
}

#undef APPLICATION_CPP