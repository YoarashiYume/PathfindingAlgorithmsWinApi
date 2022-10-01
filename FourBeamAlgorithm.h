#ifndef FOURBEAMALGORITHM_H_
#define FOURBEAMALGORITHM_H_
#include "TwoBeamAlgorithm.h"
/**
\brief Realization of Four Beam Algorithm
*/
class FourBeamAlgorithm final: public TwoBeamAlgorithm
{
public:
	/**
	\brief path building method
	\param pointList point list
	\return true if it was possible to build a path, otherwise false
	*/
	bool buildPath(std::vector<Point>& pointList) override;
	/**
	\brief path finding method
	\param pointList point list
	*/
	void findPath(std::vector<Point>& pointList) override;
private:
	/**
	\brief returns direction from one point to another point
	\param from,to points to find directions
	\return Direction
	*/
	Direction setDir(const Point * const from, const Point* const to);
	/**
	\brief runs from the start point to the end point, setting intermediate points as waypoints
	\param currPoint start point
	\param dir detour
	*/
	void setPath(Point* currPoint,const Direction dir);
};

#endif // !FOURBEAMALGORITHM_H_
