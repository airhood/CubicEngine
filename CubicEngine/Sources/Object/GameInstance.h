#pragma once

#include "../Component/Component.h"
#include "Scene.h"

namespace CubicEngine {

	class Scene;

	class GameInstance : public Component {
	public:
		GameInstance();

		~GameInstance();

		Scene* scene;

		// Game Loop
		virtual void Start() = 0;

		virtual void PhysicsTick(float elapsedTime) = 0;

		virtual void FrameTick(float elapsedTime) = 0;

		virtual void Tick(float elapsedTime) = 0;
	};
}