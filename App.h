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

#include <stdexcept>
#include <d2d1.h>
/**
\brief App class
*/
class App final
{
private:
	/**
	\brief list of button (and buttons action)
	*/
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
	int m_appWidth = 1000;///< current window width
	int m_appHeight = 800;///< current window height
	bool isFirst = true;///< app just opened flag
	bool isCleared = false;///< is field clear flag
	HWND m_hWnd, m_hButtonSetSize, m_hButtonClear, m_hButtonStart, m_hEdit;///< control descriptors
	HWND m_hWave, m_hOrtoganal, m_hOrtoganalD, m_hTwoBeam, m_hFourBeam, m_hAstar;///< algorithm switch button descriptors
	ID2D1Factory* pD2D1Factory; ///< direct2d factory
	ID2D1HwndRenderTarget* pRT; ///< direct2d drawing interface
	MSG msg; ///< window interaction information

	const std::wstring m_szAppName = L"Algorithm"; ///< App title
	const std::wstring m_szClassName = L"Algorithm Window";///< app class name
	/**
	\brief Method initializes the window
	*/
	void init_native_window_obj();
	/**
	\brief Method initializes the control components
	*/
	void create_native_controls();

	/**
	\brief Safe release of d2d1 objects
	\param obj pointer to d2d1 object
	*/
	template<typename T>
	void SafeRelease(T** obj);
	/**
	\brief Window registration method
	\param hwnd Window procedure handle
	\param uMsg message
	\param wParam,lParam additional information message
	\return DefWindowProc value
	*/
	static LRESULT CALLBACK application_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	/**
	\brief message handling method
	\param hwnd Window procedure handle
	\param uMsg message
	\param wParam,lParam additional information message
	\return DefWindowProc value
	*/
	LRESULT CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	/**
	\brief Constructor with base screen height and width values (1280x800)
	*/
	explicit App();
	/**
	\brief Destructor
	*/
	~App();
	/**
	\brief  Method launches the graphical application
	\return exit code
	*/
	int run();
private:
	/**
	\brief method reads field size
	\return text from App::m_hEdit
	*/
	std::string readSize() const;
	
	Field* f = nullptr;///< created field
	Graphics* disp = nullptr;///< graphic component
	Algorithm* al = nullptr;///< current algorithm
	int m_ButtonSize = 220;///< button X size
};
#endif // !APP_H_