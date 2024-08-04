#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ManagerBase.h"

namespace CubicEngine {
	namespace Input {
		enum class KeyCode {
			Space,
			Apostrophe,
			Comma,
			Minus,
			Period,
			Slash,
			Alpha_0,
			Alpha_1,
			Alpha_2,
			Alpha_3,
			Alpha_4,
			Alpha_5,
			Alpha_6,
			Alpha_7,
			Alpha_8,
			Alpha_9,
			Semicolon,
			Equal,
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			LeftBracket,
			Backslash,
			RightBracket,
			GraveAccent,
			World1, // ?
			World2, // ?

			Escape,
			Enter,
			Tab,
			Backspace,
			Insert,
			Delete,
			Right,
			Left,
			Down,
			Up,
			PageUp,
			PageDown,
			Home,
			End,
			CapsLock,
			ScrollLock,
			NumLock,
			PrintScreen,
			Pause,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			F16,
			F17,
			F18,
			F19,
			F20,
			F21,
			F22,
			F23,
			F24,
			F25,
			Keypad_0,
			Keypad_1,
			Keypad_2,
			Keypad_3,
			Keypad_4,
			Keypad_5,
			Keypad_6,
			Keypad_7,
			Keypad_8,
			Keypad_9,
			Keypad_Decimal,
			Keypad_Divide,
			Keypad_Multiply,
			Keypad_Substract,
			Keypad_Add,
			Keypad_Enter,
			Keypad_Equal,
			LeftShift,
			LeftControl,
			LeftAlt,
			LeftSuper,
			RightShift,
			RightControl,
			RightAlt,
			RightSuper,
			Menu
		};

		class InputManager : public ManagerBase {
		public:
			explicit InputManager(GLFWwindow* window);
			~InputManager();

		public:
			void Init() override;

			void Exterminate() override;

			bool GetKey(KeyCode key);

		private:
			GLFWwindow* window;
			static const int glfw_keyCode[];
		};
	}
}