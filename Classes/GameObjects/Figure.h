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

public:
	bool horseReleased;
	Vec2 horseOnBoard;

	Figure(Vec2 _initialPosition, Vec2B _initOnBoard = Vec2B(0, 0));
	~Figure();

	Sprite* getSprite();
	bool isTargetCoordsValid(Vec2B targetCoordinate, Vec2B figurePositionOnBoard);
};

#endif // !__FIGURE_H__