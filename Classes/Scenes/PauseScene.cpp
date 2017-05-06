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
	/*auto _kbListener = EventListenerKeyboard::create();
	_kbListener->onKeyReleased */
	createButtons();
	
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

	auto exitButton = UImanager::createButton("Exit", ccc4(215, 255, 0, 255),
		CC_CALLBACK_1(PauseScene::exitButtonCallback, this), middleBtnPos - spaceBetweenButtons);

	auto menu = Menu::create(settingsButton, resumeButton, exitButton, NULL);
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
	_eventDispatcher->resumeEventListenersForTarget(this->getParent(), true);
	this->getParent()->removeChild(this);
}

void PauseScene::exitButtonCallback(Ref* pSender)
{
	exit(0);
}