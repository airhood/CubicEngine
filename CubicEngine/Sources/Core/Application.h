#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "EngineCore.h"

#if defined(CORE_CLASS) || defined(APPLICATION_CPP)

namespace CubicEngine {
	class Application {
	public:
		Application();
		~Application();
		void Initialize();
		void Start();

		void setScreenSize(int width, int height);
		int getScreenWidth();
		int getScreenHeight();

		void setTitle(std::string title);
		std::string getTitle();

	private:
		bool initialized;
		int screen_width, screen_height;
		std::string title;

		// GL
		GLFWwindow* window;
		GLuint vertexbuffer;
		GLuint programID;
	};
}

#endif