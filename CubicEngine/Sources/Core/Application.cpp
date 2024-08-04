#define APPLICATION_CPP

#include "Application.h"

using namespace CubicEngine;

Application::Application() {

}

Application::~Application() {

}

void Application::Init() {
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Mac OS only

	window = glfwCreateWindow(1920, 1080, "CubicEngine", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return;
	}

	glViewport(0, 0, screen_width, screen_height);
	
	glfwSwapInterval(1);

	CORE->window = window;
	CORE->Init();
}

void Application::Start() {
	CORE->Start();
}

void Application::setScreenSize(int width, int height) {
	screen_width = width;
	screen_height = height;
	glfwSetWindowSize(window, screen_width, screen_height);
	glViewport(0, 0, screen_width, screen_height);
}

int Application::getScreenWidth() {
	return screen_width;
}

int Application::getScreenHeight() {
	return screen_height;
}

void Application::setTitle(std::string title) {
	this->title = title;
	glfwSetWindowTitle(window, title.c_str());
}

std::string Application::getTitle() {
	return title;
}

#undef APPLICATION_CPP