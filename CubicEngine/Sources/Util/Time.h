#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace CubicEngine {
	class Time {
	public:
		static float time();

		static float physicsTime();
		static float frameTime();

		static void updatePhysicsTime();
		static void updateFrameTime();

		// delta time
		static float deltaPhysicsTime();
		static float deltaFrameTime();

	private:
		friend class EngineCore;
		static void init();

		static float initTime;

		static float currentPhysicsTime;
		static float currentFrameTime;
		static float lastPhysicsTime;
		static float lastFrameTime;
	};
}