#include "ChessBoard.h"

ChessBoard::ChessBoard(int _cellsAmount)
{
	cellsAmount = _cellsAmount;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	BoardSideSize = visibleSize.height * 8 / 9;
	LeftUpperBoardPoint = Vec2(origin.x + (visibleSize.width - BoardSideSize) / 2,
		origin.y + BoardSideSize + BoardSideSize / 16);
	cellSideSize = BoardSideSize / cellsAmount;

	cells = std::vector<std::vector<Cell*>>(cellsAmount, std::vector<Cell*>(cellsAmount));
	for (auto &row : cells)
		for (auto &cell : row)
			cell = new Cell();
}

ChessBoard::~ChessBoard()
{
	for (auto &row : cells)
		for (auto &cell : row)
			delete cell;
}

void ChessBoard::create()
{
	Color4F white(1, 1, 1, 1);
	Color4F black(255, 255, 255, 1);
	auto leftUpperCellCenter = Vec2(LeftUpperBoardPoint.x + cellSideSize / 2,
		LeftUpperBoardPoint.y - cellSideSize / 2);

	int rowIdx = 0, columnIdx = 0;
	for (auto &row : cells) {
		for (auto &currentCell : row) {
			currentCell->coordinatesInTab = Vec2(columnIdx, rowIdx);
			currentCell->centerCoordinate = leftUpperCellCenter +
									Vec2(rowIdx * cellSideSize, -columnIdx * cellSideSize);	
			currentCell->scoreWeight = (rowIdx == 0 && columnIdx == 0) ? 0 : getRandomWeight();	//initial figure position cell weight = 0
			auto tmp = currentCell->scoreWeight;
			currentCell->scoreLabel = createScoreLabel(		currentCell->scoreWeight,
															currentCell->centerCoordinate);
			currentCell->color = (rowIdx + columnIdx) % 2 == 0 ? white : black;					//set node color	
			currentCell->cellNode = ChessBoard::createRect(	currentCell->centerCoordinate,
															currentCell->color,																
															BoardSideSize / cellsAmount);
			rowIdx++;
		}
		rowIdx = 0; columnIdx++;
	}
}

Label* ChessBoard::createScoreLabel(int score, Vec2 position) 
{
	Label *label = Label::createWithTTF(std::to_string(score), "fonts/Enchanted Land cyr-lat.ttf", 60);
	label->setPosition(position);
	label->setTextColor(ccc4(0, 255, 0, 255));
	return label;
}

inline int ChessBoard::getRandomWeight() 
{
	return rand() % 99 + 1;
}

DrawNode* ChessBoard::createRect(Vec2 rectCenter, Color4F color, float sideSize)
{
	auto rectNode = DrawNode::create();
	Vec2 rectangle[4];
	rectangle[0] = Vec2(rectCenter.x - sideSize / 2, rectCenter.y - sideSize / 2);
	rectangle[1] = Vec2(rectCenter.x + sideSize / 2, rectCenter.y - sideSize / 2);
	rectangle[2] = Vec2(rectCenter.x + sideSize / 2, rectCenter.y + sideSize / 2);
	rectangle[3] = Vec2(rectCenter.x - sideSize / 2, rectCenter.y + sideSize / 2);

	rectNode->drawPolygon(rectangle, 4, color, 1, color);
	return rectNode;
}

std::vector<std::vector<Cell*>>* ChessBoard::getCells()
{
	return &cells;
}

Vec2 ChessBoard::getLeftUpperBoardPoint()
{
	return LeftUpperBoardPoint;
}

Vec2B ChessBoard::ConvertVec2toVec2B(Vec2 truePosition)
{
	const int targetPosOnBoardX = abs(LeftUpperBoardPoint.y - truePosition.y) /
		(BoardSideSize / cellsAmount);
	const int targetPosOnBoardY = abs(LeftUpperBoardPoint.x - truePosition.x) /
		(BoardSideSize / cellsAmount);

	return Vec2B(targetPosOnBoardX, targetPosOnBoardY);
}

bool ChessBoard::isPositionBelongsToBoard(Vec2 position)
{
	auto BoardSideSize = visibleSize.height * 8 / 9;
	return (position.x >= LeftUpperBoardPoint.x &&
		position.x <= LeftUpperBoardPoint.x + BoardSideSize &&
		position.y  < LeftUpperBoardPoint.y &&
		position.y  > LeftUpperBoardPoint.y - BoardSideSize);
}