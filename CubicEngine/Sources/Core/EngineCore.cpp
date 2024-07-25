#include "EngineCore.h"

using namespace CubicEngine;

IMPLEMENT_SINGLETON(EngineCore);

EngineCore::EngineCore() {

}

EngineCore::~EngineCore() {

}

void EngineCore::Init() {
	if (initialized) {
		// TODO: throw error: App already initialized
	}
	application = new Application();
	initialized = true;
}

Application* EngineCore::GetApplication() {
	return application;
}