#pragma once

#include "Object.h"
#include <fmod.hpp>

namespace CubicEngine {
	class AudioClip : public Object {
	public:
		void* Clone_Obj() const override;

	private:
		friend class AssetLoader;
		friend class AudioPlayer;
		friend class AudioManager;
		FMOD::Sound* sound;
	};
}