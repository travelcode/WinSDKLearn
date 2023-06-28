#pragma once
#include <Windows.h>  
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID)
	{
	case WM_DESTROY: //退出应用程序
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}
int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	//第三步:注册窗口类
	WNDCLASS wc{};
	wc.cbClsExtra = 0;							//窗口类附加数据buff大小
	wc.cbWndExtra = 0;							//窗口附加数据buff大小
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);   //绘制窗口背景的画刷句柄
	wc.hCursor = NULL;							//窗口鼠标句柄
	wc.hIcon = NULL;							//窗口图标句柄
	wc.hInstance = hInstance;					//当前模块的实例句柄
	wc.lpfnWndProc = WndProc;					//窗口处理函数	
	wc.lpszClassName = TEXT("Main");			//窗口类的名称
	wc.lpszMenuName = NULL;						//窗口菜单的的资源ID字符串
	wc.style = CS_HREDRAW | CS_VREDRAW;			//窗口类的风格,CS_GLOBALCLASS表示全局窗口类的注册
	RegisterClass(&wc);


	HWND hWnd = CreateWindow(TEXT("Main"), TEXT("window"), WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	MSG nMsg;

	while (GetMessage(&nMsg, NULL, 0, 0))
	{

		TranslateMessage(&nMsg);

		DispatchMessage(&nMsg);

	}

	return 0;
}