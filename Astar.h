#ifndef ASTAR_H
#define ASTAR_H_
#include "Algorithm.h"
class Astar : public Algorithm
{
private:
	double hFunction(Point& current, Point& finishCell);
	Point* minimymF(std::vector<Point*> list);
	bool isPathFind{false};
public:
	bool buildPath(std::vector<Point>& pointList) override;
	void findPath(std::vector<Point>& pointList) override;
};

#endif // !ASTAR_H