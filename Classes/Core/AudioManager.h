#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__
#include <AudioEngine.h>
using namespace cocos2d::experimental;
#define BACKGROUND_SOUND "Sounds/sound.mp3"

class AudioManager
{
private:
	int			background_audioID;
	bool				  _playing;

	AudioManager() 
		: _playing(false)
		, background_audioID(NULL)
	{
	} 

	AudioManager(AudioManager const&) = delete;
	AudioManager& operator= (AudioManager const&) = delete;
public:
	static AudioManager& getInstance();
	void playBackgroundAudio();
	void stopBackgroundAudio();
	void pauseBackgroundAudio();
	void resumeBackgroundAudio();
	void setBackgroundAudioVolume(float value);
	float getBackgroundAudioVolume();
	bool isBackgroundMusicPlaying();
	void endAudio();
};

#endif //__AUDIO_MANAGER_H__
