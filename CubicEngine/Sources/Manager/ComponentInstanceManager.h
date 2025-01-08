#pragma once

#include "ManagerBase.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {

	class ComponentInstanceManager : public ManagerBase {
	public:
		explicit ComponentInstanceManager() = default;
		~ComponentInstanceManager();

	public:
		void Init() override;

		void Start() override;

		void PhysicsTick(float elapsedTime) override;

		void FrameTick(float elapsedTime) override;

		void LateTick(float elapsedTime) override;

		void Exterminate() override;

	};
}