#include "Algorithm.h"

bool Algorithm::isOrtogonal(const Point& first_, const Point& second_)const
{
	return ((first_.getLocation().first - second_.getLocation().first == 0
		&& abs(first_.getLocation().second - second_.getLocation().second) == 1)
		|| (abs(first_.getLocation().first - second_.getLocation().first) == 1
			&& first_.getLocation().second - second_.getLocation().second == 0));

}
