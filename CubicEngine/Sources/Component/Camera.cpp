#include "Camera.h"
#include "../Object/GameObject.h"

using namespace CubicEngine;

void Camera::Destroy() {

}

void* Camera::Clone_Obj() {
	return Clone();
}

Component* Camera::Clone_Comp()
{
	return Clone();
}

Camera* Camera::Clone() {
	Camera* clone = new Camera();
	clone->fov = fov;
	clone->aspectRatio = aspectRatio;
	clone->nearPlane = nearPlane;
	clone->farPlane = farPlane;
	return clone;
}

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