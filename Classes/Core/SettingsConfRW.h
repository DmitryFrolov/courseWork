#ifndef _SETTINGS_CONFIG_RW
#define _SETTINGS_CONFIG_RW

#include "config.h"
#define CONFIG_PATH "../Resources/config/settings.conf"

static class SettingsConfRW
{
public:

	//return 1 if background music should by played, otherwise 0 
	static bool readBGMusicPlaying();

	//arg: 1 if background music should by played, otherwise 0 
	static void writeBGMusicPlaying(bool isPlaying);

	//return value of background music volume in range 0.0 ... 1.0
	static float readBGMusicVolume();

	/*arg: background music volume in range 0.0 ... 1.0
	*/
	static void writeBGMusicVolume(float volume);
};

#endif //_SETTINGS_CONFIG_RW