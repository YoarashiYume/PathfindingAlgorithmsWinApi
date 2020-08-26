#ifndef FIELD_H_
#define FIELD_H_
#include <vector>
#include <d2d1.h>
#include <math.h>
#include "Point.h"
class Field
{
private:
	std::vector<Point> m_listOfPoint;
	int m_size;
public:
	Field(int size_);
	void refreshField();
	std::pair<D2D1::ColorF, std::pair<int, int>> repaintField(float pixelX_, float pixelY_);
	std::pair<D2D1::ColorF, std::pair<int, int>> getColorAndLocation(float pixelX_, float pixelY_);
	int getSize();
	void clear();
	std::vector<Point>& getList();
	bool canBuild();
};
#endif // !FIELD_H_
