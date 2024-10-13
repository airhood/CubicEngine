#include "LayerMask.h"

using namespace CubicEngine;

int LayerMask::GetLayerByName(std::string name) {
	return CORE->GET(LayerManager)->GetLayerByName(name);
}

int LayerMask::GetMaskByLayer(int layer) {
	return 1 << layer;
}

int LayerMask::GetMaskByName(std::string name) {
	return 1 << GetLayerByName(name);
}