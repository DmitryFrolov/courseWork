#ifndef __FIGURE_H__
#define __FIGURE_H__

#include "cocos2d.h"
USING_NS_CC;
class Figure
{ 
private:
	Sprite* figure;
	Vec2 origin;
	Size visibleSize;

public:
	Figure(Vec2 _initialPosition, Vec2 _initOnBoard = Vec2(0, 0));
	~Figure();

	Sprite* getSprite();
	bool targetCoordsIsValid(Vec2 targetCoordinate);
	bool targetCoordsIsValid(Vec2 targetCoordinate, Vec2 figurePositionOnBoard);

	bool horseReleased;
	Vec2 horseOnBoard;
};

#endif // !__FIGURE_H__