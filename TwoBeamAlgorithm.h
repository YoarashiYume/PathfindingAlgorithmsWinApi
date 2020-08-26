#ifndef TWOBEAMALGORITHM_H_
#define TWOBEAMALGORITHM_H_
#include "Algorithm.h"
class TwoBeamAlgorithm : public Algorithm
{

protected:

	enum class Direction {
		UP,
		LEFT,
		RIGHT,
		DOWN
	};
	bool isPath = false;
	std::pair<int, int> resultDir = std::make_pair(-1, -1);
	virtual bool buildPath(std::vector<Point>& const pointList) override;
	Point* interestedNeighbour(Point& currentPoint, Direction dir_, Point::Type endType);
private:
	bool alpha, beta;
	bool isItCorrectDirect(Point* startPoint_, Direction mainDir_, Direction subDir_);
	void buildPath(Point* startPoint_, Direction mainDir_, Direction subDir_);

public:

	void findPath(std::vector<Point>& const pointList) override;
	void buildWay(Point* startPoint_, Direction mainDir_, Direction subDir_);

};
#endif // !TWOBEAMALGORITHM_H_