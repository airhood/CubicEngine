#include "GameInstance.h"

using namespace CubicEngine;

GameInstance::GameInstance() {
	has_instance = true;
}

GameInstance::~GameInstance() {

}

void GameInstance::Init_() {
	// TODO: get game_objects reference from SceneManager in core
}