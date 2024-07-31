#pragma once

#define CORE_CLASS

#include <iostream>
#include <vector>
#include "../Util/MacroDef.h"
#include "Application.h"

// Managers
#include "../Manager/ManagerBase.h" // Base
#include "../Manager/InputManager.h"
#include "../Manager/RenderManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/GameObjectManager.h"

#define Manager(NAME)                                               \
public:                                                             \
	NAME* Get##NAME##FUNC() const {                                 \
		return obj_##NAME;                                          \
	}                                                               \
private:                                                            \
	NAME* obj_##NAME;

#define CORE EngineCore::getInstance()
#define GET(NAME) Get##NAME##FUNC()

namespace CubicEngine {

	using namespace Input;
	using namespace Rendering;
	
	class Application;

	enum class TickCycleOrder {
		FH, // Start from the first game object and process components at high hierarchy first
		FL, // Start from the first game object and process components at low hierarchy first
		LH, // Start from the last game object and process components at high hierarchy first
		LL  // Start from the last game object and process components at low hierarchy first
	};

	class GameObjectManager;

	class EngineCore {
		DECLARE_SINGLETON(EngineCore);

	public:
		~EngineCore();

		Application* GetApplication();

		void Init();
		void Start();

		// game loop
		void GameLoop();
		void PhysicsTick(float elapsedTime);
		void FrameTick(float elapsedTime);
		void LateTick(float elapsedTime);

		Manager(InputManager);
		Manager(RenderManager);
		Manager(SceneManager);
		Manager(GameObjectManager);

	public:
		bool initialized = false;
		TickCycleOrder tick_cycle_order = TickCycleOrder::FH;
		Application* application;

		std::vector<ManagerBase*> managers;
		void CacheManagers();
	};
}

#undef CORE_CLASS