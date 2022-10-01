#ifndef ORTHOGONALDIAGONALRAYALGORITHM_H_
#define ORTHOGONALDIAGONALRAYALGORITHM_H_
#include "OrthogonalRayAlgorithm.h"
/**
\brief Realization of the Orthogonal Diagonal Ray Algorithm
*/
class OrthogonalDiagonalRayAlgorithm  final: public OrthogonalRayAlgorithm
{
public:
/**
	\brief path building method
	\param pointList point list
	\return true if it was possible to build a path, otherwise false
	*/
	bool buildPath(std::vector<Point>&  pointList) override;
};
#endif // !ORTHOGONALRAYALGORITHM_H_