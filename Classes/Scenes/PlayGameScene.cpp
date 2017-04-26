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

	initAllVariables();
	drawGameObjects();
	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseUp = CC_CALLBACK_1(PlayGameScene::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
	return true;
}

void PlayGameScene::initAllVariables() 
{
	srand(time(NULL));
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	player1Score = 0;
	player2Score = 0;
	currentTurn = _PLAYER_1_TURN_;
}

void PlayGameScene::drawGameObjects() 
{
	drawBackground();
	drawBoard();
	drawFigure();
	drawPlayerScoreLabels();
}

void PlayGameScene::drawBoard() 
{
	chessBoardObj = new ChessBoard(CELLS_AMOUNT);
	chessBoardObj->create();
	cells = *chessBoardObj->getCells();
	LeftUpperBoardPoint = chessBoardObj->getLeftUpperBoardPoint();
	
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
	this->addChild(playableFigure->getSprite(), 1);
}

void PlayGameScene::drawPlayerScoreLabels()
{
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
		if ((mEvent->getMouseButton() == MOUSE_BUTTON_LEFT) && isPositionBelongsToBoard(Vec2(mEvent->getCursorX(), mEvent->getCursorY()))
			&& playableFigure->horseReleased && playableFigure->targetCoordsIsValid(
				chessBoardObj->ConvertVec2toVec2B(Vec2(mEvent->getCursorX(), mEvent->getCursorY())), playableFigure->horseOnBoard))
		{ 
			playableFigure->horseOnBoard = chessBoardObj->ConvertVec2toVec2B(Vec2(mEvent->getCursorX(), mEvent->getCursorY()));
			playableFigure->horseReleased = false;
			runMainGameSequence(playableFigure->getSprite(), getNearestCellCenterCoordinates(Vec2(mEvent->getCursorX(), mEvent->getCursorY())) );
		}
	}
}

Vec2 PlayGameScene::getNearestCellCenterCoordinates(Vec2 coordinate)
{
	auto vec = chessBoardObj->ConvertVec2toVec2B(coordinate);
	return cells.at(vec.x).at(vec.y)->centerCoordinate;
}


void PlayGameScene::runMainGameSequence(Sprite *obj, Vec2 moveto)
{
	auto acMoveTo = MoveTo::create(2, moveto);
	auto releaseHorse = CallFunc::create([this]() { playableFigure->horseReleased = true; });
	auto upgradeScore = CallFunc::create([this]() {
		int scoreToAdd = cells.at(playableFigure->horseOnBoard.x).at(playableFigure->horseOnBoard.y)->scoreWeight;
		if (scoreToAdd != 0) {
			cells.at(playableFigure->horseOnBoard.x).at(playableFigure->horseOnBoard.y)->scoreWeight = 0;
			cells.at(playableFigure->horseOnBoard.x).at(playableFigure->horseOnBoard.y)->scoreLabel->setString("0");
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
	if (AI)
		sequence = Sequence::create(acMoveTo, upgradeScore, switchTurn, DelayTime::create(0.5),
			aiTurn, DelayTime::create(2), upgradeScore, switchTurn, releaseHorse, nullptr);
	else
		sequence = Sequence::create(acMoveTo, upgradeScore, switchTurn, releaseHorse, nullptr);
	obj->runAction(sequence);
}

void PlayGameScene::runMainGameSequence(Sprite *obj)//overload for ai vs ai debug only
{ 
	auto switchHorse = CallFunc::create([this]() {	playableFigure->horseReleased = !playableFigure->horseReleased; });
	auto upgradeScore = CallFunc::create([this]() {
		int scoreToAdd = cells.at(playableFigure->horseOnBoard.x).at(playableFigure->horseOnBoard.y)->scoreWeight;
		if (scoreToAdd != 0) {
			cells.at(playableFigure->horseOnBoard.x).at(playableFigure->horseOnBoard.y)->scoreWeight = 0;
			cells.at(playableFigure->horseOnBoard.x).at(playableFigure->horseOnBoard.y)->scoreLabel->setString("0");
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
	Sequence* sequence = Sequence::create(switchHorse, aiTurn, DelayTime::create(2), upgradeScore, switchTurn, switchHorse, nullptr);
	obj->runAction(sequence);
}

void PlayGameScene::aiPlay()
{
	playableFigure->horseReleased = false;
	int num_of_available = 0, target_cell_id = 0;
	std::vector<Cell> available_cells;
	available_cells.reserve(8);	

	for (auto &row : cells)
		for (auto &cell : row)
		{
			if (cell->scoreWeight > 0 && playableFigure->targetCoordsIsValid(cell->coordinatesInTab, playableFigure->horseOnBoard)) {
				available_cells.push_back(*cell);
				num_of_available++;
			}
		}

	if (num_of_available == 0) //if all available turns == 0 -> game is over
		endGameScene();

	int numOfNonZeroCellWeightFinded = 0;
	{ 
		int best_delta = -1000, current_delta, loop_worst_delta;
		for (int ita = 0; ita < num_of_available; ++ita) {
			loop_worst_delta = 1000;
			for (auto &row : cells)
				for (auto &cell : row)
				{
					if (playableFigure->targetCoordsIsValid(cell->coordinatesInTab, available_cells.at(ita).coordinatesInTab) && cell->coordinatesInTab != playableFigure->horseOnBoard)
						if (available_cells.at(ita).scoreWeight != 0 && cell->scoreWeight != 0) {
							numOfNonZeroCellWeightFinded++;
							current_delta = available_cells.at(ita).scoreWeight - cell->scoreWeight;
							if (current_delta < loop_worst_delta)
								loop_worst_delta = current_delta;
						}
					if (loop_worst_delta > best_delta) {
						target_cell_id = ita;
						best_delta = loop_worst_delta;
					}
				}
		}

		playableFigure->horseOnBoard = available_cells.at(target_cell_id).coordinatesInTab;
		auto acMoveTo = MoveTo::create(2, available_cells.at(target_cell_id).centerCoordinate);
		playableFigure->getSprite()->runAction(acMoveTo);

		//todo: add checking for available cells 4 user turn
	}
}

void PlayGameScene::endGameScene()
{
	exit(0);
}