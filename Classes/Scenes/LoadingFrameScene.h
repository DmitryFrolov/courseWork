#ifndef __LOADING_FRAME_H__
#define __LOADING_FRAME_H__

#include "cocos2d.h"
#include "MainMenuScene.h"
#include "Core/SettingsConfRW.h"
#include "Core/UImanager.h"
#include "Core/AudioManager.h"

#define LOADING_FRAME_BACKROUND_IMAGE "backgrounds/loading-frame-backgound.jpg"

class LoadingFrame : public cocos2d::Layer
{
private:
	ui::LoadingBar* loadingBar;
public:
	//=================SceneCreators
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoadingFrame);
	void LoadingFrame::createInterface();
	//=================applyDefaults
	void applyDefaults();
	void applyBGMPlaying();
	void applyAIOpponentState();

};

#endif //__LOADING_FRAME_H__