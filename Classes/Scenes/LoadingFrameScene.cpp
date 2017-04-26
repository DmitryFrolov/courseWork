#include "Scenes/LoadingFrameScene.h"

Scene* LoadingFrame::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingFrame::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingFrame::init()
{
	if (!Layer::init())
	{
		return false;
	}
	applyDefaults();
	createInterface();
	this->schedule(schedule_selector(LoadingFrame::runMainMenuScene), 0.5f);
	loadingBar->setPercent(100);
	return true;
}

void LoadingFrame::createInterface()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	loadingBar = UImanager::createLoadingBar(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(loadingBar);
	auto backgroundImage = UImanager::createBackground(LOADING_FRAME_BACKROUND_IMAGE, 1.1);
	this->addChild(backgroundImage, -1);
}

void LoadingFrame::runMainMenuScene(float dt)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(MainMenuScene::createScene());
}

//=======================================apply defaults
void LoadingFrame::applyDefaults()
{
	applyBGMPlaying();
}

void LoadingFrame::applyBGMPlaying()
{
	if (SettingsConfRW::readBGMusicPlaying() == 1) //if BGM playing in conf
	{
		AudioManager::getInstance().playBackgroundAudio();  //play BGM
		AudioManager::getInstance().setBackgroundAudioVolume(SettingsConfRW::readBGMusicVolume());  //set volume
	}
}