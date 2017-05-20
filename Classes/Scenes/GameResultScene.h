#ifndef _GAME_RESULT_SCENE_H_
#define _GAME_RESULT_SCENE_H_
#include "cocos2d.h"
#include "Classes\Core\UImanager.h"
#include "Classes\Scenes\PlayGameScene.h"
#include "Classes\Scenes\MainMenuScene.h"
USING_NS_CC;

#define RESULT_BACKROUND_IMAGE "backgrounds/background2.png"

class GameResultScene : public Layer
{
private:
	static int p1Score, p2Score;
public:
	GameResultScene(void) {}
	~GameResultScene(void) {}

	CREATE_FUNC(GameResultScene);
	static Scene* createScene(int p1Score, int p2Score);
	virtual bool init();

	void drawBackground();
	void drawPlayerResultLabels();
	void drawWinnerLabel();
	void drawMenu();
};

#endif //_GAME_RESULT_SCENE_H_
