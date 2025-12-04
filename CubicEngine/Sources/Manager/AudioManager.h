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

		FMOD::System* GetFMODSystem();

	private:
		FMOD::System* system = nullptr;

		bool InitFMOD();
		bool RestartFMOD();
		void TryRestartFMOD();

		int numRestartFMOD = 0;
		int maxRestartFMOD = 10;
	};
}