#ifndef ASTAR_H
#define ASTAR_H_
#include "Algorithm.h"
/**
\brief Realization of the A* algorithm
*/
class Astar final : public Algorithm
{
private:
	/**
	\brief method for estimating the distance from the current to the end point
	\param current current point
	\param finishCell end point
	\return distance
	*/
	double hFunction(const Point& current,const Point& finishCell) const;
	/**
	\brief method for finding a point with estimated distance to end point
	\param list
	\return point with minimum Point::constF
	*/
	Point* minimymF(std::vector<Point*>& list) const;
	bool isPathFind{false}; ///< is the path found flag
public:
	/**
	\brief path building method
	\param pointList point list
	\return true if it was possible to build a path, otherwise false
	*/
	virtual bool buildPath(std::vector<Point>& pointList) override;
	/**
	\brief path finding method
	\param pointList point list
	*/
	virtual void findPath(std::vector<Point>& pointList) override;
};

#endif // !ASTAR_H