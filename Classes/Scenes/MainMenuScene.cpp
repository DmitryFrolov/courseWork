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
	createButtons();
	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}
//====================================Buttons
void MainMenuScene::createButtons()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto middleBtnPos = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2); 
	//set middle (Settings for now) button coordinates at the center of the screenspace

	auto settingsButton = UImanager::createButton("Settings", ccc4(215, 255, 0, 255),
		CC_CALLBACK_1(MainMenuScene::settingsSceneCallback, this), middleBtnPos);
	MenuItems.pushBack(settingsButton);
	Vec2 spaceBetweenButtons = Vec2(0, settingsButton->getContentSize().height * 1.5);

	auto playButton = UImanager::createButton("Play", ccc4(215, 255, 0, 255),
		CC_CALLBACK_1(MainMenuScene::playGameCallback, this), middleBtnPos + spaceBetweenButtons);
	MenuItems.pushBack(playButton);
	
	auto exitButton = UImanager::createButton("Exit", ccc4(215, 255, 0, 255), 
		CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this), middleBtnPos - spaceBetweenButtons);
	MenuItems.pushBack(exitButton);
}

//==============================Background
void MainMenuScene::createBackground()
{
	auto backgroundImage = UImanager::createBackground(MAIN_MENU_BACKROUND_IMAGE, 2);
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
