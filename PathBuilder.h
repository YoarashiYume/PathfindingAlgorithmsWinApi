#ifndef PATHBUILDER_H_
#define PATHBUILDER_H_
#include "Algorithm.h"
#include "Field.h"
class PathBuilder
{
public:
	int buildPatch(Algorithm* algorithm, Field& f);
};

#endif // !PATHBUILDER_H_