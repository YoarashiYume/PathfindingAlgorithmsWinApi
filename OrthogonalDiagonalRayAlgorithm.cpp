#include "OrthogonalDiagonalRayAlgorithm.h"

bool OrthogonalDiagonalRayAlgorithm::buildPath(std::vector<Point>&  pointList)
{
	//search for start element
	Point* currentPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	//search for finish element
	this->finishPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	std::pair<Point*, Direction> closestPoint;
	//search for the next point
	while (currentPoint->getType() != Point::Type::FINISH)
	{
		float m_distance = FLT_MAX;
		for (auto& el : currentPoint->getNeighbors())
		{
			if (el.get().getState() == Point::State::VISITED || el.get().getType() == Point::Type::BLOCK)
				continue;
			float newDistance = getDistanceToFinish(el.get());
			if (m_distance > newDistance)
			{
				//finding the smallest distance
				m_distance = newDistance;
				closestPoint = std::make_pair(&el.get(), getPriority(*currentPoint, el.get()));
			}
			else if (m_distance == newDistance && closestPoint.second < getPriority(*currentPoint, el.get()))
			{
				//if the same distance, then the choice of direction priority
				closestPoint = std::make_pair(&el.get(), getPriority(*currentPoint, el.get()));
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
