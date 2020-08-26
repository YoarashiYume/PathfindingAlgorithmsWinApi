#ifndef POINT_H_
#define POINT_H_
#include <utility>
#include <vector>
#include <d2d1.h>
#include <math.h>
class Point
{
public:
	enum class Type
	{
		FREE,
		BLOCK,
		START,
		FINISH
	};
	enum class State
	{
		VISITED,
		NOT_VISITED,
		PATH
	};
private:
	const int cCountofType = 4;
	static int countOfStart;
	static int countOfFinish;
	std::pair<int, int> m_location;
	std::pair<int, int> m_pixelCenter;
	State m_State;
	Type m_Type;
	std::vector<std::reference_wrapper<Point>> neighbors;
	std::vector<D2D1::ColorF> m_color = {
		D2D1::ColorF::DarkGray,
		D2D1::ColorF(0.666,0,0),
		D2D1::ColorF(0.0627,0.615,0.768),
		D2D1::ColorF(0,0.784,1),
		//D2D1::ColorF(0.596,0.741,0.074),
		D2D1::ColorF(0.96,1,0),
		D2D1::ColorF::DarkGray,
		D2D1::ColorF(0.654,0.768,0.98)
		//D2D1::ColorF(0.41,0,1)
	};
	/*for beam Algorithm*/
	bool isFromA = false;
	bool isFromB = false;
	bool m_isBorder = false;
	/*for Lee Algorithm*/
	int cost = -1;
	/*for A-star*/
	int costG = INT_MAX;
	double costF;
	Point* previous = nullptr;
public:
	void setVisited();
	Type getType();
	void setType(Type newType_);
	State getState();
	void setState(State state_);
	D2D1::ColorF getColor();
	std::pair<int, int> getLocation();
	std::pair<int, int> getPixelLocation();
	void addNeighbors(Point& otherPoint);
	std::vector<std::reference_wrapper<Point>>& getNeighbors();
	Point(int x_, int y_, bool isBorder_, State state_, Type type_);
	int getCost();
	void setCost(int cost_);
	std::pair<bool, bool> checkStateBeam();
	void setIsFromA(bool newState_);
	void setIsFromB(bool newState_);
	bool isBorder();
	double getCostF();
	void setCostF(double costF_);
	int getCostG();
	void setCostG(int costG_);
	void setPrevious(Point* previous_);
	Point* getPrevious();
	static bool isStartAndFinish();
};
#endif // !POINT_H_