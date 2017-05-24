#include "PlayGameScene.h"

Scene* PlayGameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PlayGameScene::create();
	scene->addChild(layer);
	return scene;
}

bool PlayGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	player1Score = 0, player2Score = 0;
	currentTurn = _PLAYER_1_TURN_;

	drawGameObjects();

	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseUp = CC_CALLBACK_1(PlayGameScene::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
	
	auto _kbListener = EventListenerKeyboard::create();
	_kbListener->onKeyReleased = CC_CALLBACK_2(PlayGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_kbListener, this);

	return true;
}

void PlayGameScene::drawGameObjects() 
{
	drawBackground();
	drawPauseButton();
	drawBoard();
	drawFigure();
	drawPlayerScoreLabels();
}

void PlayGameScene::drawBoard() 
{
	chessBoard = new ChessBoard(Settings::getInstance().getAmountOfCellsInARow(), Settings::getInstance().getCellMaxWeight());
	chessBoard->create();
	cells = *chessBoard->getCells();
	
	for (auto &row : cells)
		for (auto &cell : row) {
			this->addChild(cell->cellNode, -1);
			this->addChild(cell->scoreLabel, 0);
		}
}

void PlayGameScene::drawBackground()
{
	auto backgroundImage = UImanager::createBackground(CHESS_BACKROUND_IMAGE);
	this->addChild(backgroundImage, -2);
}

void PlayGameScene::drawFigure()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto cellSideSize = visibleSize.height * 8 / 9 / Settings::getInstance().getAmountOfCellsInARow() * 5 / 6;

	auto scale = Director::getInstance()->getVisibleSize().height / (250 * Settings::getInstance().getAmountOfCellsInARow());
	playableFigure = new Figure(cells.at(0).at(0)->centerCoordinate, 
		scale,
		Vec2(0, 0));
	this->addChild(playableFigure->getSprite(), 0);
}

void PlayGameScene::drawPlayerScoreLabels()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	player1ScoreLabel = Label::createWithTTF("Player 1 score: " + std::to_string(player1Score),
		"fonts/Enchanted Land cyr-lat.ttf", visibleSize.height / 14);
	player1ScoreLabel->setPosition(Vec2(origin.x + player1ScoreLabel->getBoundingBox().size.width / 1.3,
										origin.y + visibleSize.height - player1ScoreLabel->getBoundingBox().size.height ));
	player1ScoreLabel->setTextColor(ccc4(0, 255, 0, 255));

	player2ScoreLabel = Label::createWithTTF("Player 2 score: " + std::to_string(player2Score),
		"fonts/Enchanted Land cyr-lat.ttf", visibleSize.height / 14);
	player2ScoreLabel->setPosition(Vec2(origin.x + visibleSize.width - player2ScoreLabel->getBoundingBox().size.width / 1.3,
										origin.y + visibleSize.height - player2ScoreLabel->getBoundingBox().size.height ));
	player2ScoreLabel->setTextColor(ccc4(0, 255, 0, 255));
	this->addChild(player1ScoreLabel, 0);
	this->addChild(player2ScoreLabel, 0);
}

void PlayGameScene::drawPauseButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create("settings-icon.png", "settings-icon.png", CC_CALLBACK_1(PlayGameScene::showDialogPause, this));
	closeItem->setScale(visibleSize.height / 8000);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getBoundingBox().size.width / 2, 
											    origin.y + closeItem->getBoundingBox().size.height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

//==================executing when mouse up
void PlayGameScene::onMouseUp(Event *event)
{
	//debug
	if (AI_ONLY) {
		if (playableFigure->getFigureReleased())
			runMainGameSequence((Sprite*)playableFigure->getSprite());
	}
	else {
		EventMouse* mEvent = (EventMouse*)event;
		Vec2 cursorPosition = Vec2(mEvent->getCursorX(), mEvent->getCursorY());
		
		if ((mEvent->getMouseButton() == MOUSE_BUTTON_LEFT) && chessBoard->isPositionBelongsToBoard(cursorPosition)
			&& playableFigure->getFigureReleased() && 
			cells.at(chessBoard->ConvertVec2toVec2B(cursorPosition).x).at(chessBoard->ConvertVec2toVec2B(cursorPosition).y)->scoreWeight != 0 &&
			playableFigure->isTargetCoordsValid(chessBoard->ConvertVec2toVec2B(cursorPosition), playableFigure->getFigureOnBoard()))
		{ 
			playableFigure->setFigureOnBoard(chessBoard->ConvertVec2toVec2B(cursorPosition));
			playableFigure->setFigureReleased(false);
			runMainGameSequence(playableFigure->getSprite(), getNearestCellCenterCoordinates(cursorPosition) );
		}
	}
}

Vec2 PlayGameScene::getNearestCellCenterCoordinates(Vec2 coordinate)
{
	auto vec = chessBoard->ConvertVec2toVec2B(coordinate);
	return cells.at(vec.x).at(vec.y)->centerCoordinate;
}

void PlayGameScene::runMainGameSequence(Sprite *obj, Vec2 moveto)
{
	auto acMoveTo = MoveTo::create(ANIMATION_LENGHT, moveto);
	auto releaseHorse = CallFunc::create([this]() { playableFigure->setFigureReleased(true); });
	auto upgradeScore = CallFunc::create([this]() {
		auto currentCell = cells.at(playableFigure->getFigureOnBoard().x).at(playableFigure->getFigureOnBoard().y);
		int scoreToAdd = currentCell->scoreWeight;
		if (scoreToAdd != 0) {
			currentCell->scoreWeight = 0;
			currentCell->scoreLabel->setString("0");
			if (currentTurn == _PLAYER_1_TURN_) {
				player1Score += scoreToAdd;
				player1ScoreLabel->setString("Player 1 score: " + std::to_string(player1Score));
			}
			else { 
				player2Score += scoreToAdd;
				player2ScoreLabel->setString("Player 2 score: " + std::to_string(player2Score));
			}
		}
	});

	auto checkAvailableCellsExist = CallFunc::create([this]() {
		if (getAvailableCells()->empty())	//if all available cells == 0 -> game is over
		{
			endGameScene();
			return;
		}
	});

	auto switchTurn = CallFunc::create([this]() {
		if (currentTurn == _PLAYER_1_TURN_)
			currentTurn = _PLAYER_2_TURN_;
		else
			currentTurn = _PLAYER_1_TURN_;
	});

	auto aiTurn = CallFunc::create([this]() {
		aiPlay();
	});

	Sequence* sequence;
	if(SettingsConfRW::readAIEnabled())
		sequence = Sequence::create(acMoveTo, upgradeScore, checkAvailableCellsExist, switchTurn, DelayTime::create(0.5),
			aiTurn, DelayTime::create(ANIMATION_LENGHT), upgradeScore, checkAvailableCellsExist, switchTurn, releaseHorse, nullptr);
	else
		sequence = Sequence::create(acMoveTo, upgradeScore, checkAvailableCellsExist, switchTurn, releaseHorse, nullptr);
	obj->runAction(sequence);
}

void PlayGameScene::runMainGameSequence(Sprite *obj)//overload for ai vs ai debug only
{ 
	auto switchHorse = CallFunc::create([this]() {	playableFigure->setFigureReleased(!playableFigure->getFigureReleased()); });
	auto upgradeScore = CallFunc::create([this]() {
		auto currnetCell = cells.at(playableFigure->getFigureOnBoard().x).at(playableFigure->getFigureOnBoard().y);
		int scoreToAdd = currnetCell->scoreWeight;
		if (scoreToAdd != 0) {
			currnetCell->scoreWeight = 0;
			currnetCell->scoreLabel->setString("0");
			if (currentTurn == _PLAYER_1_TURN_) {
				player1Score += scoreToAdd;
				player1ScoreLabel->setString("Player 1 score: " + std::to_string(player1Score));
			} else { 
				player2Score += scoreToAdd;
				player2ScoreLabel->setString("Player 2 score: " + std::to_string(player2Score));
			}
		}
	});

	auto switchTurn = CallFunc::create([this]() {
		if (currentTurn == _PLAYER_1_TURN_)
			currentTurn = _PLAYER_2_TURN_;
		else
			currentTurn = _PLAYER_1_TURN_;
	});

	auto aiTurn = CallFunc::create([this]() {
		aiPlay();
	});
	Sequence* sequence = Sequence::create(switchHorse, aiTurn, DelayTime::create(ANIMATION_LENGHT), upgradeScore, switchTurn, switchHorse, nullptr);
	obj->runAction(sequence);
}

void PlayGameScene::aiPlay()
{
	auto available_cells = getAvailableCells();
	int loop_worst_delta = Settings::getInstance().getCellMaxWeight(), 
		turn_worst_delta = -Settings::getInstance().getCellMaxWeight(), 
		target_cell_id = 0;
	for (size_t iteratorAvailable = 0; iteratorAvailable < available_cells->size(); ++iteratorAvailable)
	{
		for (auto &row : cells)															//check enemy available moves
			for (auto &cell : row)
				if (playableFigure->isTargetCoordsValid(cell->coordinatesInTab, available_cells->at(iteratorAvailable).coordinatesInTab)			
					&& cell->coordinatesInTab != playableFigure->getFigureOnBoard())			//and target position != current figure position
					if (available_cells->at(iteratorAvailable).scoreWeight != 0 && cell->scoreWeight != 0) {	//not plot a route through 0-value cells
						//cells where the opponent's passage is possible
						int current_delta = available_cells->at(iteratorAvailable).scoreWeight - cell->scoreWeight;
						if (current_delta < loop_worst_delta)
							loop_worst_delta = current_delta;
					}
		if (loop_worst_delta > turn_worst_delta) {
			target_cell_id = iteratorAvailable;
			turn_worst_delta = loop_worst_delta;
		}
		loop_worst_delta = Settings::getInstance().getCellMaxWeight();
	}
	playableFigure->setFigureOnBoard(available_cells->at(target_cell_id).coordinatesInTab);
	auto acMoveTo = MoveTo::create(ANIMATION_LENGHT, available_cells->at(target_cell_id).centerCoordinate);
	playableFigure->getSprite()->runAction(acMoveTo);
}

std::vector<Cell> *PlayGameScene::getAvailableCells()
{
	std::vector<Cell> *available_cells = new std::vector<Cell>();
	available_cells->reserve(8);  //8 - maximum available for turn cell in case of knight figure

	for (auto &row : cells)
		for (auto &cell : row)
		{
			if (cell->scoreWeight > 0 && playableFigure->isTargetCoordsValid(cell->coordinatesInTab, playableFigure->getFigureOnBoard())) {
				available_cells->push_back(*cell);
			}
		}
	return available_cells;
}

void PlayGameScene::endGameScene()
{
	auto scene = GameResultScene::createScene(player1Score, player2Score);
	Director::getInstance()->replaceScene(scene);
}

void PlayGameScene::showDialogPause(Ref* pSender)
{
	_eventDispatcher->pauseEventListenersForTarget(this, true);
	Vector<Node*> childs = this->getChildren();
	for( auto child : childs)
	{
		CCSprite *sprite = (CCSprite *)child;
		child->pauseSchedulerAndActions();
	} //pause all scene childs

	auto scene = PauseScene::create();
	this->addChild(scene, 1);
}

void PlayGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	EventKeyboard* kbEvent = (EventKeyboard*)event;
	
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		showDialogPause(this);
		break;
	}
}
