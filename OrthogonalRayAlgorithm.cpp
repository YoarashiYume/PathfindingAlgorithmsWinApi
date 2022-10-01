#include "OrthogonalRayAlgorithm.h"

float OrthogonalRayAlgorithm::getDistanceToFinish(const Point& currentPoint_) const
{
	return sqrtf(
		powf(static_cast<float>(finishPoint->getLocation().first - currentPoint_.getLocation().first), 2) +
		powf(static_cast<float>(finishPoint->getLocation().second - currentPoint_.getLocation().second), 2)
	);
}

OrthogonalRayAlgorithm::Direction OrthogonalRayAlgorithm::getPriority(const Point& currentPoint_,const Point& newPoint_) const
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

bool OrthogonalRayAlgorithm::buildPath(std::vector<Point>&  pointList)
{
	//search for start element
	Point* currentPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	//search for finish element
	this->finishPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	std::pair<Point*,Direction> closestPoint;
	//search for the next point
	while (currentPoint->getType() != Point::Type::FINISH)
	{
		float m_distance = FLT_MAX;
		for (auto& el : currentPoint->getNeighbors())
		{
			if (el.get().getState() == Point::State::VISITED || el.get().getType() == Point::Type::BLOCK)
				continue;
			if (isOrtogonal(el.get(), *currentPoint))//no diagonal neighbors
			{
				float newDistance = getDistanceToFinish(el.get());
				if (m_distance > newDistance)
					//finding the smallest distance
				{
					m_distance = newDistance;
					closestPoint = std::make_pair(&el.get(), getPriority(*currentPoint,el.get()));
				}
				else if (m_distance == newDistance && closestPoint.second < getPriority(*currentPoint, el.get()))
					//if the same distance, then the choice of direction priority
				{
					closestPoint = std::make_pair(&el.get(), getPriority(*currentPoint, el.get()));
				}
			}
		}
		currentPoint->setState(Point::State::VISITED);
		if (closestPoint.first == nullptr)
			return false;
		if (currentPoint->getLocation() == closestPoint.first->getLocation())
			return false;//if there is no change, then there are no path
		currentPoint = closestPoint.first;
	}
	return true;
}

void OrthogonalRayAlgorithm::findPath(std::vector<Point>&  pointList)
{
	for (auto& el : pointList)
		if (el.getState() == Point::State::VISITED)
			el.setState(Point::State::PATH);
}
