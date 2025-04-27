#define APPLICATION_CPP

#include "Application.h"

using namespace CubicEngine;
using namespace CubicEngine::Core;

static const std::string source = "Application.cpp";

Application::Application() {

}

Application::~Application() {
	Logger::Log(LogLevel::DEBUG, "[Core] Application instance deleting.", source);
}

void Application::Init() {
	Logger::Log(LogLevel::DEBUG, "[Core] Application initializing.", source);
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Mac OS only
	Logger::Log(LogLevel::DEBUG, "[Core] GLFW initialized.", source);

	window = glfwCreateWindow(resolution.width, resolution.height, title.c_str(), NULL, NULL);
	Logger::Log(LogLevel::DEBUG, "[Core] Created GLFW window.", source);

	if (window == NULL) {
		Logger::Log(LogLevel::ERROR, "[Core] Failed to open GLFW window.", source);
		glfwTerminate();
		Logger::Log(LogLevel::DEBUG, "[Core] Terminated GLFW.", source);
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
		Logger::Log(LogLevel::ERROR, "[Core] Failed to initialize GLEW.", source);
		glfwTerminate();
		Logger::Log(LogLevel::DEBUG, "[Core] Terminated GLFW.", source);
		return;
	}
	
	glfwSwapInterval(1);

	CORE->window = window;
	CORE->Init();
}

void Application::Start() {
	Logger::Log(LogLevel::DEBUG, "[Core] Application start.", source);
	CORE->Start();
}

void Application::Quit() {
	Logger::Log(LogLevel::DEBUG, "[Core] Application quit.", source);
	CORE->Quit();
	glfwTerminate();
	Logger::Log(LogLevel::DEBUG, "[Core] Terminated GLFW.", source);
}

void Application::SetResolution(int width, int height) {
	resolution.width = width;
	resolution.height = height;
	ApplyResolution();
	Logger::Log(LogLevel::INFO, fmt::format("[App] Window resolution set to (width: {}, height: {}).", width, height), source);
}

void Application::SetResolution(Resolution resolution) {
	this->resolution = resolution;
	ApplyResolution();
	Logger::Log(LogLevel::INFO, fmt::format("[App] Window resolution set to (width: {}, height: {}).", resolution.width, resolution.height), source);
}

void Application::ApplyResolution() {
	glfwSetWindowSize(window, resolution.width, resolution.height);
	glViewport(0, 0, resolution.width, resolution.height);
	Logger::Log(LogLevel::DEBUG, "[App] Applied window resolution.", source);
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
	Logger::Log(LogLevel::DEBUG, fmt::format("[App] Set title to {}", title), source);
}

std::string Application::GetTitle() {
	return title;
}

#undef APPLICATION_CPP