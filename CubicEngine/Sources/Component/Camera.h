#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
// Component.h & Transform.h included in GameObject.h
// Cannot directly include Transform.h because it's incomplete
#include "../Component/Component.h"

namespace CubicEngine {
	class GameObject;
	class Application;

	enum class ProjectionType {
		Perspective,
		Orthographic
	};

	class Camera : public Component {
	public:
		Camera();
		~Camera() = default;

		void Destroy() override;

		void* Clone_Obj() const override;
		Component* Clone_Comp() const override;
		Camera* Clone() const;

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewProjectionMatrix();

		ProjectionType projectionType = ProjectionType::Perspective;
		float fov = 45.0f, nearPlane = 0.1f, farPlane = 100.0f;

	private:
		Application* application;

		float aspectRatio;
	};
}