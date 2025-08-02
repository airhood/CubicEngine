#include "Camera.h"
#include "../Object/GameObject.h"
#include "../Core/EngineCore.h"

using namespace CubicEngine;

Camera::Camera() {
	this->application = CORE->GetApplication();
}

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
	auto root = RootGameObject();
	Transform* transform = root->GetComponent<Transform>();
	glm::vec3 pos = transform->position;
	glm::vec3 front = glm::normalize(transform->front());
	glm::vec3 up = glm::normalize(transform->up());

	return glm::lookAt(pos, pos + front, up);
}

glm::mat4 Camera::GetProjectionMatrix() {
	aspectRatio = (float)(application->GetResolutionWidth()) / (float)(application->GetResolutionWidth());
	return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);


	//float left = 0.0f;
	//float right = (float)application->GetResolutionWidth();
	//float bottom = 0.0f;
	//float top = (float)application->GetResolutionHeight();
	//float near = -1.0f;
	//float far = 1.0f;
	//return glm::ortho(left, right, bottom, top, near, far);
}

glm::mat4 Camera::GetViewProjectionMatrix() {
	return GetProjectionMatrix() * GetViewMatrix();
}