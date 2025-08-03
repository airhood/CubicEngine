#pragma once

#include "../../CubicEngine.h"
#include "../../Object/GameObject.h"
#include "../../Component/Component.h"

using namespace CubicEngine;

class Player : public Component {
public:
	Player() = default;

	void FrameTick(float elapsedTime) override;

	Component* Clone_Comp() override { return nullptr; }

private:
	const float moveSpeed = 0.1f;
	const float div_sqrt2 = 0.707106f;
};