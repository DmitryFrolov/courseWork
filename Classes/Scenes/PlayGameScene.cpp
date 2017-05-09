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
	drawBoard();
	drawFigure();
	drawPlayerScoreLabels();

	auto visbleSize = Director::getInstance()->getVisibleSize();
	auto color = new LayerColor();
	colorLayer = color->create(ccc4(0, 0, 0, 0), visbleSize.width, visbleSize.height);
	colorLayer->ignoreAnchorPointForPosition(false);
	colorLayer->setPosition(Vec2(visbleSize.width / 2, visbleSize.height / 2));
	this->addChild(colorLayer);
}

void PlayGameScene::drawBoard() 
{
	chessBoard = new ChessBoard(CELLS_AMOUNT_IN_A_ROW, CELL_MAX_WEIGHT);
	chessBoard->create();
	cells = *chessBoard->getCells();
	LeftUpperBoardPoint = chessBoard->getLeftUpperBoardPoint();
	
	for (auto &row : cells)
		for (auto &cell : row) {
			this->addChild(cell->cellNode, -1);
			this->addChild(cell->scoreLabel, 0, "text_label");
		}
}

void PlayGameScene::drawBackground()
{
	auto backgroundImage = UImanager::createBackground(CHESS_BACKROUND_IMAGE, 2);
	this->addChild(backgroundImage, -2);
}

void PlayGameScene::drawFigure()
{
	playableFigure = new Figure(cells.at(0).at(0)->centerCoordinate);
	this->addChild(playableFigure->getSprite(), 0);
}

void PlayGameScene::drawPlayerScoreLabels()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	player1ScoreLabel = Label::createWithTTF("Player 1 score: " + std::to_string(player1Score),
		"fonts/Enchanted Land cyr-lat.ttf", 70);
	player1ScoreLabel->setAnchorPoint(Vec2(0, 0.5));
	player1ScoreLabel->setPosition(Vec2(origin.x + visibleSize.width / 15,
		origin.y + visibleSize.height * 9 / 10));
	player1ScoreLabel->setTextColor(ccc4(0, 255, 0, 255));
	this->addChild(player1ScoreLabel, 0, "text_label");

	player2ScoreLabel = Label::createWithTTF("Player 2 score: " + std::to_string(player2Score),
		"fonts/Enchanted Land cyr-lat.ttf", 70);
	player2ScoreLabel->setAnchorPoint(Vec2(1, 0.5));
	player2ScoreLabel->setPosition(Vec2(origin.x + visibleSize.width * 14 / 15,
		origin.y + visibleSize.height * 9 / 10));
	player2ScoreLabel->setTextColor(ccc4(0, 255, 0, 255));
	this->addChild(player2ScoreLabel, 0, "text_label");
}

//==================executing when mouse up
void PlayGameScene::onMouseUp(Event *event)
{
	//debug
	if (AI_ONLY) {
		if (playableFigure->horseReleased)
			runMainGameSequence((Sprite*)playableFigure->getSprite());
	}
	else {
		EventMouse* mEvent = (EventMouse*)event;
		Vec2 cursorPosition = Vec2(mEvent->getCursorX(), mEvent->getCursorY());
		Cell* targetCell = cells.at(chessBoard->ConvertVec2toVec2B(cursorPosition).x).at(chessBoard->ConvertVec2toVec2B(cursorPosition).y);
		
		if ((mEvent->getMouseButton() == MOUSE_BUTTON_LEFT) && chessBoard->isPositionBelongsToBoard(cursorPosition)
			&& playableFigure->horseReleased && //targetCell->scoreWeight != 0 &&
			playableFigure->isTargetCoordsValid(chessBoard->ConvertVec2toVec2B(cursorPosition), playableFigure->horseOnBoard))
		{ 
			playableFigure->horseOnBoard = chessBoard->ConvertVec2toVec2B(cursorPosition);
			playableFigure->horseReleased = false;
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
	auto releaseHorse = CallFunc::create([this]() { playableFigure->horseReleased = true; });
	auto upgradeScore = CallFunc::create([this]() {
		auto currentCell = cells.at(playableFigure->horseOnBoard.x).at(playableFigure->horseOnBoard.y);
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
	//if (AI_ENABLED)
	if(SettingsConfRW::readAIEnabled())
		sequence = Sequence::create(acMoveTo, upgradeScore, switchTurn, DelayTime::create(0.5),
			aiTurn, DelayTime::create(ANIMATION_LENGHT), upgradeScore, switchTurn, releaseHorse, nullptr);
	else
		sequence = Sequence::create(acMoveTo, upgradeScore, switchTurn, releaseHorse, nullptr);
	obj->runAction(sequence);
}

void PlayGameScene::runMainGameSequence(Sprite *obj)//overload for ai vs ai debug only
{ 
	auto switchHorse = CallFunc::create([this]() {	playableFigure->horseReleased = !playableFigure->horseReleased; });
	auto upgradeScore = CallFunc::create([this]() {
		auto currnetCell = cells.at(playableFigure->horseOnBoard.x).at(playableFigure->horseOnBoard.y);
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
	int num_of_available = 0, target_cell_id = 0;
	std::vector<Cell> available_cells;
	available_cells.reserve(8);

	for (auto &row : cells)
		for (auto &cell : row)
		{
			if (cell->scoreWeight > 0 && playableFigure->isTargetCoordsValid(cell->coordinatesInTab, playableFigure->horseOnBoard)) {
				available_cells.push_back(*cell);
				num_of_available++;
			}
		}

	if (num_of_available == 0)	//if all available cells == 0 -> game is over
	{
		endGameScene();
		return;
	}

	int loop_worst_delta = CELL_MAX_WEIGHT, turn_worst_delta = -CELL_MAX_WEIGHT;
	for (int iteratorAvailable = 0; iteratorAvailable < num_of_available; ++iteratorAvailable) 
	{
		for (auto &row : cells)															//check enemy available moves
			for (auto &cell : row)
				if (playableFigure->isTargetCoordsValid(cell->coordinatesInTab, available_cells.at(iteratorAvailable).coordinatesInTab)			
					&& cell->coordinatesInTab != playableFigure->horseOnBoard)			//and target position != current figure position
					if (available_cells.at(iteratorAvailable).scoreWeight != 0 && cell->scoreWeight != 0) {	//not plot a route through 0-value cells
						//cells where the opponent's passage is possible
						int current_delta = available_cells.at(iteratorAvailable).scoreWeight - cell->scoreWeight;
						if (current_delta < loop_worst_delta)
							loop_worst_delta = current_delta;
					}
		if (loop_worst_delta > turn_worst_delta) {
			target_cell_id = iteratorAvailable;
			turn_worst_delta = loop_worst_delta;
		}
		loop_worst_delta = CELL_MAX_WEIGHT;
	}
	playableFigure->horseOnBoard = available_cells.at(target_cell_id).coordinatesInTab;
	auto acMoveTo = MoveTo::create(2, available_cells.at(target_cell_id).centerCoordinate);
	playableFigure->getSprite()->runAction(acMoveTo);

	//checking available cells for ser turn 
	num_of_available = 0;
	for (auto &row : cells)
		for (auto &cell : row)
		{
			if (cell->scoreWeight > 0 && playableFigure->isTargetCoordsValid(cell->coordinatesInTab, playableFigure->horseOnBoard)) {
				available_cells.push_back(*cell);
				num_of_available++;
			}
		}

	if (num_of_available == 0) { //if all available cells == 0 -> game is over
		endGameScene();
		return;
	}
}

void PlayGameScene::endGameScene()
{
	auto scene = GameResultScene::createScene(player1Score, player2Score);
	Director::getInstance()->replaceScene(scene);
}

//pause
void PlayGameScene::showDialogPause()
{
	_eventDispatcher->pauseEventListenersForTarget(this, true);

	auto scene = PauseScene::create();
	this->addChild(scene, 1);
	
	colorLayer->setOpacity(140);
}

void PlayGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	EventKeyboard* kbEvent = (EventKeyboard*)event;
	
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		showDialogPause();
		break;
	}
}
