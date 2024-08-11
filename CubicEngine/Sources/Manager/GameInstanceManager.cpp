#include "GameInstanceManager.h"

using namespace CubicEngine;

GameInstanceManager::~GameInstanceManager()
{
	Exterminate();
}

void GameInstanceManager::Init()
{

}

void GameInstanceManager::Exterminate()
{

}

void GameInstanceManager::AddGameInstance(GameInstance* instance)
{
	game_instances.push_back(instance);
}

void GameInstanceManager::AddGameInstances(std::vector<GameInstance*> instances) {
	for (auto& instance : instances) {
		AddGameInstance(instance);
	}
}

void GameInstanceManager::StartInstances()
{
	for (auto& instance : game_instances) {
		instance->Start();
	}
}

void GameInstanceManager::PhysicsTickInstances(float elapsedTime)
{
	for (auto& instance : game_instances) {
		instance->PhysicsTick(elapsedTime);
	}
}

void GameInstanceManager::FrameTickInstances(float elapsedTime)
{
	for (auto& instance : game_instances) {
		instance->FrameTick(elapsedTime);
	}
}

void GameInstanceManager::LateTickInstances(float elapsedTime)
{
	for (auto& instance : game_instances) {
		instance->LateTick(elapsedTime);
	}
}
