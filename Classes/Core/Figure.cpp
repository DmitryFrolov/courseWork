#include "Figure.h"

Figure::Figure(Vec2 _initialPosition, Vec2 _initOnBoard)
{
	figure = Sprite::create("horse.png");
	figure->setPosition(_initialPosition);
	figure->setScale(0.5);					//	CELLS_AMOUNT/16

	horseOnBoard = _initOnBoard;
	horseReleased = true;
}


Figure::~Figure()
{
}

Sprite* Figure::getSprite()
{
	return figure;
}


//принимает координаты центра и координаты на доске
bool Figure::targetCoordsIsValid(Vec2 targetCoordinate, Vec2 figurePositionOnBoard)
{
	const int dX = figurePositionOnBoard.x - targetCoordinate.x;
	const int dY = figurePositionOnBoard.y - targetCoordinate.y;
	if (abs(dX) * abs(dY) == 2)
		return true;
	return false;
}

