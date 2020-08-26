#ifndef FOURBEAMALGORITHM_H_
#define FOURBEAMALGORITHM_H_
#include "TwoBeamAlgorithm.h"
class FourBeamAlgorithm : public TwoBeamAlgorithm
{
public:
	bool buildPath(std::vector<Point>& const pointList) override;
	void findPath(std::vector<Point>& const pointList) override;
private:
	Direction setDir(Point* from, Point* to);
	void setPath(Point* currPoint, Direction dir);
};

#endif // !FOURBEAMALGORITHM_H_
