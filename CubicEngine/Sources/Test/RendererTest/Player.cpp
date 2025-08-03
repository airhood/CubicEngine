#include "Player.h"
#include "../../Util/Input.h"

#include <iostream>

void Player::FrameTick(float elapsedTime) {
	if ((Input::GetKey(KeyCode::W)) && (Input::GetKey(KeyCode::A))) {
		RootGameObject()->transform()->position.z += moveSpeed * div_sqrt2;
		RootGameObject()->transform()->position.x -= moveSpeed * div_sqrt2;
	}
	else if ((Input::GetKey(KeyCode::W)) && (Input::GetKey(KeyCode::S))) {

	}
	else if ((Input::GetKey(KeyCode::W)) && (Input::GetKey(KeyCode::D))) {
		RootGameObject()->transform()->position.z += moveSpeed * div_sqrt2;
		RootGameObject()->transform()->position.x += moveSpeed * div_sqrt2;
	}
	else if ((Input::GetKey(KeyCode::A)) && (Input::GetKey(KeyCode::S))) {
		RootGameObject()->transform()->position.x -= moveSpeed * div_sqrt2;
		RootGameObject()->transform()->position.z -= moveSpeed * div_sqrt2;
	}
	else if ((Input::GetKey(KeyCode::A)) && (Input::GetKey(KeyCode::D))) {

	}
	else if ((Input::GetKey(KeyCode::S)) && (Input::GetKey(KeyCode::D))) {
		RootGameObject()->transform()->position.z -= moveSpeed * div_sqrt2;
		RootGameObject()->transform()->position.x += moveSpeed * div_sqrt2;
	}
	else if (Input::GetKey(KeyCode::W)) {
		RootGameObject()->transform()->position.z += moveSpeed;
	}
	else if (Input::GetKey(KeyCode::A)) {
		RootGameObject()->transform()->position.x -= moveSpeed;
	}
	else if (Input::GetKey(KeyCode::S)) {
		RootGameObject()->transform()->position.z -= moveSpeed;
	}
	else if (Input::GetKey(KeyCode::D)) {
		RootGameObject()->transform()->position.x += moveSpeed;
	}
}