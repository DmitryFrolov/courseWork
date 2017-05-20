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
	createInterface();
	loadingBar->setPercent(50);
	applyDefaults();
	this->schedule([&](float dt) {
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	}, 1.f, 0, 0.f, "LFshedule");
	loadingBar->setPercent(100);
	return true;
}

void LoadingFrame::createInterface()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	loadingBar = UImanager::createLoadingBar(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	loadingBar->setScale(Director::getInstance()->getWinSize().height / 600);
	this->addChild(loadingBar);
	auto backgroundImage = UImanager::createBackground(LOADING_FRAME_BACKROUND_IMAGE);
	this->addChild(backgroundImage, -1);
}

//=======================================apply defaults
void LoadingFrame::applyDefaults()
{
	applyBGMPlaying();
	applyAIOpponentState();
}

void LoadingFrame::applyBGMPlaying()
{
	if (SettingsConfRW::readBGMusicPlaying() == 1) //if BGM playing in conf
	{
		float volume = SettingsConfRW::readBGMusicVolume();
		AudioManager::getInstance().playBackgroundAudio();  //play BGM
		AudioManager::getInstance().setBackgroundAudioVolume(volume); 
		
		Settings::getInstance().setBackgroundAudioEnabledState(true); //writeToSingleton
		Settings::getInstance().setBackgroundAudioVolumeValue(volume);
	}
}

void LoadingFrame::applyAIOpponentState()
{
	Settings::getInstance().setAIOpponentEnabled(SettingsConfRW::readAIEnabled());
}