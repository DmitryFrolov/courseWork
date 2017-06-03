#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "Core\UImanager.h"
#include "Core\AudioManager.h"
#include "SettingsScene.h"
#include "PlayGameScene.h"

USING_NS_CC;
#define MAIN_MENU_BACKROUND_IMAGE "backgrounds/background2.png"

class MainMenuScene : public cocos2d::Layer
{
private:
	void createMenuButtons();
	void createBackground();
public:
	//=================MainMenuSceneCreators
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainMenuScene);
};

#endif //!__MAIN_MENU_SCENE_H__
