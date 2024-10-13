#pragma once

#include <string>
#include "ManagerBase.h"
#include "../Object/LayerMask.h"

namespace CubicEngine {
	class LayerManager : public ManagerBase {
	public:
		explicit LayerManager() = default;
		~LayerManager();

		void Exterminate() override;

		int GetLayerByName(std::string layer_name);

		// called before starting core)
		void SetLayerName(int layer, std::string name);

	private:
		std::string layer_names[32];
	};
}