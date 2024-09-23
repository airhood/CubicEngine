#pragma once

#include "../CubicEngine.h"

#include <iostream>
#include "EngineCore.h"

#if defined(CORE_CLASS) || defined(APPLICATION_CPP)

namespace CubicEngine {

	struct Resolution {
		int width;
		int height;
	};

	class Application {
	public:
		Application();
		~Application();
		void Init();
		void Start();

		void SetResolution(int width, int height);
		void SetResolution(Resolution resolution);
		Resolution GetResolution();
		int GetResolutionWidth();
		int GetResolutionHeight();

		void SetTitle(std::string title);
		std::string GetTitle();

	private:
		bool initialized;
		Resolution resolution;
		std::string title;

		void ApplyResolution();

		// GL
		GLFWwindow* window;
		GLuint vertexbuffer;
		GLuint programID;
	};
}

#endif