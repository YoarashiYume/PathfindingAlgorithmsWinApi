#include "FourBeamAlgorithm.h"

bool FourBeamAlgorithm::buildPath(std::vector<Point>& pointList)
{
	//search for start element
	Point* startPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	//search for finish element
	Point* finishPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	for (size_t i = 0; i < 4; ++i)
		buildWay(startPoint, static_cast<Direction> (i), static_cast<Direction> (i));// No additional direction
	for (size_t i = 0; i < 4; ++i)
		buildWay(finishPoint, static_cast<Direction> (i), static_cast<Direction> (i));// No additional direction
	return isPath;
}

void FourBeamAlgorithm::findPath(std::vector<Point>& pointList)
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

FourBeamAlgorithm::Direction FourBeamAlgorithm::setDir(const Point* const from, const Point* const to)
{
	int dX = from->getLocation().first - to->getLocation().first;
	int dY = from->getLocation().second - to->getLocation().second;
	if (dX > 0)
		return Direction::RIGHT;
	else if (dX < 0)
		return Direction::LEFT;
	else if (dY < 0)
		return Direction::UP;
	else
		return Direction::DOWN;
}

void FourBeamAlgorithm::setPath(Point* currPoint,const Direction dir)
{
	Point::Type endType = currPoint->getType() == Point::Type::START ? Point::Type::FINISH : Point::Type::START;
	std::pair<bool, bool> res = std::make_pair(true, true);
	while (currPoint->checkStateBeam() != res)
	{
		currPoint->setState(Point::State::PATH);
		currPoint = interestedNeighbour(*currPoint, dir);
	}
}
