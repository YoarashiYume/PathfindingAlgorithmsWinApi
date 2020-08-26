#include "WaveAlgorithm.h"



bool WaveAlgorithm::buildPath(std::vector<Point>& const pointList)
{
	std::vector<std::reference_wrapper<Point>> currentList;
	auto it = std::find_if(pointList.begin(), pointList.end(), [](Point & el) {
		return el.getType() == Point::Type::START;
		});
	currentList.push_back(std::ref(*it));
	currentList.front().get().setCost(0);
	while (!currentList.empty())
	{
		for (auto& el : currentList.front().get().getNeighbors())
		{
			if (el.get().getCost() == -1 && el.get().getType()!=Point::Type::BLOCK)
				if(isOrtogonal(el.get(),currentList.front().get()))		
				{
					el.get().setCost(currentList.front().get().getCost() + 1);
					currentList.push_back(el);
					if (el.get().getType() == Point::Type::FINISH)
						return true;
				}
		}
		currentList.front().get().setState(Point::State::VISITED);
		currentList.erase(std::remove_if(currentList.begin(), currentList.end(), [](std::reference_wrapper<Point>& el) {
			return el.get().getState() == Point::State::VISITED;
			}), currentList.end());
	}
	return false;
}

void WaveAlgorithm::findPath(std::vector<Point>& const pointList)
{
	Point* currentPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	currentPoint->setState(Point::State::PATH);
	while (currentPoint->getType() != Point::Type::START)
	{
		for (auto& el : currentPoint->getNeighbors())
			if (el.get().getCost() == currentPoint->getCost() - 1)
				{
					currentPoint = &el.get();
					break;
				}
		currentPoint->setState(Point::State::PATH);
	}
}
