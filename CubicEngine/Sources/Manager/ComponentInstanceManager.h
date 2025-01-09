#pragma once

#include "ManagerBase.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {

	class GameObject;

	class ComponentInstanceManager : public ManagerBase {
	public:
		explicit ComponentInstanceManager() = default;
		~ComponentInstanceManager();

	public:
		void Init() override;

		void Start() override;

		void PhysicsTick(float elapsed_time) override;

		void FrameTick(float elapsed_time) override;

		void LateTick(float elapsed_time) override;

		void Exterminate() override;

	private:
		void CallStart(GameObject* game_object);
		void CallPhysicsTick(float elapsed_time, GameObject* game_object);
		void CallFrameTick(float elapsed_time, GameObject* game_object);
		void CallLateTick(float elapsed_time, GameObject* game_object);

	};
}