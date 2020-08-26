#ifndef  GRAPHICS_H_
#define GRAPHICS_H_
#include<d2d1.h>
#include<Windows.h>
#include "Field.h"
class Graphics
{
private:
	ID2D1SolidColorBrush* m_pBrush;
	ID2D1Factory* m_pD2D1Factory;
	ID2D1HwndRenderTarget* m_pRT;
	PAINTSTRUCT pt;
	HWND* m_pHwnd;
	float pixelToDPIX(float x);
	float pixelToDPIY(float y);
	float dpiToPixelX(float x_);
	float dpiToPixelY(float y_);
	float dpiX;
	float dpiY;
	float offsetXinDPI;
	float offsetYinDPI;
public:
	~Graphics();
	Graphics(HWND* hwnd_, ID2D1Factory* pD2D1Factory, ID2D1HwndRenderTarget* pRT, int dpiX_, int dpiY_);
	void changeField(Field& f, int dpiX_, int dpiY_);
	void printFullField(Field& f);
	void repaintField(Field& f);
	void clear(Field& f);
};
#endif // ! GRAPHICS_H_

