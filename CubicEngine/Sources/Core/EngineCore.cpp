#include "EngineCore.h"
#include "../Manager/RenderBase.h"
#include "../Util/Input.h"
#include <Windows.h>
#include <chrono>

using namespace CubicEngine::Core;

IMPLEMENT_SINGLETON(EngineCore);

static const std::string source = "EngineCore.cpp";

EngineCore::EngineCore() {
	Logger::Init();
	application = new Application();
	Logger::Log(LogLevel::DEBUG, "[Core] Application instance generated.", source);
}

EngineCore::~EngineCore() {
	Logger::Log(LogLevel::DEBUG, "[Core] EngineCore instance deleting.", source);
}

CubicEngine::Application* EngineCore::GetApplication() {
	return application;
}

void EngineCore::Init() {
	Logger::Log(LogLevel::DEBUG, "[Core] EngineCore initializing.", source);
	glfwSetWindowUserPointer(window, new PointerHolder());
	if (glfw_PointerHolder() == nullptr) { // validate pointer holder
		try {
			Logger::Log(LogLevel::FATAL, "[Core] set glfw window pointer failed", "EngineCore.cpp");
		}
		catch (...) { }

		Panic();
	}
#ifdef _DEBUG
	Logger::LogConsole(true);
	Logger::Log(LogLevel::DEBUG, "[Logger] LogConsole: true", source);
#else
	Logger::LogConsole(false);
	Logger::Log(LogLevel::DEBUG, "[Logger] LogConsole: false", source);
#endif
	CreateManagers();
	Logger::Log(LogLevel::DEBUG, "[Core] Manager created.", source);
	CacheManagers();
	Logger::Log(LogLevel::DEBUG, "[Core] Manager cached.", source);
	InitManagers();
	Logger::Log(LogLevel::DEBUG, "[Core] Manager initialized.", source);
	InitUtils();
	Logger::Log(LogLevel::DEBUG, "[Core] Utils initialized.", source);
}

void EngineCore::Start() {
	Logger::Log(LogLevel::DEBUG, "[Core] Engine start.", source);
	running = true;
	for (auto& manager : managers) {
		manager->Start();
	}
	Logger::Log(LogLevel::DEBUG, "[Core] Managers started.", source);
	EngineMain();
}

void EngineCore::Quit() {
	Logger::Log(LogLevel::INFO, "[Core] Engine quit.", source);
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
	Logger::Log(LogLevel::DEBUG, "[Core] Engine main loop enter.", source);

	const int frame_delay = 1000 / (application->GetFPS());

	while (running && (!glfwWindowShouldClose(window))) {
		Logger::Log(LogLevel::TRACE, "[Core] Engine main loop.", source);

		auto frame_start = std::chrono::high_resolution_clock::now();

		Time::updateFrameTime();
		float delta_frame_time = Time::deltaFrameTime();
		
		FrameTick(delta_frame_time);
		LateTick(delta_frame_time);
		Render();

		auto frame_end = std::chrono::high_resolution_clock::now();

		int frame_time = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end - frame_start).count();

		if (frame_time < frame_delay) {
			Sleep(frame_delay - frame_time);
		}
	}
}


void EngineCore::Render() {
	Logger::Log(LogLevel::TRACE, "[Core] Render event function call.", source);
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

void EngineCore::InitUtils() {
	CubicEngine::Input::inputManager = obj_InputManager;
}

[[noreturn]] void EngineCore::Panic() {
	std::abort();
}