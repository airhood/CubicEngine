#include "CubicEngine.h"

using namespace CubicEngine;

int main(void)
{
	CubicApp();
	Application* app = App();
	app->SetTitle("Awesome Game");
	app->SetResolution(1080, 720);
	app->Init();
	app->Start();
}