#include "PauseScene.h"

Scene* PauseScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PauseScene::create();
	scene->addChild(layer);
	return scene;
}

bool PauseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	createButtons();

	return true;
}

void PauseScene::createButtons()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto middleBtnPos = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	
	auto settingsButton = UImanager::createButton("Settings", ccc4(215, 255, 0, 255),
		CC_CALLBACK_1(PauseScene::settingsSceneCallback, this), middleBtnPos);

	Vec2 spaceBetweenButtons = Vec2(0, settingsButton->getContentSize().height * 1.5);

	auto resumeButton = UImanager::createButton("Resume", ccc4(215, 255, 0, 255),
		CC_CALLBACK_1(PauseScene::resumeButtonCallback, this), middleBtnPos + spaceBetweenButtons);

	auto menuButton = UImanager::createButton("Menu", ccc4(215, 255, 0, 255),
		CC_CALLBACK_1(PauseScene::menuButtonCallback, this), middleBtnPos - spaceBetweenButtons);

	auto exitButton = UImanager::createButton("Exit", ccc4(215, 255, 0, 255),
		CC_CALLBACK_1(PauseScene::exitButtonCallback, this), middleBtnPos - 2 * spaceBetweenButtons);

	auto menu = Menu::create(settingsButton, resumeButton, menuButton, exitButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void PauseScene::settingsSceneCallback(Ref* pSender)
{
	auto scene = SettingsScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void PauseScene::resumeButtonCallback(Ref* pSender)
{
	auto parent = this->getParent();
	((PlayGameScene*)parent)->colorLayer->setOpacity(0);
	
	_eventDispatcher->resumeEventListenersForTarget(parent, true);
	parent->removeChild(this);
}

void PauseScene::menuButtonCallback(Ref* pSender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void PauseScene::exitButtonCallback(Ref* pSender)
{
	exit(0);
}
