#ifndef ASTAR_H
#define ASTAR_H_
#include "Algorithm.h"
class Astar : public Algorithm
{
private:
	double hFunction(Point& current, Point& finishCell);
	Point* minimymF(std::vector<Point*> list);
	bool isPathFind;
public:
	bool buildPath(std::vector<Point>& const pointList) override;
	void findPath(std::vector<Point>& const pointList) override;
};

#endif // !ASTAR_H