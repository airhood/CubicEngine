#include "CubicEngine.h"

using namespace CubicEngine;

int main(void)
{
	CubicApp();
	
	Application* app = CUBIC_ENGINE->GetApplication();
	app->setTitle("���� �̸�");
	app->Initialize();
}