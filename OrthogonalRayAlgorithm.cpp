#include "OrthogonalRayAlgorithm.h"

float OrthogonalRayAlgorithm::getDistanceToFinish(Point& currentPoint_)
{
	return sqrt(
		pow((finishPoint->getLocation().first - currentPoint_.getLocation().first), 2) +
		pow((finishPoint->getLocation().second - currentPoint_.getLocation().second), 2)
	);
}

OrthogonalRayAlgorithm::Direction OrthogonalRayAlgorithm::getPriority(Point& currentPoint_, Point& newPoint_)
{
	int dX = newPoint_.getLocation().first - currentPoint_.getLocation().first;
	int dY = newPoint_.getLocation().second - currentPoint_.getLocation().second;
	switch (dX)
	{
	case 1:
		switch (dY)
		{
		case 0:
			return Direction::RIGHT;
		case 1:
			return Direction::RIGHT_UP;
		case -1:
			return Direction::RIGHT_DOWN;
		}
	case -1:
		switch (dY)
		{
		case 0:
			return Direction::LEFT;
		case 1:
			return Direction::LEFT_UP;
		case -1:
			return Direction::LEFT_DOWN;
		}
	default:
		switch (dY)
		{
		case 1:
			return Direction::UP;
		case -1:
			return Direction::DOWN;
		}
	}
	return Direction();
}

bool OrthogonalRayAlgorithm::buildPath(std::vector<Point>& const pointList)
{
	Point* currentPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	this->finishPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	std::pair<Point*,Direction> closestPoint;
	while (currentPoint->getType() != Point::Type::FINISH)
	{
		m_distance = FLT_MAX;
		for (auto& el : currentPoint->getNeighbors())
		{
			if (el.get().getState() == Point::State::VISITED || el.get().getType() == Point::Type::BLOCK)
				continue;
			if (isOrtogonal(el.get(), *currentPoint))
			{
				int newDistance = getDistanceToFinish(el.get());
				if (m_distance > newDistance)
				{
					m_distance = newDistance;
					closestPoint = std::make_pair(&el.get(), getPriority(*currentPoint,el.get()));
				}
				else if (m_distance == newDistance && closestPoint.second < getPriority(*currentPoint, el.get()))
				{
					closestPoint = std::make_pair(&el.get(), getPriority(*currentPoint, el.get()));
				}
			}
		}
		currentPoint->setState(Point::State::VISITED);
		if (closestPoint.first == nullptr)
			return false;
		if (currentPoint->getLocation() == closestPoint.first->getLocation())
			return false;
		currentPoint = closestPoint.first;
	}
	return true;
}

void OrthogonalRayAlgorithm::findPath(std::vector<Point>& const pointList)
{
	for (auto& el : pointList)
		if (el.getState() == Point::State::VISITED)
			el.setState(Point::State::PATH);
}
