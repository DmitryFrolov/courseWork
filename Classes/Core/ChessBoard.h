#ifndef _CHESS_BOARD_H_
#define _CHESS_BOARD_H_
#include "cocos2d.h"

USING_NS_CC;

typedef Vec2 Vec2B; //Vec2B - the structure describing coordinates on board

/*
*The structure describing the cell of the ChessBoard
*/
struct Cell 
{
	Vec2B coordinatesInTab;
	Vec2 centerCoordinate;
	DrawNode *cellNode;
	Color4F color;
	Label* scoreLabel;
	int scoreWeight;
};

class ChessBoard
{
private:
	Size							visibleSize;
	Vec2							origin;
	float							cellSideSize;
	Vec2							LeftUpperBoardPoint;
	float							BoardSideSize;
	int								cellsAmount;
	std::vector<std::vector<Cell*>> cells;

	/*
	@returns score Label
	@arg1 score to be written on Label
	@arg2 position of the Label
	*/
	Label* createScoreLabel(int score, Vec2 position);

	/*
	@returns rectangle
	@arg1 center coordinate of the rect
	@arg2 color of the rect
	@arg3 side size of the rect
	*/
	DrawNode* createRect(Vec2 rectCenter, Color4F color, float sideSize);

	/*
	@returns random integer number that ñan be the weight of a cell
	*/
	inline int getRandomWeight();

public:
	/*
	*Calculates main variables, needed to build the chess board, allocates memory for cells
	*/
	ChessBoard(int cellsAmount);

	/*
	*releases the memory, allocated for cells
	*/
	~ChessBoard();
	
	/*
	*initalizes all cells of the board
	*/
	void create();
	
	/*
	@returns double dimensional vector of cells 
	*/
	std::vector<std::vector<Cell*>>* getCells();

	/*
	@returns left upper board point
	*/
	Vec2 getLeftUpperBoardPoint();

	Vec2B ChessBoard::ConvertVec2toVec2B(Vec2 classic);

	/*
	*ñhecks whether the point belongs to the board
	*/
	bool isPositionBelongsToBoard(Vec2 position);
};

#endif _CHESS_BOARD_H_