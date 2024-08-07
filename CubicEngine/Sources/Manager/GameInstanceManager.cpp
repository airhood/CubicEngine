#include "GameInstanceManager.h"

CubicEngine::GameInstanceManager::~GameInstanceManager()
{
	Exterminate();
}

void CubicEngine::GameInstanceManager::Init()
{

}

void CubicEngine::GameInstanceManager::Exterminate()
{

}

void CubicEngine::GameInstanceManager::AddGameInstance(GameInstance* instance)
{
	game_instances.push_back(instance);
}

void CubicEngine::GameInstanceManager::AddGameInstances(std::vector<GameInstance*> instances) {
	for (auto& instance : instances) {
		AddGameInstance(instance);
	}
}

void CubicEngine::GameInstanceManager::StartInstances()
{
	for (auto& instance : game_instances) {
		instance->Start();
	}
}

void CubicEngine::GameInstanceManager::PhysicsTickInstances(float elapsedTime)
{
	for (auto& instance : game_instances) {
		instance->PhysicsTick(elapsedTime);
	}
}

void CubicEngine::GameInstanceManager::FrameTickInstances(float elapsedTime)
{
	for (auto& instance : game_instances) {
		instance->FrameTick(elapsedTime);
	}
}

void CubicEngine::GameInstanceManager::LateTickInstances(float elapsedTime)
{
	for (auto& instance : game_instances) {
		instance->LateTick(elapsedTime);
	}
}
