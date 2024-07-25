#include "CubicEngine.h"

using namespace CubicEngine;

int main(void)
{
	CubicApp();
	
	Application* app = CUBIC_ENGINE->GetApplication();
	app->setTitle("게임 이름");
	app->Initialize();
}