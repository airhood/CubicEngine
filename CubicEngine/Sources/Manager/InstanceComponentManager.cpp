#include "InstanceComponentManager.h"

using namespace CubicEngine;

InstanceComponentManager::~InstanceComponentManager()
{
	Exterminate();
}

void InstanceComponentManager::Init()
{

}

void InstanceComponentManager::PhysicsTick(float elapsedTime)
{
	for (auto& instance_component : instance_components) {
		instance_component->PhysicsTick(elapsedTime);
	}
}

void InstanceComponentManager::FrameTick(float elapsedTime)
{
	for (auto& instance_component : instance_components) {
		instance_component->FrameTick(elapsedTime);
	}
}

void InstanceComponentManager::LateTick(float elapsedTime)
{
	for (auto& instance_component : instance_components) {
		instance_component->LateTick(elapsedTime);
	}
}

void InstanceComponentManager::Exterminate()
{

}

void InstanceComponentManager::AddGameInstance(InstanceComponent* instance_component)
{
	instance_components.push_back(instance_component);
}

void InstanceComponentManager::StartInstances()
{
	for (auto& instance_component : instance_components) {
		instance_component->Start();
	}
}