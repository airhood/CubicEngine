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
	CORE->GET(SceneManager)->StageScene(scene);
	CORE->GET(SceneManager)->OpenScene(0);

	GameObject* game_object = new GameObject();
	game_object->AddComponent<GameManager>();
	scene->AddGameObject(game_object);

	Camera* camera = new Camera();
	CORE->GET(RenderManager)->SetCamera(camera);

	app->Start();
}