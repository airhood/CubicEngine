#include "AudioPlayer.h"

using namespace CubicEngine;

void AudioPlayer::SetAudioSource(AudioClip* audioSource) {
	this->audioSource = audioSource;
}

AudioClip* AudioPlayer::GetAudioSource() {
	return this->audioSource;
}