#pragma once

#include "../../CubicEngine.h"
#include "../../Component/Component.h"

using namespace CubicEngine;

class GameManager : public Component {
public:
	GameManager() = default;

	void Start() override;

	Component* Clone_Comp() override { return nullptr; }
};