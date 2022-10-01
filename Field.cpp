#include "Field.h"

Field::Field(const int size_)
{
	m_size = size_;
	for (std::int32_t y = 0; y < size_; ++y)
		for (std::int32_t x = 0; x < size_; ++x)
			m_listOfPoint.push_back(Point(x, y,(x == 0 || x==size_-1 || y == size_-1 || y==0), Point::State::NOT_VISITED, Point::Type::FREE));
	for (Point& point : m_listOfPoint)
		for (Point& otherPoint : m_listOfPoint)
			point.addNeighbors(otherPoint);
}

void Field::refreshField()
{
	for (Point& point : m_listOfPoint)
		point.setState(Point::State::NOT_VISITED);
}

std::pair<D2D1::ColorF,std::pair<int,int>> Field::repaintField(const float pixelX_,const float pixelY_)
{
	for (Point& point : m_listOfPoint)
		if (abs(pixelX_ - point.getPixelLocation().first)<9)
			if (abs(pixelY_ - point.getPixelLocation().second) <9)
			{
				if (point.getType() == Point::Type::FINISH)
					point.setType(Point::Type::FREE);
				else
					point.setType(static_cast<Point::Type> (static_cast<int> (point.getType()) + 1));
				return std::make_pair(point.getColor(),point.getPixelLocation());
			}
	return std::make_pair(-1, std::make_pair(-1,-1));
}

std::pair<D2D1::ColorF, std::pair<int, int>> Field::getColorAndLocation(const float pixelX_,const float pixelY_) const
{
	for (const Point& point : m_listOfPoint)
		if (abs(pixelX_ - point.getPixelLocation().first) < 9)
			if (abs(pixelY_ - point.getPixelLocation().second) < 9)
				return std::make_pair(point.getColor(), point.getPixelLocation());
	return { D2D1::ColorF{0,0,0},{-1,-1} };
}

int Field::getSize() const
{
	return m_size;
}

void Field::clear()
{
	for (auto& el : m_listOfPoint)
	{
		el.setCost(-1);
		el.setState(Point::State::NOT_VISITED);
		el.setType(Point::Type::FREE);
		el.setIsFromA(false);
		el.setIsFromB(false);
		el.setCostF(INT_MAX);
		el.setCostG(INT_MAX);
		el.setPrevious(nullptr);
	}
}



std::vector<Point>& Field::getList()
{
	return m_listOfPoint;
}

bool Field::canBuild() const
{
	return Point::isStartAndFinish();
}
