#ifndef ORTHOGONALRAYALGORITHM_H_
#define ORTHOGONALRAYALGORITHM_H_
#include "Algorithm.h"
/**
\brief Realization of the Orthogonal Ray Algorithm
*/
class OrthogonalRayAlgorithm : public Algorithm
{
protected:
	/**
	\brief the method calculates the distance from the current point to the finish
	calculated by the formula:
	\f[
		distance = \sqrt{(finishCell.x - currentCell.x)^{2})+(finishCell.y - currentCell.y)^{2})}
	\f]
	\param currentPoint current point
	\return distance to finish
	*/
	float getDistanceToFinish(const Point& currentPoint_) const;
	Point* finishPoint{nullptr};///< end point
	/**
	\brief Priority direction
	*/
	enum class Direction
	{
		RIGHT_DOWN,
		DOWN,
		LEFT_DOWN,
		LEFT,
		LEFT_UP,
		UP,
		RIGHT_UP,
		RIGHT
	};
	/**
	\brief choice of direction from one point to another
	\param currentPoint_,newPoint_ two points
	\return Direction
	*/
	Direction getPriority(const Point& currentPoint_,const Point& newPoint_) const;
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
	virtual ~OrthogonalRayAlgorithm() = default;
};
#endif // !ORTHOGONALRAYALGORITHM_H_