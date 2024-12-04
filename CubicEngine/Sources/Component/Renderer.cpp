#include "Renderer.h"

using namespace CubicEngine;

void Renderer::SetRenderOrder(int value) {
	renderOrder = value;
}

int Renderer::GetRenderOrder() const {
	return renderOrder;
}