#include "CubicEngine.h"

using namespace CubicEngine;

int main(void)
{
	CubicApp();
	Application* app = GetApplication();
	app->setTitle("Awesome Game");
	app->setScreenSize(1920, 1080);
	app->Init();
	app->Start();
}