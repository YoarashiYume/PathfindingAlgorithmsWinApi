#include "App.h"

App::App()
{
	try
	{
		this->init_native_window_obj();
		this->create_native_controls();
	}
	catch (const std::exception& ex)
	{
		std::string exeptionInfo = ex.what();
		MessageBox(nullptr, std::wstring(exeptionInfo.begin(), exeptionInfo.end()).c_str(), L"Error", MB_ICONERROR | MB_OK);
		ExitProcess(EXIT_FAILURE);
	}
}

App::~App()
{
	SafeRelease(&pD2D1Factory);
	SafeRelease(&pRT);
	delete f;
	delete disp;
	delete al;
}

int App::run()
{
	ShowWindow(this->m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(this->m_hWnd);
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int> (msg.wParam);
}

std::string App::readSize() const
{
	std::wstring text{};
	text.resize(MAX_PATH);
	GetWindowText(this->m_hEdit, &text[0], MAX_PATH);
	text.erase(remove(text.begin(), text.end(), 0), text.end());
	if (text.empty())
		return "";
	std::string temp(text.begin(), text.end());
	return temp;
}



void App::init_native_window_obj()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED, &pD2D1Factory);
	if (!SUCCEEDED(hr))
		throw std::runtime_error("Cannot create factory");
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = this->m_szClassName.c_str();
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = App::application_proc;


	if (!RegisterClassEx(&wc)) throw std::runtime_error("Cannot register main window");

	RECT windowRC{ 0,0,this->m_appWidth,this->m_appHeight };
	AdjustWindowRect(&windowRC, WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX  /*|WS_MAXIMIZEBOX | WS_OVERLAPPEDWINDOW */, false);
	this->m_hWnd = CreateWindowEx(
		0,
		this->m_szClassName.c_str(),
		this->m_szAppName.c_str(),
		WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX /*| WS_MAXIMIZEBOX | WS_OVERLAPPEDWINDOW*/,
		(GetSystemMetrics(SM_CXSCREEN) - windowRC.right) / 2,
		(GetSystemMetrics(SM_CXSCREEN) - windowRC.bottom) / 2,
		windowRC.right, windowRC.bottom, nullptr, nullptr, nullptr, this
	);
	if (!this->m_hWnd)
		throw std::runtime_error("Cannot create main window");

}

void App::create_native_controls()
{
	this->m_hEdit = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"Edit",
		L"Size",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		0, 0, m_ButtonSize, 30,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::OTHER_ID), nullptr, nullptr
	);
	if (!this->m_hEdit)
		throw std::runtime_error("Cannot create edit");
	this->m_hButtonSetSize = CreateWindowEx(
		0,
		L"Button",
		L"Set Size",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 40, m_ButtonSize, 30,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::SETSIZEBUTTON_ID), nullptr, nullptr
	);
	if (!this->m_hButtonSetSize)
		throw std::runtime_error("Cannot create size button");
	this->m_hWave = CreateWindowEx(
		0,
		L"Button",
		L"Wave Algorithm",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 80, m_ButtonSize, 30,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::WAVEBUTTON_ID), nullptr, nullptr
	);
	if (!this->m_hWave)
		throw std::runtime_error("Cannot create Wave button");
	this->m_hOrtoganal = CreateWindowEx(
		0,
		L"Button",
		L"Ortoganal Algorithm",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 120, m_ButtonSize, 30,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::ORTOGANALBUTTON_ID), nullptr, nullptr
	);
	if (!this->m_hOrtoganal)
		throw std::runtime_error("Cannot create Ortoganal button");
	this->m_hOrtoganalD = CreateWindowEx(
		0,
		L"Button",
		L"Ortoganal-Diagonal Algorithm",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 160, m_ButtonSize, 30,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::ORTOGANALDBUTTON_ID), nullptr, nullptr
	);
	if (!this->m_hOrtoganalD)
		throw std::runtime_error("Cannot create Ortoganal-Diagonal button");
	this->m_hTwoBeam = CreateWindowEx(
		0,
		L"Button",
		L"Two Beam Algorithm",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 200, m_ButtonSize, 30,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::TWOBEAMBUTTON_ID), nullptr, nullptr
	);
	if (!this->m_hTwoBeam)
		throw std::runtime_error("Cannot create Two Beam button");
	this->m_hFourBeam = CreateWindowEx(
		0,
		L"Button",
		L"Four Beam Algorithm",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 240, m_ButtonSize, 30,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::FOURBEAMBUTTON_ID), nullptr, nullptr
	);
	if (!this->m_hFourBeam)
		throw std::runtime_error("Cannot create Four Beam button");
	this->m_hAstar = CreateWindowEx(
		0,
		L"Button",
		L"A* Algorithm",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 280, m_ButtonSize, 30,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::ASTARBUTTON_ID), nullptr, nullptr
	);
	if (!this->m_hAstar)
		throw std::runtime_error("Cannot create A* button");
	this->m_hButtonStart = CreateWindowEx(
		0,
		L"Button",
		L"Strart",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 320, m_ButtonSize, 30,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::StartButton_ID), nullptr, nullptr
	);
	if (!this->m_hButtonStart)
		throw std::runtime_error("Cannot create Strart button");

	this->m_hButtonClear = CreateWindowEx(
		0,
		L"Button",
		L"Clear",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 360, m_ButtonSize, 30,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::CLEARBUTTON_ID), nullptr, nullptr
	);
	if (!this->m_hButtonClear)
		throw std::runtime_error("Cannot create Clear button");
	pD2D1Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hWnd, D2D1::SizeU(1267, 764)), &pRT);
	RECT temp;
	GetClientRect(m_hWnd, &temp);
	pRT->Resize(D2D1::SizeU(
		temp.right - temp.left,
		temp.bottom - temp.top
	));
	HFONT hFont = CreateFont(18, 0, 0, 0, FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Roboto");
	SendMessage(this->m_hButtonClear, WM_SETFONT, (WPARAM)hFont, true);
	SendMessage(this->m_hButtonSetSize, WM_SETFONT, (WPARAM)hFont, true);
	SendMessage(this->m_hButtonStart, WM_SETFONT, (WPARAM)hFont, true);
	SendMessage(this->m_hWave, WM_SETFONT, (WPARAM)hFont, true);
	SendMessage(this->m_hOrtoganal, WM_SETFONT, (WPARAM)hFont, true);
	SendMessage(this->m_hOrtoganalD, WM_SETFONT, (WPARAM)hFont, true);
	SendMessage(this->m_hTwoBeam, WM_SETFONT, (WPARAM)hFont, true);
	SendMessage(this->m_hFourBeam, WM_SETFONT, (WPARAM)hFont, true);
	SendMessage(this->m_hAstar, WM_SETFONT, (WPARAM)hFont, true);
	float xTEMP = 0;
	float yTEMP = 0;
	pD2D1Factory->GetDesktopDpi(&xTEMP, &yTEMP);
	disp = new Graphics(&m_hWnd, pD2D1Factory, pRT, static_cast<std::int32_t>(xTEMP), static_cast<std::int32_t>(yTEMP));
}


LRESULT App::application_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	App* pApp;
	if (uMsg == WM_NCCREATE)
	{
		pApp = static_cast<App*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp)))
			if (GetLastError() != 0)
				return false;
	}
	else
		pApp = reinterpret_cast<App*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (pApp)
	{
		pApp->m_hWnd = hwnd;
		return pApp->window_proc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT App::window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		MessageBox(this->m_hWnd, L" Dark Gray cell - free cell\n Dark Blue cell - start cell\n Light Blue cell - finish cell\n Dark Red cell - blocked cell\n Yellow cell - visited cell\n Light Violet cell - path cell", L"Info", MB_OK);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return 0;
	case WM_LBUTTONDOWN:
	{
		if (!f)
			break;
		if (!isCleared)
		{
			disp->clear(*f);
			isCleared = true;
		}
		disp->changeField(*f, LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	case WM_COMMAND:
	{
		switch (static_cast<App::CTL_ID>(LOWORD(wParam)))
		{
		case App::CTL_ID::SETSIZEBUTTON_ID:
		{
			std::string text = readSize();
			if (text == "")
				break;
			if (std::find_if(text.begin(),text.end(), [](unsigned char c) {	return std::isdigit(c); }) == text.end())
				break;
			if (f)
				delete f;
			f = new Field(std::stoi(text) <= 44 ? std::stoi(text) : 44);
			disp->printFullField(*f);				
			break;
		}
		case App::CTL_ID::WAVEBUTTON_ID:
			if (al)
				delete al;
			al = new WaveAlgorithm();
			break;
		case App::CTL_ID::TWOBEAMBUTTON_ID:
			if (al)
				delete al;
			al = new TwoBeamAlgorithm();
			break;
		case App::CTL_ID::FOURBEAMBUTTON_ID:
			if (al)
				delete al;
			al = new FourBeamAlgorithm();
			break;
		case App::CTL_ID::ORTOGANALBUTTON_ID:
			if (al)
				delete al;
			al = new OrthogonalRayAlgorithm();
			break;
		case App::CTL_ID::ORTOGANALDBUTTON_ID:
			if (al)
				delete al;
			al = new OrthogonalDiagonalRayAlgorithm();
			break;
		case App::CTL_ID::ASTARBUTTON_ID:
			if (al)
				delete al;
			al = new Astar();
			break;
		case App::CTL_ID::CLEARBUTTON_ID:
			if (!f)
				break;
			disp->clear(*f);
			isCleared = true;
			break;
		case App::CTL_ID::StartButton_ID:
			if (!isCleared || !f || !al)
				break;
			if (!f->canBuild())
				break;
			if (!al->buildPath(f->getList()))
				break;
			al->findPath(f->getList());
			disp->repaintField(*f);
			isCleared = false;
			break;
		default:
			break;
		}
	}
	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
template<typename T>
void App::SafeRelease(T** obj)
{
	(*obj)->Release();
	(*obj) = nullptr;
}
