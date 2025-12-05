#include "AudioClip.h"

using namespace CubicEngine;

void* AudioClip::Clone_Obj() const {
	AudioClip* audioClip = new AudioClip();
	audioClip->sound = this->sound;
	return audioClip;
}