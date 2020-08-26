#include "TwoBeamAlgorithm.h"

bool TwoBeamAlgorithm::buildPath(std::vector<Point>& const pointList)
{
	Point* startPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	Point* finishPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	alpha = startPoint->getLocation().first - finishPoint->getLocation().first >= 0;
	beta = startPoint->getLocation().second - finishPoint->getLocation().second < 0;
	std::pair<Direction, Direction> waysForA = std::make_pair(
		alpha ? TwoBeamAlgorithm::Direction::LEFT : TwoBeamAlgorithm::Direction::RIGHT,
		beta ? TwoBeamAlgorithm::Direction::DOWN : TwoBeamAlgorithm::Direction::UP);
	std::pair<Direction, Direction> waysForB = std::make_pair(
		alpha ? TwoBeamAlgorithm::Direction::RIGHT : TwoBeamAlgorithm::Direction::LEFT,
		beta ? TwoBeamAlgorithm::Direction::UP : TwoBeamAlgorithm::Direction::DOWN);
	buildWay(startPoint, waysForA.first, waysForA.second);
	buildWay(startPoint, waysForA.second, waysForA.first);
	buildWay(finishPoint, waysForB.first, waysForB.second);
	buildWay(finishPoint, waysForB.second, waysForB.first);
	return isPath;
}

void TwoBeamAlgorithm::findPath(std::vector<Point>& const pointList)
{
	Point* startPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	Point* finishPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	std::pair<Direction, Direction> waysForA = std::make_pair(
		alpha ? TwoBeamAlgorithm::Direction::LEFT : TwoBeamAlgorithm::Direction::RIGHT,
		beta ? TwoBeamAlgorithm::Direction::DOWN : TwoBeamAlgorithm::Direction::UP);
	std::pair<Direction, Direction> waysForB = std::make_pair(
		alpha ? TwoBeamAlgorithm::Direction::RIGHT : TwoBeamAlgorithm::Direction::LEFT,
		beta ? TwoBeamAlgorithm::Direction::UP : TwoBeamAlgorithm::Direction::DOWN);
	if (isItCorrectDirect(startPoint, waysForA.first, waysForA.second))
		buildPath(startPoint, waysForA.first, waysForA.second);
	if (isItCorrectDirect(startPoint, waysForA.second, waysForA.first))
		buildPath(startPoint, waysForA.second, waysForA.first);
	if (isItCorrectDirect(finishPoint, waysForB.first, waysForB.second))
		buildPath(finishPoint, waysForB.first, waysForB.second);
	if (isItCorrectDirect(finishPoint, waysForB.second, waysForB.first))
		buildPath(finishPoint, waysForB.second, waysForB.first);
}

void TwoBeamAlgorithm::buildWay(Point* startPoint_, Direction mainDir_, Direction subDir_)
{
	Point* startPoint = startPoint_;
	std::function<void(bool)> set;
	Point::Type endType = startPoint->getType() == Point::Type::START ? Point::Type::FINISH : Point::Type::START;
	while (!isPath)
	{
		set = std::bind(endType == Point::Type::FINISH ? &Point::setIsFromA : &Point::setIsFromB, startPoint,std::placeholders::_1);
		startPoint->setState(Point::State::VISITED);
		set(true);
		if (startPoint->getType() == endType)
		{
			if (endType != Point::Type::START)
				resultDir.first = static_cast<int> (mainDir_);
			else
				resultDir.second = static_cast<int> (mainDir_);
			isPath = true;
			return;
		}
		if (endType != Point::Type::START)
		{
			if (startPoint->checkStateBeam().second == true)
			{
				resultDir.first = static_cast<int> (mainDir_);
				isPath = true;
				return;
			}
		}
		else if (startPoint->checkStateBeam().first == true)
		{
			resultDir.second = static_cast<int> (mainDir_);
			isPath = true;
			return;
		}
		
		if (!interestedNeighbour(*startPoint, mainDir_, endType))
		{
			if (startPoint->isBorder())
				return;
			if (!interestedNeighbour(*startPoint, subDir_, endType))
				return;
			else
				startPoint = interestedNeighbour(*startPoint, subDir_, endType);
		}
		else
			startPoint = interestedNeighbour(*startPoint, mainDir_, endType);
	}
}

bool TwoBeamAlgorithm::isItCorrectDirect(Point* startPoint_, Direction mainDir_, Direction subDir_)
{
	std::pair<bool, bool> res = std::make_pair(true, true);
	Point* cPoint = startPoint_;
	Point::Type endType = cPoint->getType() == Point::Type::START ? Point::Type::FINISH : Point::Type::START;
	while (true)
	{
		if (cPoint->checkStateBeam() == res)
			return true;
		if (!interestedNeighbour(*cPoint, mainDir_, endType))
		{
			if (!interestedNeighbour(*cPoint, subDir_, endType))
				return false;
			else
				cPoint = interestedNeighbour(*cPoint, subDir_, endType);
		}
		else
			cPoint = interestedNeighbour(*cPoint, mainDir_, endType);


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

void TwoBeamAlgorithm::buildPath(Point* startPoint_, Direction mainDir_, Direction subDir_)
{
	std::pair<bool, bool> res = std::make_pair(true, true);
	Point* cPoint = startPoint_;
	Point::Type endType = cPoint->getType() == Point::Type::START ? Point::Type::FINISH : Point::Type::START;
	while (true)
	{
		cPoint->setState(Point::State::PATH);
		if (cPoint->checkStateBeam() == res)
			return;
		if (!interestedNeighbour(*cPoint, mainDir_, endType))
		{
			if (!interestedNeighbour(*cPoint, subDir_, endType))
				return;
			else
				cPoint = interestedNeighbour(*cPoint, subDir_, endType);
		}
		else
			cPoint = interestedNeighbour(*cPoint, mainDir_, endType);


		if (endType != Point::Type::START)
		{
			if (cPoint->checkStateBeam().first != true)
				return;
		}
		else if (cPoint->checkStateBeam().second != true)
			return;

	}
}

Point* TwoBeamAlgorithm::interestedNeighbour(Point& currentPoint_, Direction dir_, Point::Type endType)
{
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
