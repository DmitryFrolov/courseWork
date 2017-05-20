#ifndef _PAUSE_SCREEN_H_
#define _PAUSE_SCREEN_H_
#include "cocos2d.h"
#include "Classes\Core\UImanager.h"
#include "Classes\Scenes\SettingsScene.h"
#include "Classes\Scenes\MainMenuScene.h"
USING_NS_CC;

class PauseScene : public Layer
{
private:
	Layer *blacklightLayer;
public:
	CREATE_FUNC(PauseScene);
	static Scene* createScene();
	virtual bool init();
	void createButtons();
	void createBlacklightLayer();
};

#endif // _PAUSE_SCREEN_H_