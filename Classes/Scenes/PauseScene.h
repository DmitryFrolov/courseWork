#ifndef _PAUSE_SCREEN_H_
#define _PAUSE_SCREEN_H_
#include "cocos2d.h"
#include "Classes\Core\UImanager.h"
#include "Classes\Scenes\SettingsScene.h"
#include "Classes\Scenes\MainMenuScene.h"
USING_NS_CC;

class PauseScene : public Layer
{
public:
	PauseScene(void) {}
	~PauseScene(void) {}

	CREATE_FUNC(PauseScene);
	static Scene* createScene();
	virtual bool init();
	void createButtons();
	void settingsSceneCallback(Ref* pSender);
	void resumeButtonCallback(Ref* pSender);
	void menuButtonCallback(Ref* pSender);
	void exitButtonCallback(Ref* pSender);
};

#endif // _PAUSE_SCREEN_H_