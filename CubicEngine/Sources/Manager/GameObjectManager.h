#pragma once

#include "ManagerBase.h"
#include "../Object/GameObject.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {

	class GameObject;

	namespace Core {
		class GameObjectManager : public ManagerBase {
		public:
			explicit GameObjectManager() = default;
			~GameObjectManager();

		public:
			void Init() override;

			void Exterminate() override;

		public:

		};
	}
}