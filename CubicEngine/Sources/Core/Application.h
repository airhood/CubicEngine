#pragma once

#include <iostream>
#include "EngineCore.h"

#if defined(CORE_CLASS) || defined(APPLICATION_CPP)

namespace CubicEngine {

	struct Resolution {
		int width;
		int height;

		Resolution(int width, int height) : width(width), height(height) {}
	};

	class Application {
	public:
		Application();
		~Application();
		void Init();
		void Start();
		void Quit();

		void SetResolution(int width, int height);
		void SetResolution(Resolution resolution);
		Resolution GetResolution();
		int GetResolutionWidth();
		int GetResolutionHeight();
		void SetFPS(int fps);
		int GetFPS();

		void SetTitle(std::string title);
		std::string GetTitle();

	private:
		bool initialized;
		Resolution resolution = Resolution(1920, 1080);
		int fps = 60;
		std::string title;

		void ApplyResolution();

		// GL
		GLFWwindow* window;
		GLuint vertexbuffer;
		GLuint programID;
	};
}

#endif