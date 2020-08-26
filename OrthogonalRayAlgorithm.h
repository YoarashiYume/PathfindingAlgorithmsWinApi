#ifndef ORTHOGONALRAYALGORITHM_H_
#define ORTHOGONALRAYALGORITHM_H_
#include "Algorithm.h"
class OrthogonalRayAlgorithm : public Algorithm
{
protected:
	float m_distance = FLT_MAX;
	float getDistanceToFinish(Point& currentPoint_);
	Point* finishPoint;
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
	Direction getPriority(Point& currentPoint_, Point& newPoint_);
public:
	virtual bool buildPath(std::vector<Point>& const pointList) override;
	void findPath(std::vector<Point>& const pointList) override;
};
#endif // !ORTHOGONALRAYALGORITHM_H_