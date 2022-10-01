#include "Graphics.h"

Graphics::~Graphics()
{
	m_pBrush->Release();
	m_pBrush = nullptr;
}

Graphics::Graphics(HWND* hwnd_, ID2D1Factory* pD2D1Factory, ID2D1HwndRenderTarget* pRT,const int dpiX_,const int dpiY_)
{
	m_pD2D1Factory = pD2D1Factory;
	m_pRT = pRT;
	dpiX = static_cast<float>(dpiX_);
	dpiY = static_cast<float>(dpiY_);
	offsetXinDPI = pixelToDPIX(230.f);
	offsetYinDPI = pixelToDPIY(0.f);
	m_pHwnd = hwnd_;
	m_pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::DarkGray),
		&m_pBrush);
}

void Graphics::changeField(Field& f,const int dpiX_,const int dpiY_)
{
	auto colorAndLocation = f.repaintField(dpiToPixelX(dpiX_ - offsetXinDPI), dpiToPixelY(dpiY_ - offsetYinDPI) );
	if (colorAndLocation.second.first != -1)
	{
		m_pRT->CreateSolidColorBrush(
			colorAndLocation.first,
			&m_pBrush);
		BeginPaint(*m_pHwnd, &pt);
		m_pRT->BeginDraw();
		float x = static_cast<float>(colorAndLocation.second.first - 8);
		float dx = static_cast<float>(x + 16);
		float y = static_cast<float>(colorAndLocation.second.second - 8);
		float dy = static_cast<float>(y + 16);
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
			pixelToDPIX(static_cast<float>(f.getSize() * 17)) + offsetXinDPI,
			pixelToDPIY(static_cast<float>(f.getSize() * 17)) + offsetYinDPI),
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
		auto colorAndLocation = f.getColorAndLocation(static_cast<float>(el.getPixelLocation().first),
			static_cast<float>(el.getPixelLocation().second));
		m_pBrush->SetColor(colorAndLocation.first);
		float x = static_cast<float>(colorAndLocation.second.first - 8);
		float dx = static_cast<float>(x + 16);
		float y = static_cast<float>(colorAndLocation.second.second - 8);
		float dy = static_cast<float>(y + 16);
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
 
float Graphics::pixelToDPIX(const float x) const
{
	return x * 96 / dpiX;
}

float Graphics::pixelToDPIY(const float y) const
{
	return y * 96 / dpiY;
}

float Graphics::dpiToPixelX(const float x_) const
{
	return x_ * dpiX / 96;
}
float Graphics::dpiToPixelY(const float y_) const
{
	return y_ * dpiY / 96;
}
