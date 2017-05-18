#include "Settings.h"

Settings::Settings() 
	: backgroundAudioVolume(0)
	, backgroundAudioEnabled(false)
	, aiOpponentEnabled(false)
	, amountOfCellsInARow(8)
	, cellMaxWeight(323)
{
}

Settings& Settings::getInstance()
{
	static Settings settings;
	return settings;
}

void Settings::setBackgroundAudioVolumeValue(float volume)
{
	backgroundAudioVolume = volume;
}

void Settings::setBackgroundAudioEnabledState(bool isEnabled)
{
	backgroundAudioEnabled = isEnabled;
}

void Settings::setAIOpponentEnabled(bool isEnabled)
{
	aiOpponentEnabled = isEnabled;
}

float Settings::getBackgroundAudioVolume()
{
	return backgroundAudioVolume;
}

bool Settings::getBackgroundAudioEnabled()
{
	return backgroundAudioEnabled;
}

bool Settings::getAIOpponentEnabled()
{
	return aiOpponentEnabled;
}

int	Settings::getAmountOfCellsInARow()
{
	return amountOfCellsInARow;
}

int Settings::getCellMaxWeight()
{
	return cellMaxWeight;
}