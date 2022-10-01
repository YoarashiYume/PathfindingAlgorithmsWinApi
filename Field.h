#ifndef FIELD_H_
#define FIELD_H_
#include <vector>
#include <d2d1.h>
#include <math.h>
#include "Point.h"
/**
\brief Сlass contains information about points
*/
class Field final
{
private:
	std::vector<Point> m_listOfPoint;///< list of point
	int m_size;///< field size
public:
	/**
	\brief Constructor
	\param size_ field side
	*/
	Field(const int size_);
	/**
	\brief method resets visit information
	*/
	void refreshField();
	/**
	\brief changes the color of the cell
	\param pixelX_,pixelY_ fmouse click coordinates
	\return position of the center of the displayed Point and its color
	*/
	std::pair<D2D1::ColorF, std::pair<int, int>> repaintField(const float pixelX_,const float pixelY_);
	/**
	\brief determines point data by mouse click coordinates
	\param pixelX_,pixelY_ fmouse click coordinates
	\return position of the center of the displayed Point and its color
	*/
	std::pair<D2D1::ColorF, std::pair<int, int>> getColorAndLocation(const float pixelX_,const float pixelY_) const;
	/**
	\brief returns the field size
	\return Field::m_size
	*/
	int getSize() const;
	/**
	\brief method resets information about all points
	*/
	void clear();
	/**
	\brief method returns point list
	\return Field::m_listOfPoint
	*/
	std::vector<Point>& getList();
	/**
	\brief checks for the presence of a start and end point
	\return true if both points are set,otherwise false
	*/
	bool canBuild() const;
};
#endif // !FIELD_H_
