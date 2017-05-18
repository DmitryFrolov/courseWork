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
	createBlacklightLayer();
	
	return true;
}

void PauseScene::createButtons()
{
	std::vector<ButtonData*> *data = new std::vector<ButtonData*>;
	data->reserve(4);
	data->push_back(new ButtonData("Resume", CC_CALLBACK_1(PauseScene::resumeButtonCallback, this)));
	data->push_back(new ButtonData("Menu", CC_CALLBACK_1(PauseScene::menuButtonCallback, this)));
	data->push_back(new ButtonData("Settings", CC_CALLBACK_1(PauseScene::settingsSceneCallback, this)));
	data->push_back(new ButtonData("Exit", CC_CALLBACK_1(PauseScene::exitButtonCallback, this)));
	auto menu = UImanager::createMenu(data);
	this->addChild(menu, 1);
}

void PauseScene::createBlacklightLayer()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto color = new LayerColor();
	blacklightLayer = color->create(ccc4(0, 0, 0, 0), winSize.width, winSize.height);
	blacklightLayer->ignoreAnchorPointForPosition(false);
	blacklightLayer->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	blacklightLayer->setOpacity(140);
	this->addChild(blacklightLayer, -1);
}

void PauseScene::settingsSceneCallback(Ref* pSender)
{
	auto scene = SettingsScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void PauseScene::resumeButtonCallback(Ref* pSender)
{
	auto parent = this->getParent();
	blacklightLayer->setOpacity(0);
	_eventDispatcher->resumeEventListenersForTarget(parent, true);
	
	Vector<Node*> childs = parent->getChildren();
	for (auto child : childs)
	{
		CCSprite *sprite = (CCSprite *)child;
		child->resumeSchedulerAndActions();
	}
	parent->removeChild(this);
}

void PauseScene::menuButtonCallback(Ref* pSender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void PauseScene::exitButtonCallback(Ref* pSender)
{
	AudioManager::getInstance().endAudio();
	Director::getInstance()->end();
	exit(0);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif  
}
