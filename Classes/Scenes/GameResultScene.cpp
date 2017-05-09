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
	auto backgroundImage = UImanager::createBackground(RESULT_BACKROUND_IMAGE, 2);
	this->addChild(backgroundImage, -1);
}

void GameResultScene::drawPlayerResultLabels()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto player1Result = Label::createWithTTF("Player 1 score: " + std::to_string(p1Score),
		"fonts/Enchanted Land cyr-lat.ttf", 70);
	player1Result->setAnchorPoint(Vec2(0, 0.5));
	player1Result->setPosition(Vec2(origin.x + visibleSize.width / 15,
		origin.y + visibleSize.height * 9 / 10));
	player1Result->setTextColor(ccc4(0, 255, 0, 255));
	this->addChild(player1Result, 0, "text_label");

	auto player2Result = Label::createWithTTF("Player 2 score: " + std::to_string(p2Score),
		"fonts/Enchanted Land cyr-lat.ttf", 70);
	player2Result->setAnchorPoint(Vec2(1, 0.5));
	player2Result->setPosition(Vec2(origin.x + visibleSize.width * 14 / 15,
		origin.y + visibleSize.height * 9 / 10));
	player2Result->setTextColor(ccc4(0, 255, 0, 255));
	this->addChild(player2Result, 0, "text_label");
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
	auto winnnerLabel = UImanager::createTextLabel(result, "fonts/Enchanted Land cyr-lat.ttf", 70, center);
	winnnerLabel->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(winnnerLabel, 0, "text_label");
}

void GameResultScene::drawMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Vector<MenuItem*> MenuItems;
	auto middleBtnPos = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4);

	auto againButton = UImanager::createButton("Menu", ccc4(215, 255, 0, 255),
		CC_CALLBACK_1(GameResultScene::playGameCallback, this), middleBtnPos);
	MenuItems.pushBack(againButton);
	Vec2 spaceBetweenButtons = Vec2(againButton->getContentSize().width * 1.5, 0);

	auto menuButton = UImanager::createButton("To menu", ccc4(215, 255, 0, 255),
		CC_CALLBACK_1(GameResultScene::menuCallback, this), middleBtnPos - spaceBetweenButtons);
	MenuItems.pushBack(menuButton);

	auto exitButton = UImanager::createButton("Exit", ccc4(215, 255, 0, 255),
		CC_CALLBACK_1(GameResultScene::exitCallback, this), middleBtnPos + spaceBetweenButtons);
	MenuItems.pushBack(exitButton);

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void GameResultScene::playGameCallback(Ref* pSender)
{
	auto scene = PlayGameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameResultScene::menuCallback(Ref* pSender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameResultScene::exitCallback(Ref* pSender)
{
	AudioManager::getInstance().endAudio();
	Director::getInstance()->end();
	exit(0);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif   
}
