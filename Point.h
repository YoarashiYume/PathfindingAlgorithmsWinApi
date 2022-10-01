#ifndef POINT_H_
#define POINT_H_
#include <utility>
#include <vector>
#include <d2d1.h>
#include <math.h>

/**
\brief Сlass stores information about the point of the field
*/

class Point final
{
public:

	/**
	\brief Sell types
	*/
	enum class Type
	{
		FREE,///< empty point
		BLOCK,///< blocked point
		START,///< starting point
		FINISH///< terminal point
	};
	const int COUNT_OF_POINT_TYPE = 4;
	/**
	\brief Sell states
	*/
	enum class State
	{
		VISITED,///< visited point
		NOT_VISITED,///< not yet visited
		PATH///< path point
	};
private:
	
	static int countOfStart;///< Count of starting points
	static int countOfFinish;///< Count of terminal points
	std::pair<int, int> m_location; ///< point location
	
	std::pair<int, int> m_pixelCenter;///< position of the center of the displayed square
	State m_State;///< point state
	
	Type m_Type;///< point type
	std::vector<std::reference_wrapper<Point>> neighbors; ///< Array of neighbors point 
	std::vector<D2D1::ColorF> m_color = {
		D2D1::ColorF::DarkGray,
		D2D1::ColorF(0.666,0,0),
		D2D1::ColorF(0.0627,0.615,0.768),
		D2D1::ColorF(0,0.784,1),
		D2D1::ColorF(0.96,1,0),
		D2D1::ColorF::DarkGray,
		D2D1::ColorF(0.654,0.768,0.98)
	}///< point color array

	/*for beam Algorithm*/
	bool isFromA = false;///< point met while constructing path A
	bool isFromB = false;///< point met while constructing path B
	
	bool m_isBorder = false;///< is a boundary point
	
	/*for Lee Algorithm*/
	int cost = -1;///< Number of moves from the starting cellpointto the current one
	
	/*for A-star*/
	int costG = INT_MAX;///< Number of moves from the starting point to the current one
	double costF{};///< estimated distance to target
	
	Point* previous = nullptr;///< previous point, used when creating a path
public:
	/**
	\brief Method sets the state of the point as visited
	*/
	void setVisited();
	/**
	\brief Method returns point type
	\return Point::n_Type
	*/
	Type getType() const;
	/**
	\brief Method sets point type
	\param newType_ new point type
	*/
	void setType(const Type newType_);
	/**
	\brief Method returns point state
	\return Point::m_State
	*/
	State getState() const;
	/**
	\brief Method sets point state
	\param newType_ new point state
	*/
	void setState(const State state_);
	
	/**
	\brief Method returns point color
	\return Color depending on the type
	*/
	D2D1::ColorF getColor()const;
	/**
	\brief Method returns point location
	\return Point::m_location
	*/
	std::pair<int, int> getLocation()const;
	/**
	\brief Method returns point graphic center location
	\return Point::m_pixelCenter
	*/
	std::pair<int, int> getPixelLocation()const;
	/**
	\brief Method adds a link to the neighboring point
	Method checks if the "other" point is adjacent. and, if so, adds a link
	\param other other Point
	*/
	void addNeighbors(Point& otherPoint);
	/**
	\brief Method returns neighbors list
	\return neighbors list
	*/
	std::vector<std::reference_wrapper<Point>>& getNeighbors();
	/**
	\brief Constructor
	\param x,y point coordinates
	\param isBorder_ is a boundary point
	\param state_ point type 
	\param type_ point type 
	*/
	Point(const int x_,const int y_,const bool isBorder_,const State state_,const Type type_);
	/**
	\brief returns point costs
	\return Point::cost
	*/
	int getCost()const;
	/**
	\brief sets point cost
	\param cost_ new cost
	*/
	void setCost(const int cost_);
	/**
	\brief whether the point is in one of the paths
	\return Point::isFromA and Point::isFromB
	*/
	std::pair<bool, bool> checkStateBeam()const;
	/**
	\brief changes state along path A
	\param new state
	*/
	void setIsFromA(const bool newState_);
	/**
	\brief changes state along path B
	\param new state
	*/
	void setIsFromB(const bool newState_);
	/**
	\brief returns boundary type
	\return true if point is boundary,otherwise false 
	*/
	bool isBorder() const;
	/**
	\brief returns estimated points costs
	\return Point::costF
	*/
	double getCostF() const;
	/**
	\brief sets Point::costF
	\param costF_ new estimated cost
	*/
	void setCostF(const double costF_);
	/**
	\brief returns point costs
	\return Point::costG
	*/
	int getCostG() const;
	/**
	\brief sets Point::costG
	\param costG_ new cost
	*/
	void setCostG(const int costG_);
	/**
	\brief Method sets previous point
	\param cell previous point
	*/
	void setPrevious(Point* previous_);
	/**
	\brief Method returns previous point
	\return previous point
	*/
	Point* getPrevious() const;
	/**
	\brief checks for the presence of a start and end point
	\return true if both points are set,otherwise false
	*/
	static bool isStartAndFinish() const;
};
#endif // !POINT_H_