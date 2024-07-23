#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"

#include "Input.h"

namespace CubicEngine {
	class Application {
	protected:
		GLFWwindow* window;
		Input* input;

	public:
		Application();
		~Application();
		void Initialize();
		void Start();

		void setTitle(std::string title);
		std::string getTitle();

	private:
		bool initialized;
		std::string title;
		GLuint vertexbuffer;
		GLuint programID;
	};
}