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
	glm::vec3 front = glm::normalize(transform->Forward());
	glm::vec3 up = glm::normalize(transform->Up());

	glm::mat4 view_mat = glm::lookAt(pos, pos + front, up);
	return view_mat;
}

glm::mat4 Camera::GetProjectionMatrix() {
	glm::mat4 projection_mat;
	switch (projectionType) {
		case ProjectionType::Perspective:
			aspectRatio = (float)(application->GetResolutionWidth()) / (float)(application->GetResolutionHeight());
			projection_mat = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
			break;
		case ProjectionType::Orthographic:
			{
				// TODO: temp orthographic projection
				float left = 0.0f;
				float right = (float)application->GetResolutionWidth();
				float bottom = 0.0f;
				float top = (float)application->GetResolutionHeight();
				float near = -10.0f;
				float far = 10.0f;
				projection_mat = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, near, far);
			}
			break;
		default:
			Logger::Log(LogLevel::ERROR, "Not pre-defined projection type", source);
			projection_mat = glm::mat4();
			break;
	}

	projection_mat[0][0] *= -1;
	return projection_mat;
}

glm::mat4 Camera::GetViewProjectionMatrix() {
	return GetProjectionMatrix() * GetViewMatrix();
}