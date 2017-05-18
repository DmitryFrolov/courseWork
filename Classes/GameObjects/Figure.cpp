#include "Figure.h"

Figure::Figure(Vec2 _initialPosition, float scale, Vec2B _initOnBoard = Vec2(0,0))
{
	figure = Sprite::create("horse.png");
	figure->setPosition(_initialPosition);
	figure->setScale(scale);					

	figureOnBoard = _initOnBoard;
	figureReleased = true;
}

Sprite* Figure::getSprite()
{
	return figure;
}

bool Figure::isTargetCoordsValid(Vec2B targetCoordinate, Vec2B figurePositionOnBoard)
{
	const int dX = figurePositionOnBoard.x - targetCoordinate.x;
	const int dY = figurePositionOnBoard.y - targetCoordinate.y;
	if (abs(dX) * abs(dY) == 2)
		return true;
	return false;
}

bool Figure::getFigureReleased()
{
	return figureReleased;
}

void Figure::setFigureReleased(bool isReleased) 
{
	figureReleased = isReleased;
}

Vec2B Figure::getFigureOnBoard()
{
	return figureOnBoard;
}

void Figure::setFigureOnBoard(Vec2B posOnBoard)
{
	figureOnBoard = posOnBoard;
}