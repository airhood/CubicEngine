#pragma once

#include "../Component/Component.h"
#include "Scene.h"
#include "GameObject.h"

namespace CubicEngine {

	class GameObject;

	class GameInstance : public Component {
	public:
		GameInstance();

		~GameInstance();

		// game loop
		virtual void Start() {}

		virtual void PhysicsTick(float elapsedTime) {}

		virtual void FrameTick(float elapsedTime) {}

		virtual void LateTick(float elapsedTime) {}

		virtual void OnDestroy() {}
	};
}