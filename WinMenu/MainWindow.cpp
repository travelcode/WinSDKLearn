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
void OnCommand(HWND hWnd, WPARAM);
void OnDestroy();
void OnRightButtonUp(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
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
	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	//加载菜单方式一
	//wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU);
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

	//加载菜单方式二
	//HMENU hMenu= LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU));
	HWND hWnd = CreateWindow(szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		NULL,
		//hMenu,
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
	case WM_CREATE:
		//加载菜单方式三
		SetMenu(hWnd, LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU)));
		break;
	case WM_DESTROY:
		OnDestroy();
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_RBUTTONUP:
		//弹出上下文菜单,但是坐标系是客户区坐标,需要转换为屏幕系坐标,故一般不使用   
		//OnRightButtonUp(hWnd,message,wParam,lParam);
		break;
	case WM_CONTEXTMENU:
		OnRightButtonUp(hWnd, message, wParam, lParam);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_NEW:
		MessageBox(hWnd, TEXT("新建按钮被点击"),TEXT("菜单提示"),MB_OK);
		break;
	case ID_EXIT:
		MessageBox(hWnd, TEXT("退出按钮被点击"),TEXT("菜单提示"),MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hWnd, TEXT("关于按钮被点击"),TEXT("菜单提示"),MB_OK);
		break;
	default:
		break;
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

void OnRightButtonUp(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU));
	hMenu= GetSubMenu(hMenu,0);
	TrackPopupMenu(hMenu, TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
}
