#include "AudioManager.h"
#include "../Util/Logger.h"
#include <format>
#include <string>

using namespace CubicEngine;

static const std::string source = "AudioManager.cpp";

AudioManager::~AudioManager() {
	Exterminate();
}

void AudioManager::Init() {
	bool result = InitFMOD();
	if (!result) {
		while (numRestartFMOD < maxRestartFMOD) {
			TryRestartFMOD();
		}
	}
}

void AudioManager::Exterminate() {
	if (system != nullptr) {
		system->close();
		system->release();
		system = nullptr;
	}
}

void AudioManager::FrameTick(float elapsedTime) {
	if (system != nullptr) {
		FMOD_RESULT result = system->update();
		if (result != FMOD_OK) {
			Logger::Log(LogLevel::ERROR, "[Audio] FMOD system update failed.", source);
			RestartFMOD();
			return;
		}
	}
	else {
		TryRestartFMOD();
	}
}

FMOD::System* AudioManager::GetFMODSystem() {
	return this->system;
}

bool AudioManager::InitFMOD() {
	FMOD_RESULT result;
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK) {
		Logger::Log(LogLevel::ERROR, "[Audio] FMOD system create failed.", source);
		system = nullptr;
		return false;
	}

	unsigned int version;
	result = system->getVersion(&version);
	if (result != FMOD_OK) {
		Logger::Log(LogLevel::ERROR, "[Audio] FMOD version validation failed.", source);
		system->release();
		system = nullptr;
		return false;
	}
	else {
		Logger::Log(LogLevel::DEBUG, std::format("FMOD version {:08x}", version), source);
	}

	void* extradriverdata(nullptr);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	if (result != FMOD_OK) {
		Logger::Log(LogLevel::ERROR, "[Audio] FMOD system initialize failed.", source);
		system->release();
		system = nullptr;
		return false;
	}

	return true;
}

bool AudioManager::RestartFMOD() {
	if (system != nullptr) {
		system->release();
	}
	return InitFMOD();
}

void AudioManager::TryRestartFMOD() {
	if (numRestartFMOD >= maxRestartFMOD) return;
	numRestartFMOD++;
	bool result = RestartFMOD();
	if (result) {
		numRestartFMOD = 0;
	}
}