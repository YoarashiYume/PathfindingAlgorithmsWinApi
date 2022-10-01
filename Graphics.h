#ifndef  GRAPHICS_H_
#define GRAPHICS_H_
#include<d2d1.h>
#include<Windows.h>
#include "Field.h"
/**
\brief class responsible for rendering the field
*/
class Graphics final
{
private:
	ID2D1SolidColorBrush* m_pBrush;///< brush
	ID2D1Factory* m_pD2D1Factory;///< d2d1 factory
	ID2D1HwndRenderTarget* m_pRT;///< d2d1 drawing surface
	PAINTSTRUCT pt; ///< contains information for staining
	HWND* m_pHwnd;///< drawing surface
	/**
	\brief Method convert pixels to dpi
	\return return X position
	*/
	float pixelToDPIX(const float x) const;
	/**
	\brief Method convert pixels to dpi
	\return return Y position
	*/
	float pixelToDPIY(const float y) const;
	/**
	\brief Method convert dpi to pixels
	\return return X dpi
	*/
	float dpiToPixelX(const float x_)const;
	/**
	\brief Method convert dpi to pixels
	\return return Y dpi
	*/
	float dpiToPixelY(const float y_) const;
	float dpiX;///< current dpi for X axes
	float dpiY;///< current dpi for Y axes
	float offsetXinDPI;///< offset by X in dpi
	float offsetYinDPI;///< offset by Y in dpi
public:
	/**
	\brief Destructor
	*/
	~Graphics();
	/**
	\brief Constructor
	\param dpiX_,dpiY_  current dpi
	\param hwnd handle to the element to draw
	\param pD2D1Factory pD2D1Factory
	\param pRT pointer to drawing interface
	*/
	Graphics(HWND* hwnd_, ID2D1Factory* pD2D1Factory, ID2D1HwndRenderTarget* pRT,const int dpiX_,const int dpiY_);
	/**
	\brief updates the field when the field size changes
	\param dpiX_,dpiY_  current dpi
	\param f field
	*/
	void changeField(Field& f,const int dpiX_,const int dpiY_);
	/**
	\brief redraws the field
	\param f field
	*/
	void printFullField(Field& f);
	/**
	\brief draws the changed elements
	\param f field
	*/
	void repaintField(Field& f);
	/**
	\brief method resets information about all points
	*/
	void clear(Field& f);
};
#endif // ! GRAPHICS_H_

