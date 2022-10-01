#ifndef APP_H_
#define APP_H_
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib,"d2d1")
#pragma warning(disable: 4996)
#include <Windows.h>
#include <string>
#include "Field.h"
#include "Graphics.h"
#include "algorithms.h"
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <d2d1.h>

class App
{
private:
	enum CTL_ID {
		CLEARBUTTON_ID,
		SETSIZEBUTTON_ID,
		WAVEBUTTON_ID,
		ORTOGANALBUTTON_ID,
		ORTOGANALDBUTTON_ID,
		TWOBEAMBUTTON_ID,
		FOURBEAMBUTTON_ID,
		ASTARBUTTON_ID,
		StartButton_ID,
		OTHER_ID
	};
	int m_appWidth = 1000;
	int m_appHeight = 800;
	bool isFirst = true;
	bool isCleared = false;
	HWND m_hWnd, m_hButtonSetSize, m_hButtonClear, m_hButtonStart, m_hEdit;
	HWND m_hWave, m_hOrtoganal, m_hOrtoganalD, m_hTwoBeam, m_hFourBeam, m_hAstar;
	ID2D1Factory* pD2D1Factory;
	ID2D1HwndRenderTarget* pRT;
	MSG msg;

	const std::wstring m_szAppName = L"Algorithm";
	const std::wstring m_szClassName = L"Algorithm Window";

	void init_native_window_obj();
	void create_native_controls();


	template<typename T>
	void SafeRelease(T** obj);

	static LRESULT CALLBACK application_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	explicit App();
	~App();
	int run();
private:
	std::string readSize();
	std::string text = "";
	Field* f = nullptr;
	Graphics* disp = nullptr;
	Algorithm* al = nullptr;
	int m_ButtonSize = 220;
};
#endif // !APP_H_