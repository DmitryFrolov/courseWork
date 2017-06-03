#ifndef __SETTINGS_H__
#define __SETTINGS_H__

/* Singleton class stores data from settings config
** to avoid multiple file read/write requests
*/
class Settings
{
private:
	float	backgroundAudioVolume;
	bool   backgroundAudioEnabled;
	bool		aiOpponentEnabled;
	int		  amountOfCellsInARow;
	int				cellMaxWeight;
	
	Settings();
	~Settings() {}

	Settings(Settings const&) = delete;
	Settings& operator= (Settings const&) = delete;
public:
	static Settings& getInstance();

	void setBackgroundAudioVolumeValue(float);
	void setBackgroundAudioEnabledState(bool);
	void setAIOpponentEnabled(bool);

	float getBackgroundAudioVolume();
	bool getBackgroundAudioEnabled();
	bool getAIOpponentEnabled();
	int	getAmountOfCellsInARow();
	int getCellMaxWeight();
};

#endif // __SETTINGS_H__