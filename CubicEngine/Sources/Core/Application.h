#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../shader.h"
#include "../Manager/InputManager.h"

namespace CubicEngine {

	class InputManager;

	class Application {
	protected:
		GLFWwindow* window;
		InputManager* input;

	public:
		Application();
		~Application();
		void Initialize();
		void Start();

		void setTitle(std::string title);
		std::string getTitle();

	private:

	private:
		bool initialized;
		std::string title;
		GLuint vertexbuffer;
		GLuint programID;
	};
}