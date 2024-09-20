#pragma once

#include "../CubicEngine.h"

#include <iostream>
#include "EngineCore.h"

#if defined(CORE_CLASS) || defined(APPLICATION_CPP)

namespace CubicEngine {
	class Application {
	public:
		Application();
		~Application();
		void Init();
		void Start();

		void setScreenSize(int width, int height);
		int getScreenWidth() { return screen_width; }
		int getScreenHeight() { return screen_height; }

		void setTitle(std::string title);
		std::string getTitle() { return title; }

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