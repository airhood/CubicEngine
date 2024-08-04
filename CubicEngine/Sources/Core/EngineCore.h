#pragma once

#define CORE_CLASS

#include <iostream>
#include <vector>
#include "../Util/MacroDef.h"
#include "Application.h"
#include "../Manager/ManagerBase.h"

// Managers
#include "../Manager/InputManager.h"
#include "../Manager/RenderManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/GameInstanceManager.h"

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

	class SceneManager;

	class GameObjectManager;

	class GameInstanceManager;

	class EngineCore {
		DECLARE_SINGLETON(EngineCore);

	public:
		~EngineCore();

		Application* GetApplication();

		GLFWwindow* window;

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
		Manager(GameInstanceManager);

	private:
		Application* application;

		std::vector<ManagerBase*> managers;
		void CreateManagers();
		void CacheManagers();
		void InitManagers();
	};
}

#undef CORE_CLASS