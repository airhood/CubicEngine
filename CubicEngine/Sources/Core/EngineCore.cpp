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

void EngineCore::Start() {

}

void EngineCore::PhysicsTick(float elapsedTime) {
	for (auto& manager : managers) {
		manager->PhysicsTick(elapsedTime);
	}
}

void EngineCore::FrameTick(float elapsedTime) {
	for (auto& manager : managers) {
		manager->FrameTick(elapsedTime);
	}
}

void EngineCore::LateTick(float elapsedTime) {
	for (auto& manager : managers) {
		manager->LateTick(elapsedTime);
	}
}

Application* EngineCore::GetApplication() {
	return application;
}

void CubicEngine::EngineCore::CacheManagers()
{
	managers.push_back(obj_InputManager);
	managers.push_back(obj_RenderManager);
}
