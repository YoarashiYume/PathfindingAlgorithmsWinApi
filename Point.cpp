#include "Point.h"

void Point::setVisited()
{
	m_State = Point::State::VISITED;
}

Point::Type Point::getType() const
{
	return m_Type;
}

void Point::setType(const Type newType_)
{
	switch (newType_)
	{
	case Point::Type::FREE:
	case Point::Type::BLOCK:
		if (m_Type == Point::Type::START)
			--countOfStart;
		else if
			(m_Type == Point::Type::FINISH)
			--countOfFinish;
		m_Type = newType_;
		break;
	case Point::Type::START:
		if (countOfStart == 0)
		{
			m_Type = newType_;
			++countOfStart;
		}
		else if (countOfFinish == 0)
		{
			m_Type = Point::Type::FINISH;
			++countOfFinish;
		}
		else
			m_Type = Point::Type::FREE;
		break;
	case Point::Type::FINISH:
		if (m_Type == Point::Type::START)
			--countOfStart;
		if (countOfFinish == 0)
		{
			m_Type = newType_;
			++countOfFinish;
		}
		else
			m_Type = Point::Type::FREE;
		break;
	default:
		break;
	}
	
}

Point::State Point::getState() const
{
	return m_State;
}

void Point::setState(const State state_)
{
	m_State = state_;
}

D2D1::ColorF Point::getColor() const
{
	if (m_State == Point::State::NOT_VISITED)
		return m_color.at(static_cast<int> (m_Type));
	else
		return m_color.at(static_cast<int> (m_State) + COUNT_OF_POINT_TYPE);
}

std::pair<int, int> Point::getLocation() const
{
	return m_location;
}

std::pair<int, int> Point::getPixelLocation() const
{
	return m_pixelCenter;
}

void Point::addNeighbors(Point& otherPoint)
{
	if (neighbors.size() < 8 && otherPoint.getLocation() != this->getLocation())
		if (abs(this->m_location.first - otherPoint.m_location.first) <= 1)
			if (abs(this->m_location.second - otherPoint.m_location.second) <= 1)
				if (otherPoint.m_Type != Point::Type::BLOCK)
					neighbors.push_back(otherPoint);
}

std::vector<std::reference_wrapper<Point>>& Point::getNeighbors()
{
	return neighbors;
}

Point::Point(const int x_,const int y_,const bool isBorder_,const State state_,const Type type_)
{
	constexpr PIXEL_HALF_SIZE = 8;
	m_location = std::make_pair(x_, y_);
	m_pixelCenter = std::make_pair((2*PIXEL_HALF_SIZE+1) * x_ + PIXEL_HALF_SIZE, (2*PIXEL_HALF_SIZE+1) * y_ + PIXEL_HALF_SIZE);
	m_State = state_;
	m_Type = type_;
	m_isBorder = isBorder_;
}
int Point::getCost() const
{
	return cost;
}
void Point::setCost(const int cost_)
{
	cost = cost_;
}
std::pair<bool, bool> Point::checkStateBeam() const
{
	return std::make_pair(isFromA,isFromB);
}
void Point::setIsFromA(const bool newState_) const
{
	isFromA = newState_;
}
void Point::setIsFromB(const bool newState_)
{
	isFromB = newState_;
}
bool Point::isBorder() const
{
	return m_isBorder;
}
double Point::getCostF() const
{
	return costF;
}
void Point::setCostF(const double costF_)
{
	costF = costF_;
}
int Point::getCostG() const
{
	return costG;
}
void Point::setCostG(const int costG_)
{
	costG = costG_;
}
void Point::setPrevious(Point* previous_) 
{
	previous = previous_;
}
Point* Point::getPrevious() const
{
	return previous;
}
bool Point::isStartAndFinish() const
{
	return countOfFinish!=0 && countOfStart!=0;
}
int Point::countOfFinish = 0;
int Point::countOfStart = 0;