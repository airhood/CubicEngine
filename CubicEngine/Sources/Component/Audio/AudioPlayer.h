#pragma once

#include "../Component.h"
#include "../../Object/AudioClip.h"

namespace CubicEngine {
	class AudioPlayer : public Component {
	public:
		void SetAudioSource(AudioClip* audioSource);
		AudioClip* GetAudioSource();

	private:
		AudioClip* audioSource;
	};
}