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

void MainMenuScene::createMenuButtons()
{
	std::vector<ButtonData*> *data = new std::vector<ButtonData*>;
	data->reserve(3);
	data->push_back(new ButtonData("Play", [](Ref* sender) {
		auto scene = PlayGameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}));
	data->push_back(new ButtonData("Settings", [](Ref* sender) {
		auto scene = SettingsScene::createScene();
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

void MainMenuScene::createBackground()
{
	auto backgroundImage = UImanager::createBackground(MAIN_MENU_BACKROUND_IMAGE);
	this->addChild(backgroundImage, -1);
}
