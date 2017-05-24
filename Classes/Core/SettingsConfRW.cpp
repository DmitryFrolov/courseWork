#include "SettingsConfRW.h"
const char* SettingsConfRW::CONFIG_PATH = "config/settings.conf";

void SettingsConfRW::createConfig() 
{
	std::ofstream ofs(CONFIG_PATH);
	ofs.close();
}

bool SettingsConfRW::isConfigExists() 
{
	if ((_access(CONFIG_PATH, 06)) != -1) {
		return true;
	}
	return false;
}

bool SettingsConfRW::readBGMusicPlaying()
{
	if (isConfigExists()) {
		std::string temp = dConf::getValueByKey(CONFIG_PATH, "is_background_music_playing");
		return dConf::stringToBool(temp);
	}
	return false;
}

float SettingsConfRW::readBGMusicVolume()
{
	if (isConfigExists()) {
		std::string temp = dConf::getValueByKey(CONFIG_PATH, "background_music_volume");
		return atof(temp.c_str());
	}
	return 1.0;
}

bool SettingsConfRW::readAIEnabled()
{
	if (isConfigExists()) {
		std::string temp = dConf::getValueByKey(CONFIG_PATH, "is_ai_opponent_enabled");
		return dConf::stringToBool(temp);
	}
	return false;
}

void SettingsConfRW::writeBGMusicPlaying(bool isPlaying)
{
	if (isConfigExists()) {
		std::string temp = dConf::boolToString(isPlaying);
		dConf::setValueByKey(CONFIG_PATH, "is_background_music_playing", temp);
	}
}

void SettingsConfRW::writeBGMusicVolume(float volume)
{
	if (isConfigExists()) {
		dConf::setValueByKey(CONFIG_PATH, "background_music_volume", std::to_string(volume));
	}
}

void SettingsConfRW::writeAIEnabled(bool isEnabled)
{
	if (isConfigExists) {
		std::string temp = dConf::boolToString(isEnabled);
		dConf::setValueByKey(CONFIG_PATH, "is_ai_opponent_enabled", temp);
	}
}