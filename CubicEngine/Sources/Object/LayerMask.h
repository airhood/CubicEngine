#pragma once

#include <string>
#include "../Core/EngineCore.h"

namespace CubicEngine {
	class LayerMask {
	public:
		static int GetLayerByName(std::string layer_name);
		static int GetMaskByLayer(int layer);
		static int GetMaskByName(std::string layer_name);
	};
}