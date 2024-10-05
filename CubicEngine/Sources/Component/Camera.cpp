#include "Camera.h"

using namespace CubicEngine;

void Camera::Render() {

}

glm::mat4 Camera::GetViewMatrix() {
	Transform* transform = RootGameObject()->GetComponent<Transform>();
	return glm::lookAt(transform->position, transform->position + transform->front(), transform->up());
}
