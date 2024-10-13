#include "LayerManager.h"

using namespace CubicEngine;

LayerManager::~LayerManager() {
	Exterminate();
}

void LayerManager::Exterminate() {

}

int LayerManager::GetLayerByName(std::string layer_name) {
	for (int i = 0; i < 32; i++) {
		if (layer_names[i] == layer_name) return i;
	}
	return -1;
}

void LayerManager::SetLayerName(int layer, std::string name) {
	layer_names[layer] = name;
}
