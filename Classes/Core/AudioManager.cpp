#include "AudioManager.h"

AudioManager& AudioManager::getInstance()
{
	static AudioManager s;
	return s;
}

void AudioManager::playBackgroundAudio()
{
	if (_playing == true)
		stopBackgroundAudio(); //only one sound thread can be played at the same time
	background_audioID = AudioEngine::play2d(BACKGROUND_SOUND, true, 1.0f);
	_playing = true;
}

void AudioManager::stopBackgroundAudio()
{
	AudioEngine::stop(background_audioID);
	_playing = false;
}

void AudioManager::pauseBackgroundAudio()
{
	AudioEngine::pause(background_audioID);
	_playing = false;
}

void AudioManager::resumeBackgroundAudio() 
{
	AudioEngine::resume(background_audioID);
	_playing = true;
}

void AudioManager::setBackgroundAudioVolume(float value) 
{
	AudioEngine::setVolume(background_audioID, value);
}

float AudioManager::getBackgroundAudioVolume() 
{
	return AudioEngine::getVolume(background_audioID);
}

void AudioManager::endAudio() 
{
	_playing = false;
	AudioEngine::end();
}

bool AudioManager::isBackgroundMusicPlaying() 
{
	return _playing;
}
