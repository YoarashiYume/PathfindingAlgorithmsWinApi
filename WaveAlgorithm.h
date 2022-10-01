#ifndef WAVEALGORITHM_H_
#define WAVEALGORITHM_H_
#include "Algorithm.h"
/**
\brief Realization of Lee algorithm
*/

class WaveAlgorithm final: public Algorithm
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
	virtual ~WaveAlgorithm() = default;
};

#endif // !WAVEALGORITHM_H_