#pragma once

#include "../Manager/InputManager.h"

namespace CubicEngine {
	class Input {
	public:
		static bool GetKey(KeyCode key);
		static bool GetKeyPress(KeyCode key);
		static bool GetKeyRelease(KeyCode key);

	private:
		friend class CubicEngine::Core::EngineCore;
		static InputManager* inputManager;
	};
}