#ifndef _PLAY_SCENE_H_
#define _PLAY_SCENE_H_
#include "cocos2d.h"
#include "Core\UImanager.h"
#include "Core\ChessBoard.h"
#include "Core\Figure.h"
USING_NS_CC;

#define AI_ONLY					true
#define CELLS_AMOUNT			8
#define AI_ENABLED				true
#define CELL_MAX_WEIGHT			99
#define CHESS_BACKROUND_IMAGE	"backgrounds/chess-background.jpg"

enum TurnState {_PLAYER_1_TURN_, _PLAYER_2_TURN_};

class PlayGameScene : public Layer
{
private:
	Figure* playableFigure;

	Vec2 origin;
	Size visibleSize;
	ChessBoard* chessBoard;
	std::vector<std::vector<Cell*>> cells;
	Vec2 LeftUpperBoardPoint;
	TurnState currentTurn;
	int player1Score;
	int player2Score;
	Label* player1ScoreLabel;
	Label* player2ScoreLabel;
public:
	CREATE_FUNC(PlayGameScene);
	virtual bool init();
	static Scene* createScene();
	void initAllVariables();
	//============drawers
	void drawGameObjects();
	void drawBoard();
	void drawBackground();
	void drawFigure();
	void drawPlayerScoreLabels();

	void onMouseUp(Event *event);
	void runMainGameSequence(Sprite *obj, Vec2 moveto); //todo: split on create & run sequence
	void runMainGameSequence(Sprite *obj);				//overload for ai vs ai

	//returns coordinates of the center of the nearest cell
	Vec2 getNearestCellCenterCoordinates(Vec2 coordinate);
	void aiPlay();
	void endGameScene();
};
#endif // !_PLAY_SCENE_H_

