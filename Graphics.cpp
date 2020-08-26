#include "Graphics.h"

Graphics::~Graphics()
{
	m_pBrush->Release();
	m_pBrush = nullptr;
}

Graphics::Graphics(HWND* hwnd_, ID2D1Factory* pD2D1Factory,ID2D1HwndRenderTarget* pRT, int dpiX_, int dpiY_)
{
	m_pD2D1Factory = pD2D1Factory;
	m_pRT = pRT;
	dpiX = dpiX_;
	dpiY = dpiY_;
	offsetXinDPI = pixelToDPIX(230);
	offsetYinDPI = pixelToDPIY(0);
	m_pHwnd = hwnd_;
	m_pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::DarkGray),
		&m_pBrush);
}

void Graphics::changeField(Field& f,int dpiX_,int dpiY_)
{
	auto colorAndLocation = f.repaintField(dpiToPixelX(dpiX_ - offsetXinDPI), dpiToPixelY(dpiY_ - offsetYinDPI) );
	if (colorAndLocation.second.first != -1)
	{
		m_pRT->CreateSolidColorBrush(
			colorAndLocation.first,
			&m_pBrush);
		BeginPaint(*m_pHwnd, &pt);
		m_pRT->BeginDraw();
		int x = colorAndLocation.second.first - 8;
		int dx = x + 16;
		int y = colorAndLocation.second.second - 8;
		int dy = y + 16;
		m_pRT->FillRectangle(
			D2D1::RectF(
				pixelToDPIX(x) + offsetXinDPI,
				pixelToDPIY(y) + offsetYinDPI,
				pixelToDPIX(dx) + offsetXinDPI,
				pixelToDPIY(dy) + offsetYinDPI),
			m_pBrush);
		m_pRT->EndDraw();
		EndPaint(*m_pHwnd, &pt);
	}
}

void Graphics::printFullField(Field& f)
{
	BeginPaint(*m_pHwnd, &pt);
	m_pRT->BeginDraw();
	m_pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
	m_pRT->FillRectangle(
		D2D1::RectF(
			0 + offsetXinDPI,
			0 + offsetYinDPI,
			pixelToDPIX(f.getSize() * 17) + offsetXinDPI,
			pixelToDPIY(f.getSize() * 17) + offsetYinDPI),
		m_pBrush
	);
	m_pRT->EndDraw();
	EndPaint(*m_pHwnd, &pt);
}

void Graphics::repaintField(Field& f)
{
	BeginPaint(*m_pHwnd, &pt);
	m_pRT->BeginDraw();
	for (auto el : f.getList())
	{
		if (el.getType() == Point::Type::FINISH || el.getType() == Point::Type::START)
			continue;
		auto colorAndLocation = f.getColorAndLocation(el.getPixelLocation().first, el.getPixelLocation().second);
		m_pBrush->SetColor(colorAndLocation.first);
		int x = colorAndLocation.second.first - 8;
		int dx = x + 16;
		int y = colorAndLocation.second.second - 8;
		int dy = y + 16;
		m_pRT->FillRectangle(
			D2D1::RectF(
				pixelToDPIX(x) + offsetXinDPI,
				pixelToDPIY(y) + offsetYinDPI,
				pixelToDPIX(dx) + offsetXinDPI,
				pixelToDPIY(dy) + offsetYinDPI),
			m_pBrush);
	}
	m_pRT->EndDraw();
	EndPaint(*m_pHwnd, &pt);
}

void Graphics::clear(Field& f)
{
	f.clear();
	printFullField(f);
}

float Graphics::pixelToDPIX(float x)
{
	return x * 96 / dpiX;
}

float Graphics::pixelToDPIY(float y)
{
	return y * 96 / dpiY;
}

float Graphics::dpiToPixelX(float x_)
{
	return x_ * dpiX / 96;
}
float Graphics::dpiToPixelY(float y_)
{
	return y_ * dpiY / 96;
}
