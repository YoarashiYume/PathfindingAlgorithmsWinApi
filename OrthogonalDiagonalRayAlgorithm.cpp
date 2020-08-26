#include "OrthogonalDiagonalRayAlgorithm.h"

bool OrthogonalDiagonalRayAlgorithm::buildPath(std::vector<Point>& const pointList)
{
	Point* currentPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	this->finishPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	std::pair<Point*, Direction> closestPoint;
	while (currentPoint->getType() != Point::Type::FINISH)
	{
		m_distance = FLT_MAX;
		for (auto& el : currentPoint->getNeighbors())
		{
			if (el.get().getState() == Point::State::VISITED || el.get().getType() == Point::Type::BLOCK)
				continue;
			int newDistance = getDistanceToFinish(el.get());
			if (m_distance > newDistance)
			{
				m_distance = newDistance;
				closestPoint = std::make_pair(&el.get(), getPriority(*currentPoint, el.get()));
			}
			else if (m_distance == newDistance && closestPoint.second < getPriority(*currentPoint, el.get()))
			{
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
