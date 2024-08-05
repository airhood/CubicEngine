#include "EngineCore.h"

using namespace CubicEngine;

IMPLEMENT_SINGLETON(EngineCore);

EngineCore::EngineCore() {
	application = new Application();
}

EngineCore::~EngineCore() {

}

void EngineCore::Init() {
	glfwSetWindowUserPointer(window, new PointerHolder());
	CreateManagers();
	CacheManagers();
	InitManagers();
}

void EngineCore::Start() {
	obj_GameInstanceManager->StartInstances();
}

void EngineCore::GameLoop() {

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

void CubicEngine::EngineCore::CreateManagers()
{
	obj_InputManager = new InputManager();
	obj_RenderManager = new RenderManager();
	obj_SceneManager = new SceneManager();
	obj_GameObjectManager = new GameObjectManager();
	obj_GameInstanceManager = new GameInstanceManager();
}

void EngineCore::CacheManagers()
{
	managers.push_back(obj_InputManager);
	managers.push_back(obj_RenderManager);
}

void CubicEngine::EngineCore::InitManagers()
{
	for (auto& manager : managers) {
		manager->Init();
	}
}
