#ifndef __FIGURE_H__
#define __FIGURE_H__

#include "cocos2d.h"
USING_NS_CC;
typedef Vec2 Vec2B;

class Figure
{ 
private:
	Sprite* figure;
	Vec2 origin;
	Size visibleSize;
	
	bool figureReleased;
	Vec2 figureOnBoard;
public:
	Figure(Vec2 _initialPosition, float scale, Vec2B _initOnBoard);
	~Figure() { delete figure; }
	Sprite* getSprite();
	bool isTargetCoordsValid(Vec2B targetCoordinate, Vec2B figurePositionOnBoard);
	bool getFigureReleased();
	void setFigureReleased(bool);
	Vec2B getFigureOnBoard();
	void setFigureOnBoard(Vec2B);
};

#endif // !__FIGURE_H__