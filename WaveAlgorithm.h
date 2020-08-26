#ifndef WAVEALGORITHM_H_
#define WAVEALGORITHM_H_
#include "Algorithm.h"
class WaveAlgorithm : public Algorithm
{
public:
	bool buildPath(std::vector<Point>& const pointList) override;
	void findPath(std::vector<Point>& const pointList) override;
};

#endif // !WAVEALGORITHM_H_