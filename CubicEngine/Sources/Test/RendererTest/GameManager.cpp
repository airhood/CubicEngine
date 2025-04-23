#include "GameManager.h"
#include "../../Component/Renderer2D.h"

void GameManager::Start() {
	GameObject* gameObject = new GameObject();
	gameObject->SetName("TestGameObject");

	gameObject->AddComponent<Renderer2D>();
}