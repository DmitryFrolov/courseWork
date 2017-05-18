#include "MainMenuScene.h"

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init()
{
	if (!Layer::init())
		return false;

	createBackground();
	createMenuButtons();
	return true;
}
//====================================Buttons
void MainMenuScene::createMenuButtons()
{
	std::vector<ButtonData*> *data = new std::vector<ButtonData*>;
	data->reserve(3);
	data->push_back(new ButtonData("Play", CC_CALLBACK_1(MainMenuScene::playGameCallback, this)));
	data->push_back(new ButtonData("Settings", CC_CALLBACK_1(MainMenuScene::settingsSceneCallback, this)));
	data->push_back(new ButtonData("Exit", CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this)));
	auto menu = UImanager::createMenu(data);
	this->addChild(menu, 1);
}

//==============================Background
void MainMenuScene::createBackground()
{
	auto backgroundImage = UImanager::createBackground(MAIN_MENU_BACKROUND_IMAGE);
	this->addChild(backgroundImage, -1);
}

//==================================Functions to CALLBACK

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
	AudioManager::getInstance().endAudio();
	Director::getInstance()->end();
	exit(0);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif   
}

void MainMenuScene::playGameCallback(Ref* pSender)
{
	auto scene = PlayGameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainMenuScene::settingsSceneCallback(Ref* pSender)
{
	auto scene = SettingsScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
