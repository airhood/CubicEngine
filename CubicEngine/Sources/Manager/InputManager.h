#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <algorithm>

#include "ManagerBase.h"
#include "../Util/Key.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {
	namespace Input {
		class InputManager : public ManagerBase {
		public:
			explicit InputManager();
			~InputManager();

		public:
			void Init() override;

			void FrameTick(float elapsedTime) override;

			void Exterminate() override;

			bool GetKey(KeyCode key);
			bool GetKeyPress(KeyCode key);
			bool GetKeyRelease(KeyCode key);

			static const int glfw_keyCode[];
			std::vector<int> frame_pressed_keys;
			std::vector<int> frame_released_keys;
		};
	}
}