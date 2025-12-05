#pragma once

#include "ManagerBase.h"
#include "fmod.hpp"
#include <iostream>
#include <conio.h>

namespace CubicEngine {
	class AudioManager : public ManagerBase {
	public:
		explicit AudioManager() = default;
		~AudioManager();

		void Init() override;

		void Exterminate() override;

		void FrameTick(float elapsedTime) override;


	private:
		FMOD::System* system = nullptr;

		friend class AssetLoader;
		FMOD::System* GetFMODSystem();

		bool InitFMOD();
		bool RestartFMOD();
		void TryRestartFMOD();

		int numRestartFMOD = 0;
		int maxRestartFMOD = 10;
	};
}