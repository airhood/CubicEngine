#include "Player.h"
#include "../../Util/Input.h"
#include <glm.hpp>

void Player::FrameTick(float elapsedTime) {
	Transform* transform = RootGameObject()->transform();

	glm::vec3 forward = transform->Forward();
	glm::vec3 right = transform->Right();

	glm::vec2 wasd_input = Input::GetWASD();
	glm::vec3 moveDir = right * wasd_input.x + forward * wasd_input.y;
	transform->position += moveDir * moveSpeed * elapsedTime;

	float rot_x = 0.0f;
	float rot_y = 0.0f;
	float rot_z = 0.0f;
	
	if (Input::GetKey(KeyCode::Keypad_8)) rot_x -= 1.0f;
	if (Input::GetKey(KeyCode::Keypad_5)) rot_x += 1.0f;

	if (Input::GetKey(KeyCode::Keypad_6)) rot_y += 1.0f;
	if (Input::GetKey(KeyCode::Keypad_4)) rot_y -= 1.0f;
	
	if (Input::GetKey(KeyCode::Keypad_9)) rot_z -= 1.0f;
	if (Input::GetKey(KeyCode::Keypad_7)) rot_z += 1.0f;

	glm::vec2 arrows_input = Input::GetArrows();
	rot_z -= arrows_input.x;

	transform->rotation += glm::vec3(rot_x, rot_y, rot_z);

	if (Input::GetKey(KeyCode::Space) && !(Input::GetKey(KeyCode::LeftShift) || Input::GetKey(KeyCode::RightShift))) {
		transform->position.y += moveSpeed * elapsedTime;
	}
	else if ((Input::GetKey(KeyCode::LeftShift) || Input::GetKey(KeyCode::RightShift)) && !Input::GetKey(KeyCode::Space)) {
		transform->position.y -= moveSpeed * elapsedTime;
	}
}