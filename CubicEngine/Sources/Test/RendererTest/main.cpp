#include "../../CubicEngine.h"

using namespace CubicEngine;

#include "GameManager.h"

int main(void)
{
	CubicApp();
	Application* app = App();
	app->SetTitle("Awesome Game");
	app->SetResolution(1920, 1080);
	app->Init();
	app->Start();

	Scene* scene = new Scene();
	scene->SetName("test scene");
	CORE->GET(SceneManager)->StageScene(scene);

	GameManager* game_manager = new GameManager();
}