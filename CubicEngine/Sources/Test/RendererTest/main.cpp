#include "../../CubicEngine.h"
#include "../../Component/Camera.h"
#include "../../Util/Logger.h"
#include "Player.h"

using namespace CubicEngine;

#include "GameManager.h"

int main(void)
{
	CubicApp();

	//Logger::SetLogLevel(LogLevel::DEBUG);

	Application* app = App();
	app->SetTitle("Awesome Game");
	app->SetResolution(1920, 1080);
	app->SetFPS(120);
	app->Init();

	Scene* scene = new Scene();
	scene->SetName("test scene");
	auto scene_manager = CORE->GET(SceneManager);
	scene_manager->StageScene(scene);
	scene_manager->OpenScene(scene_manager->GetSceneNum("test scene"));

	GameObject* game_object = new GameObject();
	game_object->SetName("GameManager");
	game_object->AddComponent<GameManager>();
	scene->AddGameObject(game_object);

	GameObject* player = new GameObject();
	player->SetName("Player");
	player->transform()->position = glm::vec3(0.0f, 0.0f, -30.0f);
	Camera* camera = new Camera();
	player->AddComponent(camera);
	CORE->GET(RenderManager)->SetCamera(camera);
	player->AddComponent<Player>();
	scene->AddGameObject(player);

	app->Start();
}