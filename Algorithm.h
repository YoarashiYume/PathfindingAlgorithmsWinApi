#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <vector>

#include "Point.h"
/**
\brief base class for algorithms
*/
class Algorithm
{
public:
	/**
	\brief path building method
	\param pointList point list
	\return true if it was possible to build a path, otherwise false
	*/
	virtual bool buildPath(std::vector<Point>& const pointList) = 0;
	/**
	\brief path finding method
	\param pointList point list
	*/
	virtual void findPath(std::vector<Point>& const pointList) = 0;
	/**
	\brief path finding methodcheck if points are non-diagonal neighbors
	\return true if they are, otherwise false
	*/
	bool isOrtogonal(const Point& first_,const Point& second_) const ;
	/**
	\brief Destructor
	*/
	virtual ~Algorithm() = default;
};
#endif // !#define ALGORITHM_H



