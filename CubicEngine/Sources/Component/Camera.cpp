#include "Camera.h"
#include "../Object/GameObject.h"
#include "../Core/EngineCore.h"

using namespace CubicEngine;

static const std::string source = "Camera.cpp";

Camera::Camera() {
	this->application = CORE->GetApplication();
}

void Camera::Destroy() {

}

void* Camera::Clone_Obj() const {
	return Clone();
}

Component* Camera::Clone_Comp() const {
	return Clone();
}

Camera* Camera::Clone() const {
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
	switch (projectionType) {
		case ProjectionType::Perspective:
			aspectRatio = (float)(application->GetResolutionWidth()) / (float)(application->GetResolutionHeight());
			return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
		case ProjectionType::Orthographic:
			{
				// TODO: temp orthographic projection
				float left = 0.0f;
				float right = (float)application->GetResolutionWidth();
				float bottom = 0.0f;
				float top = (float)application->GetResolutionHeight();
				float near = -10.0f;
				float far = 10.0f;
				return glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, near, far);
			}
		default:
			Logger::Log(LogLevel::ERROR, "Not pre-defined projection type", source);
			return glm::mat4();
	}
}

glm::mat4 Camera::GetViewProjectionMatrix() {
	return GetProjectionMatrix() * GetViewMatrix();
}