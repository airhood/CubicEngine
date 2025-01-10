#include "GameManager.h"
#include "../../Component/Renderer2D.h"

void GameManager::Start() {
	GameObject* gameObject = new GameObject();
	gameObject->SetName("TestGameObject");
	
	Renderer2D* renderer2D = new Renderer2D();
	gameObject->AddComponent(renderer2D);
}