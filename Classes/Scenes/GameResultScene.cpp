#include "GameResultScene.h"

int GameResultScene::p1Score;
int GameResultScene::p2Score;

Scene* GameResultScene::createScene(int _p1Score, int _p2Score)
{
	p1Score = _p1Score, p2Score = _p2Score;
	auto scene = Scene::create();
	auto layer = GameResultScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameResultScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	drawBackground();
	drawPlayerResultLabels();
	drawWinnerLabel();
	drawMenu();
	return true;
}

void GameResultScene::drawBackground()
{
	auto backgroundImage = UImanager::createBackground(RESULT_BACKROUND_IMAGE);
	this->addChild(backgroundImage, -1);
}

void GameResultScene::drawPlayerResultLabels()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto player1Result = Label::createWithTTF("Player 1 score: " + std::to_string(p1Score),
		"fonts/Enchanted Land cyr-lat.ttf", visibleSize.height / 14);
	player1Result->setPosition(Vec2(origin.x + player1Result->getBoundingBox().size.width / 1.3,
										origin.y + visibleSize.height - player1Result->getBoundingBox().size.height));
	player1Result->setTextColor(ccc4(0, 255, 0, 255));

	auto player2Result = Label::createWithTTF("Player 2 score: " + std::to_string(p2Score),
		"fonts/Enchanted Land cyr-lat.ttf", visibleSize.height / 14);
	player2Result->setPosition(Vec2(origin.x + visibleSize.width - player2Result->getBoundingBox().size.width / 1.3,
										origin.y + visibleSize.height - player2Result->getBoundingBox().size.height ));
	player2Result->setTextColor(ccc4(0, 255, 0, 255));
	this->addChild(player1Result, 0);
	this->addChild(player2Result, 0);
}

void GameResultScene::drawWinnerLabel()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	char *result = "";
	if (p1Score > p2Score)
		result = "Player 1 wins!";
	else if (p1Score < p2Score)
		result = "Player 2 wins!";
	else if(p1Score == p2Score)
		result = "Draw. Wow!";

	auto center = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	auto winnnerLabel = UImanager::createTextLabel(result, "fonts/Enchanted Land cyr-lat.ttf", visibleSize.height / 10, center);
	this->addChild(winnnerLabel, 0);
}

void GameResultScene::drawMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto menuCenter = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 6);
	
	std::vector<ButtonData*> *data = new std::vector<ButtonData*>;
	data->reserve(3);
	data->push_back(new ButtonData("Again", [](Ref* sender) {
		auto scene = PlayGameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}));
	data->push_back(new ButtonData("To menu", [](Ref* sender) {
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}));
	data->push_back(new ButtonData("Exit", [](Ref* sender) {
		AudioManager::getInstance().endAudio();
		Director::getInstance()->end();
		exit(0);
	}));
	auto menu = UImanager::createMenu(data, false, menuCenter);
	this->addChild(menu, 1);
}
