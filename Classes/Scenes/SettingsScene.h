#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"
#include "Core/UImanager.h"
#include "Core/SettingsConfRW.h"
#include "Core/Settings.h"

USING_NS_CC;

#define SETTINGS_LABEL_FONT "fonts/Enchanted Land cyr-lat.ttf"
#define SETTINGS_BACKROUND_IMAGE "backgrounds/settings-background.jpg"

class SettingsScene : public cocos2d::Layer
{
private:
	ui::Slider							  *volumeSlider;
	ui::CheckBox							 *bgSoundCB;
	ui::CheckBox						   *aiEnabledCB;
public:
	//=============================SceneCreators
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingsScene);

	//=============================UI Elements	
	void drawUserInterface();
	void drawBackground();
	void drawBGSoundCheckBox();
	void drawAIStateCheckBox();
	void drawMenu();
	void drawMusicVolumeSlider();
	void setDefaultUIState();
	//=============================Callbacks
	void backButtonPressed(Ref* pSender);
	void applyButtonPressed(Ref* pSender);
};

#endif //__SETTINGS_SCENE_H__