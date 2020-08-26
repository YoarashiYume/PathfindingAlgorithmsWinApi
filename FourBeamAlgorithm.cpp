#include "FourBeamAlgorithm.h"

bool FourBeamAlgorithm::buildPath(std::vector<Point>& const pointList)
{
	Point* startPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	Point* finishPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	for (size_t i = 0; i < 4; ++i)
		buildWay(startPoint, static_cast<Direction> (i), static_cast<Direction> (i));
	for (size_t i = 0; i < 4; ++i)
		buildWay(finishPoint, static_cast<Direction> (i), static_cast<Direction> (i));
	return isPath;
}

void FourBeamAlgorithm::findPath(std::vector<Point>& const pointList)
{
	Point* currPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	Point* crossPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.checkStateBeam() == std::make_pair(true, true);
		});
	crossPoint->setState(Point::State::PATH);
	setPath(currPoint, setDir(crossPoint, currPoint));
	currPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	setPath(currPoint, setDir(crossPoint, currPoint));
}

FourBeamAlgorithm::Direction FourBeamAlgorithm::setDir(Point* from, Point* to)
{
	int dX = from->getLocation().first - to->getLocation().first;
	int dY = from->getLocation().second - to->getLocation().second;
	if (dX > 0)
		return Direction::RIGHT;
	else if (dX < 0)
		return Direction::LEFT;
	else if (dY < 0)
		return Direction::UP;
	else if (dY > 0)
		return Direction::DOWN;
}

void FourBeamAlgorithm::setPath(Point* currPoint, Direction dir)
{
	Point::Type endType = currPoint->getType() == Point::Type::START ? Point::Type::FINISH : Point::Type::START;
	std::pair<bool, bool> res = std::make_pair(true, true);
	while (currPoint->checkStateBeam() != res)
	{
		currPoint->setState(Point::State::PATH);
		currPoint = interestedNeighbour(*currPoint, dir, endType);
	}
}
