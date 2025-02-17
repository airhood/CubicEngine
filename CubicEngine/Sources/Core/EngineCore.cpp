#include "EngineCore.h"
#include "../Manager/RenderBase.h"
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
	Logger::Init();
	CreateManagers();
	CacheManagers();
	InitManagers();
}

void EngineCore::Start() {
	running = true;
	EngineMain();
}

void EngineCore::Quit() {

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
	const int frame_delay = 1000 / (application->GetFPS());
	while (running && (!glfwWindowShouldClose(window))) {
		Time::updateFrameTime();
		float delta_frame_time = Time::deltaFrameTime();
		FrameTick(delta_frame_time);
		LateTick(delta_frame_time);
		Render();
		Sleep(frame_delay);
	}
}

void EngineCore::Render() {
	for (auto& render_manager : render_managers) {
		render_manager->Render();
	}
}

void EngineCore::CreateManagers() {
	obj_InputManager = new InputManager();
	obj_RenderManager = new RenderManager();
	obj_SceneManager = new SceneManager();
	obj_ComponentInstanceManager = new ComponentInstanceManager();
	obj_LayerManager = new LayerManager();
}

void EngineCore::CacheManagers() {
	managers.push_back(obj_InputManager);
	managers.push_back(obj_RenderManager);
	managers.push_back(obj_SceneManager);
	managers.push_back(obj_ComponentInstanceManager);
	managers.push_back(obj_LayerManager);
	
	render_managers.push_back(obj_RenderManager);
}

void EngineCore::InitManagers() {
	for (auto& manager : managers) {
		manager->Init();
	}
}