#include "TwoBeamAlgorithm.h"

bool TwoBeamAlgorithm::buildPath(std::vector<Point>& pointList)
{
	//search for start element
	Point* startPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	//search for finish element
	Point* finishPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	//calculate alpha and beta
	alpha = startPoint->getLocation().first - finishPoint->getLocation().first >= 0;
	beta = startPoint->getLocation().second - finishPoint->getLocation().second < 0;
	//calculate directions
	std::pair<Direction, Direction> waysForA = std::make_pair(
		alpha ? TwoBeamAlgorithm::Direction::LEFT : TwoBeamAlgorithm::Direction::RIGHT,
		beta ? TwoBeamAlgorithm::Direction::DOWN : TwoBeamAlgorithm::Direction::UP);
	std::pair<Direction, Direction> waysForB = std::make_pair(
		alpha ? TwoBeamAlgorithm::Direction::RIGHT : TwoBeamAlgorithm::Direction::LEFT,
		beta ? TwoBeamAlgorithm::Direction::UP : TwoBeamAlgorithm::Direction::DOWN);
	//build paths
	buildWay(startPoint, waysForA.first, waysForA.second);
	buildWay(startPoint, waysForA.second, waysForA.first);
	buildWay(finishPoint, waysForB.first, waysForB.second);
	buildWay(finishPoint, waysForB.second, waysForB.first);
	return isPath;
}

void TwoBeamAlgorithm::findPath(std::vector<Point>& pointList)
{
	//search for start element
	Point* startPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	//search for finish element
	Point* finishPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	//calculate directions
	std::pair<Direction, Direction> waysForA = std::make_pair(
		alpha ? TwoBeamAlgorithm::Direction::LEFT : TwoBeamAlgorithm::Direction::RIGHT,
		beta ? TwoBeamAlgorithm::Direction::DOWN : TwoBeamAlgorithm::Direction::UP);
	std::pair<Direction, Direction> waysForB = std::make_pair(
		alpha ? TwoBeamAlgorithm::Direction::RIGHT : TwoBeamAlgorithm::Direction::LEFT,
		beta ? TwoBeamAlgorithm::Direction::UP : TwoBeamAlgorithm::Direction::DOWN);
	//find path and build it
	if (isItCorrectDirect(startPoint, waysForA.first, waysForA.second))
		buildPath(startPoint, waysForA.first, waysForA.second);
	if (isItCorrectDirect(startPoint, waysForA.second, waysForA.first))
		buildPath(startPoint, waysForA.second, waysForA.first);
	if (isItCorrectDirect(finishPoint, waysForB.first, waysForB.second))
		buildPath(finishPoint, waysForB.first, waysForB.second);
	if (isItCorrectDirect(finishPoint, waysForB.second, waysForB.first))
		buildPath(finishPoint, waysForB.second, waysForB.first);
}

void TwoBeamAlgorithm::buildWay(Point*const startPoint_,const Direction mainDir_,const Direction subDir_)
{
	//method passes the flight along the given directions, marking the points as part of path
	Point* startPoint = startPoint_;
	Point::Type endType = startPoint->getType() == Point::Type::START ? Point::Type::FINISH : Point::Type::START;
	while (!isPath)
	{
		if (endType == Point::Type::FINISH)
			startPoint->setIsFromA(true);
		else
			startPoint->setIsFromB(true);
		startPoint->setState(Point::State::VISITED);
		if (startPoint->getType() == endType)
		{
			isPath = true;
			return;
		}
		if (endType != Point::Type::START)
		{
			if (startPoint->checkStateBeam().second == true)
			{
				isPath = true;
				return;
			}
		}
		else if (startPoint->checkStateBeam().first == true)
		{
			isPath = true;
			return;
		}
		
		if (!interestedNeighbour(*startPoint, mainDir_))
		{
			if (startPoint->isBorder())
				return;
			if (!interestedNeighbour(*startPoint, subDir_))
				return;
			else
				startPoint = interestedNeighbour(*startPoint, subDir_);
		}
		else
			startPoint = interestedNeighbour(*startPoint, mainDir_);
	}
}

bool TwoBeamAlgorithm::isItCorrectDirect(Point*const startPoint_,const Direction mainDir_,const Direction subDir_)
{
	//checks if there are points on the given path that belong to both paths
	std::pair<bool, bool> res = std::make_pair(true, true);
	Point* cPoint = startPoint_;
	Point::Type endType = cPoint->getType() == Point::Type::START ? Point::Type::FINISH : Point::Type::START;
	while (true)
	{
		if (cPoint->checkStateBeam() == res)
			return true;
		if (!interestedNeighbour(*cPoint, mainDir_))
		{
			if (!interestedNeighbour(*cPoint, subDir_))
				return false;
			else
				cPoint = interestedNeighbour(*cPoint, subDir_);
		}
		else
			cPoint = interestedNeighbour(*cPoint, mainDir_);

		if (endType != Point::Type::START)
		{
			if (cPoint->checkStateBeam().first != true)
				return false;
		}
		else if (cPoint->checkStateBeam().second != true)
			return false;
	}
	return false;
}

void TwoBeamAlgorithm::buildPath(Point*const startPoint_,const Direction mainDir_,const Direction subDir_)
{
	std::pair<bool, bool> res = std::make_pair(true, true);
	Point* cPoint = startPoint_;
	Point::Type endType = cPoint->getType() == Point::Type::START ? Point::Type::FINISH : Point::Type::START;
	while (true)
	{
		cPoint->setState(Point::State::PATH);
		if (cPoint->checkStateBeam() == res)
			return;
		if (!interestedNeighbour(*cPoint, mainDir_))
		{
			if (!interestedNeighbour(*cPoint, subDir_))
				return;
			else
				cPoint = interestedNeighbour(*cPoint, subDir_);
		}
		else
			cPoint = interestedNeighbour(*cPoint, mainDir_);
		
		if (endType != Point::Type::START)
		{
			if (cPoint->checkStateBeam().first != true)
				return;
		}
		else if (cPoint->checkStateBeam().second != true)
			return;
	}
}

Point* TwoBeamAlgorithm::interestedNeighbour(Point& currentPoint_,const Direction dir_)
{
	//finds a neighboring point in a given direction
	int dir = dir_ == TwoBeamAlgorithm::Direction::UP || dir_ == TwoBeamAlgorithm::Direction::RIGHT ? 1 : -1;
	int dY = dir_ == TwoBeamAlgorithm::Direction::RIGHT || dir_ == TwoBeamAlgorithm::Direction::LEFT ? 0 : -dir;
	int dX = dir_ == TwoBeamAlgorithm::Direction::UP || dir_ == TwoBeamAlgorithm::Direction::DOWN ? 0 : dir;
	for (auto& el : currentPoint_.getNeighbors())
		if (el.get().getLocation().first - currentPoint_.getLocation().first == dX
			&& el.get().getLocation().second - currentPoint_.getLocation().second == dY
			&& el.get().getType() != Point::Type::BLOCK
			)
		{
			return &el.get();
		}
	return nullptr;
}
