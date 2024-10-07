#pragma once

#include "../Object/Scene.h"
#include "../Component/Component.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {

	class Scene;

	class InstanceComponent abstract : public Component {
	public:
		InstanceComponent();

		~InstanceComponent();

		// game loop
		virtual void Start() {}
		virtual void PhysicsTick(float elapsedTime) {}
		virtual void FrameTick(float elapsedTime) {}
		virtual void LateTick(float elapsedTime) {}

		virtual void OnDestroy() {}

		Scene* RootScene();
		Scene* CurrentScene();
		Scene* GetScene(int scene_num);
	};
}