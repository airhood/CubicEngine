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

glm::vec2 Input::GetDirectional(bool normalize /*= true*/) {
	glm::vec2 dir(0.0f);

	if (Input::GetKey(KeyCode::W)) dir.y += 1.0f;
	if (Input::GetKey(KeyCode::S)) dir.y -= 1.0f;
	if (Input::GetKey(KeyCode::A)) dir.x -= 1.0f;
	if (Input::GetKey(KeyCode::D)) dir.x += 1.0f;

	if (Input::GetKey(KeyCode::Up))    dir.y += 1.0f;
	if (Input::GetKey(KeyCode::Down))  dir.y -= 1.0f;
	if (Input::GetKey(KeyCode::Left))  dir.x -= 1.0f;
	if (Input::GetKey(KeyCode::Right)) dir.x += 1.0f;

	if (!normalize) return dir;

	if (dir.x != 0.0f || dir.y != 0.0f) {
		dir = glm::normalize(dir);
	}
	return dir;
}


glm::vec2 Input::GetWASD(bool normalize /* = true */) {
	glm::vec2 dir(0.0f);

	if (Input::GetKey(KeyCode::W)) dir.y += 1.0f;
	if (Input::GetKey(KeyCode::S)) dir.y -= 1.0f;
	if (Input::GetKey(KeyCode::A)) dir.x -= 1.0f;
	if (Input::GetKey(KeyCode::D)) dir.x += 1.0f;

	if (!normalize) return dir;

	if (dir.x != 0.0f || dir.y != 0.0f) {
		dir = glm::normalize(dir);
	}
	return dir;
}

glm::vec2 Input::GetArrows(bool normalize /* = true */) {
	glm::vec2 dir(0.0f);
	if (Input::GetKey(KeyCode::Up))    dir.y += 1.0f;
	if (Input::GetKey(KeyCode::Down))  dir.y -= 1.0f;
	if (Input::GetKey(KeyCode::Left))  dir.x -= 1.0f;
	if (Input::GetKey(KeyCode::Right)) dir.x += 1.0f;

	if (normalize && (dir.x != 0.0f || dir.y != 0.0f)) {
		dir = glm::normalize(dir);
	}
	return dir;
}