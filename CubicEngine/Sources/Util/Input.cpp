#include "Input.h"
#include "Logger.h"

using namespace CubicEngine;

static const std::string source = "Input.cpp";

InputManager* Input::inputManager = nullptr;

bool Input::GetKey(KeyCode key) {
	if (inputManager == nullptr) {
		Logger::Log(LogLevel::ERROR, "InputManager lost (inputManager is nullptr)", source);
		return false;
	}
	return inputManager->GetKey(key);
}

bool Input::GetKeyPress(KeyCode key) {
	if (inputManager == nullptr) {
		Logger::Log(LogLevel::ERROR, "InputManager lost (inputManager is nullptr)", source);
		return false;
	}
	return inputManager->GetKeyPress(key);
}

bool Input::GetKeyRelease(KeyCode key) {
	if (inputManager == nullptr) {
		Logger::Log(LogLevel::ERROR, "InputManager lost (inputManager is nullptr)", source);
		return false;
	}
	return inputManager->GetKeyRelease(key);
}
