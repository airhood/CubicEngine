#pragma once

#include "../Util/MacroDef.h"
#include "Application.h"

#include <iostream>

// Managers
#include "../Manager/InputManager.h"
#include "../Manager/RenderManager.h"

#define GET_FUNC(NAME, object)                                              \
NAME* Get##NAME##FUNC() const {                                             \
	if (typeid(NAME) == typeid(object)) {                                   \
		return object;                                                      \
	}                                                                       \
	std::cout << "[GET_FUNC] Type not matching!" << std::endl;              \
}

#define CORE EngineCore::getInstance()
#define GET(NAME) Get##NAME##FUNC()

namespace CubicEngine {

	class Application;
	
	class Input::InputManager;
	class Rendering::RenderManager;

	using namespace Input;
	using namespace Rendering;

	class EngineCore {
		DECLARE_SINGLETON(EngineCore);

	public:
		~EngineCore();

		void Init();

		Application* GetApplication();

		GET_FUNC(InputManager, inputManager);
		GET_FUNC(RenderManager, renderManager);

	private:
		bool initialized = false;

	private:
		Application* application;

		Input::InputManager* inputManager;
		Rendering::RenderManager* renderManager;
	};
}