#pragma once

#include "ManagerBase.h"

namespace CubicEngine {
	class PhysicsManager : public ManagerBase {
	public:
		explicit PhysicsManager() = default;
		~PhysicsManager();

		void PhysicsTick(float elapsedTime) override;

	private:
		void Init() override;

		void Exterminate() override;
	};
}