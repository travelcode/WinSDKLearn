// MiniWindow.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "MainWindow.h"


#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
TCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                RegisterWndClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void OnDraw(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam);
void DrawBitMap(const HDC& hdc);
void UseSystemBrush(const HDC& hdc);
void DrawSolidEllipse(const HDC& hdc);
void DrawRedEllipse(const HDC& hdc);
void DrawLine(const HDC& hdc);
void DrawPixel(const HDC& hdc);
void OnDestroy();
int LoopMessage();

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MINIWINDOW, szWindowClass, MAX_LOADSTRING);
	RegisterWndClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	return LoopMessage();
}

//
//  函数: RegisterWndClass()
//
//  目标: 注册窗口类。
//
ATOM RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINIWINDOW));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MINIWINDOW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindow(szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		OnDestroy();
		break;
	case WM_PAINT:
		OnDraw(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void OnDraw(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam)
{
	PAINTSTRUCT ps{};
	HDC hdc = BeginPaint(hWnd, &ps);
	DrawPixel(hdc);
	DrawLine(hdc);
	Rectangle(hdc, 200, 200, 500, 500);
	Ellipse(hdc, 100, 100, 300, 300);
	DrawRedEllipse(hdc);
	DrawSolidEllipse(hdc); 
	UseSystemBrush(hdc);
	DrawBitMap(hdc);
	EndPaint(hWnd, &ps);
}

void DrawBitMap(const HDC& hdc)
{
	HBITMAP hBitMap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP));
	HDC hmemeryDc = CreateCompatibleDC(hdc);
	HGDIOBJ hObj = SelectObject(hmemeryDc, hBitMap);
	BitBlt(hdc, 100, 100, 48, 48, hmemeryDc, 0, 0, SRCCOPY);
	StretchBlt(hdc, 300, 300, 24, 24, hmemeryDc, 0, 0, 48,48,SRCCOPY);
	StretchBlt(hdc, 200, 200, 96, 96, hmemeryDc, 0, 0, 48,48,SRCCOPY);
	hObj = SelectObject(hmemeryDc, hObj);
	DeleteObject(hObj);
	DeleteDC(hmemeryDc);
}

void UseSystemBrush(const HDC& hdc)
{
	HGDIOBJ hObj = GetStockObject(NULL_BRUSH);
	hObj = SelectObject(hdc, hObj);
	Rectangle(hdc, 200, 200, 300, 300);
	SelectObject(hdc, hObj);
}

void DrawSolidEllipse(const HDC& hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(22, 54, 78));
	HGDIOBJ hObj = SelectObject(hdc, hBrush);
	Ellipse(hdc, 150, 150, 400, 400);
	hObj = SelectObject(hdc, hObj);
	DeleteObject(hObj);
}

void DrawRedEllipse(const HDC& hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ hObj = SelectObject(hdc, hPen);
	Ellipse(hdc, 200, 200, 500, 500);
	hObj = SelectObject(hdc, hObj);
	DeleteObject(hObj);
}

void DrawLine(const HDC& hdc)
{
	POINT pt{};
	MoveToEx(hdc, 50, 50, &pt);
	LineTo(hdc, 100, 100);
	LineTo(hdc, 200, 100);
}

void DrawPixel(const HDC& hdc)
{
	for (size_t i = 0; i < 100; i++)
	{
		SetPixel(hdc, (INT)(5 + i), 5, RGB(255, 0, 0));

	}
}

int LoopMessage()
{
	MSG msg;
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE)) {
			if (GetMessage(&msg, NULL, NULL, NULL)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				break;
			}
		}
		//TODO 在此处做闲置处理  
	}
	return (int)msg.wParam;
}

void OnDestroy()
{
	PostQuitMessage(0);
	//TODO  在此处做窗口正在销毁处理。
}
