#include "../../CubicEngine.h"
#include "../../Component/Camera.h"
#include "../../Util/Logger.h"

using namespace CubicEngine;

#include "GameManager.h"

int main(void)
{
	CubicApp();

	Logger::SetLogLevel(LogLevel::DEBUG);

	Application* app = App();
	app->SetTitle("Awesome Game");
	app->SetResolution(1920, 1080);
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

	GameObject* cam_game_object = new GameObject();
	cam_game_object->SetName("Camera");
	cam_game_object->transform()->position = glm::vec3(0.0f, 0.0f, -30.0f);
	cam_game_object->transform()->rotation.y = 15.0f;
	Camera* camera = new Camera();
	cam_game_object->AddComponent(camera);
	CORE->GET(RenderManager)->SetCamera(camera);

	app->Start();
}