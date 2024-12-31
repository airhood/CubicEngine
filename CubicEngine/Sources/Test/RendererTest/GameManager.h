#pragma once

#include "../../CubicEngine.h"
#include "../../Object/GameObject.h"
#include "../../Component/InstanceComponent.h"

using namespace CubicEngine;

class GameManager : public InstanceComponent {
	void Start() override;
};