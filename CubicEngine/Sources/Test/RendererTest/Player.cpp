#include "Player.h"
#include "../../Util/Input.h"
#include <glm.hpp>

void Player::FrameTick(float elapsedTime) {
	Transform* transform = RootGameObject()->transform();

	glm::vec3 forward = transform->Forward();
	glm::vec3 right = transform->Right();

	glm::vec2 wasd_input = Input::GetWASD();
	glm::vec3 moveDir = right * wasd_input.x + forward * wasd_input.y;
	transform->position += moveDir * moveSpeed * elapsedTime * 20.0f;

	glm::vec2 arrows_input = Input::GetArrows();
	transform->rotation += glm::vec3(-arrows_input.y, arrows_input.x, 0.0f);
}