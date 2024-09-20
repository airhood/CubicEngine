#pragma once

#include "../CubicEngine.h"

#include "ManagerBase.h"
#include "../Object/GameInstance.h"

namespace CubicEngine {

	class GameInstance;

	namespace Core {
		class GameInstanceManager : public ManagerBase {
		public:
			explicit GameInstanceManager() = default;
			~GameInstanceManager();

		public:
			void Init() override;

			void Exterminate() override;

			void AddGameInstance(GameInstance* instance);

			void AddGameInstances(std::vector<GameInstance*> instances);

			void StartInstances();

			void PhysicsTickInstances(float elapsedTime);

			void FrameTickInstances(float elapsedTime);

			void LateTickInstances(float elapsedTime);

		private:
			std::vector<GameInstance*> game_instances;
		};
	}
}