#pragma once

#include "MacroDef.h"
#include "Application.h"

#include <iostream>

#define GET_FUNC(NAME, object)                                   \
NAME* Get##NAME##FUNC() const {                                  \
	if (typeid(NAME) == typeid(object)) {                        \
		return object;                                           \
	}                                                            \
	std::cout << "[GET_FUNC] Type not matching!" << std::endl;   \
}

#define CORE EngineCore::getInstance()
#define GET(NAME) Get##NAME##FUNC()

namespace CubicEngine {

	class Application;

	class EngineCore {
		DECLARE_SINGLETON(EngineCore);

	public:
		~EngineCore();

		void Init();

		Application* GetApplication();

	private:
		bool initialized = false;

	private:
		Application* application;
	};
}