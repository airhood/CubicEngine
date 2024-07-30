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

		std::vector<GameObject*>* game_objects;

		void Init_() override;

		virtual void Init() = 0;

		// game loop
		virtual void Start() = 0;

		virtual void PhysicsTick(float elapsedTime) = 0;

		virtual void FrameTick(float elapsedTime) = 0;

		virtual void LateTick(float elapsedTime) = 0;

		virtual void OnDestroy() = 0;
	};
}