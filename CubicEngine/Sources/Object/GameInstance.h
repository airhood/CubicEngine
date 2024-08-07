#pragma once

#include "../Component/Component.h"
#include "../Object/GameObject.h"

namespace CubicEngine {

	class Component;

	class GameObject;

	class GameInstance {
	public:
		GameInstance();

		~GameInstance();

		// game loop
		virtual void Start() {}

		virtual void PhysicsTick(float elapsedTime) {}

		virtual void FrameTick(float elapsedTime) {}

		virtual void LateTick(float elapsedTime) {}

		virtual void OnDestroy() {}

	public:
		Component* RootComponent() { return root_component; }

		int SceneNum() { return scene_num; }
		GameObject* RootGameObject() { return root_game_object; }

	private:
		friend class Component;
		Component* root_component;

		int scene_num;
		friend class GameObject;
		GameObject* root_game_object;
	};
}