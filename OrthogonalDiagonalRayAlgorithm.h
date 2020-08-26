#ifndef ORTHOGONALDIAGONALRAYALGORITHM_H_
#define ORTHOGONALDIAGONALRAYALGORITHM_H_
#include "OrthogonalRayAlgorithm.h"
class OrthogonalDiagonalRayAlgorithm : public OrthogonalRayAlgorithm
{
public:
	bool buildPath(std::vector<Point>& const pointList) override;
};
#endif // !ORTHOGONALRAYALGORITHM_H_