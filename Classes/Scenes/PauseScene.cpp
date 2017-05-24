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
	data->push_back(new ButtonData("Resume", [this](Ref* sender) {
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
	}));
	data->push_back(new ButtonData("Menu", [](Ref* sender) {
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}));
	data->push_back(new ButtonData("Exit", [](Ref* sender) {
		AudioManager::getInstance().endAudio();
		Director::getInstance()->end();
		exit(0);
	}));
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
