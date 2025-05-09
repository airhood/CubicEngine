#pragma once

#define CORE_CLASS

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Util/Logger.h"

#include "../Util/MacroDef.h"
#include "Application.h"
#include "../Manager/ManagerBase.h"
#include "../Util/PointerHolder.h"
#include "../Util/Time.h"

// Managers
#include "../Manager/InputManager.h"
#include "../Manager/RenderManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ComponentInstanceManager.h"
#include "../Manager/LayerManager.h"

#define Manager(NAME)                                               \
public:                                                             \
	NAME* Get##NAME##FUNC() const {                                 \
		return obj_##NAME;                                          \
	}                                                               \
private:                                                            \
	NAME* obj_##NAME;

#define CORE CubicEngine::Core::EngineCore::getInstance()
#define GET(NAME) Get##NAME##FUNC()

namespace CubicEngine {

	class Application;

	class RenderBase;

	class InputManager;
	class RenderManager;
	class SceneManager;
	class ComponentInstanceManager;
	class LayerManager;

	namespace Core {
		class EngineCore {
			DECLARE_SINGLETON(EngineCore);

		public:
			~EngineCore();

			Application* GetApplication();

			GLFWwindow* window;

			void Init();
			void Start();
			void Quit();

			// game loop
			void PhysicsTick(float elapsedTime);
			void FrameTick(float elapsedTime);
			void LateTick(float elapsedTime);

			Manager(InputManager);
			Manager(RenderManager);
			Manager(SceneManager);
			Manager(ComponentInstanceManager);
			Manager(LayerManager);

		private:
			bool running = false;

			Application* application;

			void EngineMain();

			void Render();

			std::vector<ManagerBase*> managers;
			std::vector<RenderBase*> render_managers;
			void CreateManagers();
			void CacheManagers();
			void InitManagers();

		public:
			[[noreturn]] void Panic();
		};
	}
}

#undef CORE_CLASS