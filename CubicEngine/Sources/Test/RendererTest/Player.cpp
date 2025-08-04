#include "Player.h"
#include "../../Util/Input.h"
#include <glm.hpp>

void Player::FrameTick(float elapsedTime) {
	glm::vec2 input = Input::GetWASD();
	RootGameObject()->transform()->position += glm::vec3(input.x, 0.0f, input.y) * moveSpeed;
	//RootGameObject()->transform()->rotation.y += 1;
}