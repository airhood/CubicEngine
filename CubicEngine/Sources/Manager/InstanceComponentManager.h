#pragma once

#include "ManagerBase.h"
#include "../Component/InstanceComponent.h"

namespace CubicEngine {

	class InstanceComponent;

	class InstanceComponentManager : public ManagerBase {
	public:
		explicit InstanceComponentManager() = default;
		~InstanceComponentManager();

	public:
		void Init() override;

		void PhysicsTick(float elapsedTime) override;

		void FrameTick(float elapsedTime) override;

		void LateTick(float elapsedTime) override;

		void Exterminate() override;

		void AddGameInstance(InstanceComponent* instance_component);

		void StartInstances();

	private:
		std::vector<InstanceComponent*> instance_components;
	};
}