#pragma once

#include "../Manager/InputManager.h"

namespace CubicEngine {
	class Input {
	public:
		static bool GetKey(KeyCode key);
		static bool GetKeyPress(KeyCode key);
		static bool GetKeyRelease(KeyCode key);

		glm::vec2 GetDirectional(bool normalize = true);
		static glm::vec2 GetWASD(bool normalize = true);
        static glm::vec2 GetArrows(bool normalize = true);

	private:
		friend class CubicEngine::Core::EngineCore;
		static InputManager* inputManager;
	};
}