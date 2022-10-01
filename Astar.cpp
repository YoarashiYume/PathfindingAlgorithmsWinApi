#include "Astar.h"
double Astar::hFunction(Point& current, Point& finishCell)
{
	return sqrt(
		pow((current.getLocation().first - finishCell.getLocation().first), 2) 
		+ pow((current.getLocation().second - finishCell.getLocation().second), 2));
}

Point* Astar::minimymF(std::vector<Point*> list)
{
	int minimumIndex = INT_MAX;
	double minF = INT_MAX;
	for (size_t i = 0; i < list.size(); ++i)
		if (list.at(i)->getCostF() < minF && list.at(i)->getType() != Point::Type::BLOCK)
		{
			minF = list.at(i)->getCostF();
			minimumIndex = i;
		}

	return list.at(minimumIndex);
}

bool Astar::buildPath(std::vector<Point>& pointList)
{
	Point* currentPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::START;
		});
	Point* finishPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	std::vector<Point*> openPointList;
	std::vector<Point*> closePointList;
	currentPoint->setCostG(0);
	currentPoint->setCostF(hFunction(*currentPoint, *finishPoint));
	openPointList.push_back(currentPoint);
	while (!openPointList.empty())
	{
		currentPoint = minimymF(openPointList);
		currentPoint->setState(Point::State::VISITED);
		closePointList.push_back(currentPoint);
		if (currentPoint->getLocation() == finishPoint->getLocation())
		{
			for (auto el : closePointList)
				el->setState(Point::State::VISITED);
			return true;
		}
		openPointList.erase(std::find_if(openPointList.begin(), openPointList.end(), [&currentPoint](Point* el) {
			return el->getLocation() == currentPoint->getLocation(); }));
		for (auto& el : currentPoint->getNeighbors())
		{
			int tempCostG = currentPoint->getCostG() + 1;
			if (el.get().getType() == Point::Type::BLOCK)
				continue;
			if (currentPoint->getState() != Point::State::VISITED
				|| (tempCostG < el.get().getCostG() && currentPoint->getState() == Point::State::VISITED))
			{
				el.get().setPrevious(currentPoint);
				el.get().setCostG(tempCostG);
				el.get().setCostF(tempCostG + hFunction(el.get(), *finishPoint));
				if (el.get().getState() == Point::State::VISITED)
					el.get().setState(Point::State::NOT_VISITED);
				openPointList.push_back(&el.get());
			}
		}
	}
		for (auto el : closePointList)
			el->setState(Point::State::VISITED);
	return false;
}
void Astar::findPath(std::vector<Point>& pointList)
{
	Point* currentPoint = &*std::find_if(pointList.begin(), pointList.end(), [](Point& el) {
		return el.getType() == Point::Type::FINISH;
		});
	while (currentPoint->getPrevious())
	{
		currentPoint->setState(Point::State::PATH);
		currentPoint = currentPoint->getPrevious();
	}
}
