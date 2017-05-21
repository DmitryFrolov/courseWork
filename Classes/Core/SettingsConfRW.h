#ifndef _SETTINGS_CONFIG_RW
#define _SETTINGS_CONFIG_RW

#include <io.h>
#include <fstream>
#include "config.h"

class SettingsConfRW
{
private:
	static const char* CONFIG_PATH;
public:
	static void createConfig();

	//return 1 if the config exists, otherwise 0
	static bool isConfigExists();

	//return 1 if background music should by played, otherwise 0
	static bool readBGMusicPlaying();

	//arg: 1 if background music should by played, otherwise 0
	static void writeBGMusicPlaying(const bool isPlaying);

	//return value of background music volume in range 0.0 ... 1.0
	static float readBGMusicVolume();

	//arg: background music volume in range 0.0 ... 1.0
	static void writeBGMusicVolume(const float volume);

	//return 1 if AI opponent is enabled, otherwise 0
	static bool readAIEnabled();

	//arg: 1 if AI opponent  should by enabled, otherwise 0
	static void writeAIEnabled(const bool isEnabled);
};

#endif //_SETTINGS_CONFIG_RW