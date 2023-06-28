﻿// MiniWindow.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "MainWindow.h"


#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
TCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HANDLE gStdOutput = 0;
// 此代码模块中包含的函数的前向声明:
ATOM                RegisterWndClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void OnMouseBaseAction(CONST HWND&, CONST UINT&, CONST WPARAM&, CONST LPARAM&);
void OnMOuseMove(CONST HWND& hWnd,CONST UINT& message,CONST WPARAM& wParam,CONST LPARAM& lParam);
void OnMouseDoubleClick(CONST HWND& hWnd, CONST UINT& message, CONST WPARAM& wParam, CONST LPARAM& lParam);
void OnMouseWheel(CONST HWND& hWnd, CONST UINT& message, CONST WPARAM& wParam, CONST LPARAM& lParam);
void OnDestroy();
int LoopMessage();

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	AllocConsole();
	gStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
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
	wcex.style = CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;//鼠标双击必须加上CS_DBLCLKS此风格  
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
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		OnMouseBaseAction(hWnd, message, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		//OnMOuseMove(hWnd,message,wParam,lParam);
		break;
	case WM_LBUTTONDBLCLK:
		OnMouseDoubleClick(hWnd, message, wParam, lParam);
		break;
	case WM_MOUSEWHEEL:
		OnMouseWheel(hWnd,message,wParam,lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void OnMouseBaseAction(const HWND& hWnd, const UINT& msgId, const WPARAM& wParam, const LPARAM& lParam)
{

	TCHAR	szText[256] = {'\0'};
	switch (msgId)
	{
	case WM_LBUTTONDOWN:
	wsprintf(szText, TEXT("%s,wparam=%d,x=%d,y=%d\n"), TEXT("鼠标左键按下"),(int) wParam, LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONUP:
	wsprintf(szText, TEXT("%s,wparam=%d,x=%d,y=%d\n"), TEXT("鼠标左键弹起"), (int)wParam,LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_RBUTTONDOWN:
	wsprintf(szText, TEXT("%s,wparam=%d,x=%d,y=%d\n"), TEXT("鼠标右键按下"), (int)wParam, LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_RBUTTONUP:
	wsprintf(szText, TEXT("%s,wparam=%d,x=%d,y=%d\n"), TEXT("鼠标右键弹起"), (int)wParam,LOWORD(lParam), HIWORD(lParam));
		break;
	default:
		break;
	}
	WriteConsole(gStdOutput, szText, lstrlen(szText), NULL, NULL);
}

void OnMOuseMove(const HWND& hWnd, const UINT& message, const WPARAM& wParam, const LPARAM& lParam)
{
	TCHAR	szText[256];
	wsprintf(szText, TEXT("%s,wparam=%d,x=%d,y=%d\n"), TEXT("鼠标移动"),(int)wParam,(int) LOWORD(lParam),(int) HIWORD(lParam));
	WriteConsole(gStdOutput, szText, lstrlen(szText), NULL, NULL);
}

void OnMouseDoubleClick(const HWND& hWnd, const UINT& message, const WPARAM& wParam, const LPARAM& lParam)
{
	TCHAR	szText[256];
	wsprintf(szText, TEXT("%s,wparam=%d,x=%d,y=%d\n"), TEXT("鼠标双击"), (int)wParam, (int)LOWORD(lParam), (int)HIWORD(lParam));
	WriteConsole(gStdOutput, szText, lstrlen(szText), NULL, NULL);
}

void OnMouseWheel(const HWND& hWnd, const UINT& message, const WPARAM& wParam, const LPARAM& lParam)
{
	TCHAR	szText[256];
	wsprintf(szText, TEXT("WM_MOUSEWHEEL,按键码=%d,偏移量=%d,X=%d,Y=%d\n"), LOWORD(wParam), (SHORT)HIWORD(wParam), LOWORD(lParam),HIWORD(lParam));
	WriteConsole(gStdOutput, szText, lstrlen(szText), NULL, NULL);
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
