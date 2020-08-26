#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <vector>
#include <algorithm>
#include <math.h>
#include <functional>
#include "Point.h"
class Algorithm
{
public:
	virtual bool buildPath(std::vector<Point>& const pointList) = 0;
	virtual void findPath(std::vector<Point>& const pointList) = 0;
	bool isOrtogonal(Point& first_, Point& second_);
protected:
	Algorithm();
};
#endif // !#define ALGORITHM_H



