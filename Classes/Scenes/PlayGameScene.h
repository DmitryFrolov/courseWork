#ifndef _PLAY_SCENE_H_
#define _PLAY_SCENE_H_
#include "cocos2d.h"
#include "Classes\Scenes\PauseScene.h"
#include "Classes\Scenes\GameResultScene.h"
#include "Core\UImanager.h"
#include "Core\Settings.h"
#include "GameObjects\ChessBoard.h"
#include "GameObjects\Figure.h"
USING_NS_CC;

#define AI_ONLY					false
#define ANIMATION_LENGHT		1
#define CHESS_BACKROUND_IMAGE	"backgrounds/chess-background.jpg"

enum TurnState {_PLAYER_1_TURN_, _PLAYER_2_TURN_};

class PlayGameScene : public Layer
{
private:
	Figure*					playableFigure;
	ChessBoard*					chessBoard;
	std::vector<std::vector<Cell*>>	 cells;
	TurnState				   currentTurn;
	int			player1Score, player2Score;
	Label*				 player1ScoreLabel;
	Label*				 player2ScoreLabel;
public:

	CREATE_FUNC(PlayGameScene);
	virtual bool init();
	static Scene* createScene();
	//============drawers
	void drawGameObjects();
	void drawBoard();
	void drawPauseButton();
	void drawBackground();
	void drawFigure();
	void drawPlayerScoreLabels();

	void onMouseUp(Event *event);
	void runMainGameSequence(Sprite *obj, Vec2 moveto);
	void runMainGameSequence(Sprite *obj); //overload for ai vs ai

	std::vector<Cell> *getAvailableCells();
	//returns coordinates of the center of the nearest cell
	Vec2 getNearestCellCenterCoordinates(Vec2 coordinate);
	void aiPlay();
	void endGameScene();
	//pause
	void showDialogPause(Ref* pSender);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
};
#endif // !_PLAY_SCENE_H_
