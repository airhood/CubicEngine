#include "Camera.h"

using namespace CubicEngine;

glm::mat4 Camera::GetViewMatrix() {
	Transform* transform = RootGameObject()->GetComponent<Transform>();
	return glm::lookAt(transform->position, transform->position + transform->front(), transform->up());
}

glm::mat4 Camera::GetProjectionMatrix() {
	return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

glm::mat4 Camera::GetViewProjectionMatrix() {
	return GetProjectionMatrix() * GetViewMatrix();
}