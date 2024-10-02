#include "EngineCore.h"
#include <Windows.h>

using namespace CubicEngine::Core;

IMPLEMENT_SINGLETON(EngineCore);

EngineCore::EngineCore() {
	application = new Application();
}

EngineCore::~EngineCore() {

}

CubicEngine::Application* EngineCore::GetApplication() {
	return application;
}

void EngineCore::Init() {
	glfwSetWindowUserPointer(window, new PointerHolder());
	CreateManagers();
	CacheManagers();
	InitManagers();
}

void EngineCore::Start() {
	running = true;
	obj_GameInstanceManager->StartInstances();
	EngineMain();
}

void EngineCore::Quit() {

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

void EngineCore::EngineMain() {
	const int delay = 1000 / (application->GetFPS());
	while (running) {
		GameLoop();
		Sleep(delay);
	}
}

void EngineCore::CreateManagers() {
	obj_InputManager = new InputManager();
	obj_RenderManager = new RenderManager();
	obj_SceneManager = new SceneManager();
	obj_GameObjectManager = new GameObjectManager();
	obj_GameInstanceManager = new GameInstanceManager();
}

void EngineCore::CacheManagers() {
	managers.push_back(obj_InputManager);
	managers.push_back(obj_RenderManager);
}

void EngineCore::InitManagers() {
	for (auto& manager : managers) {
		manager->Init();
	}
}