#pragma once
#include <Windows.h>  
// 测试系统窗口类

int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	//BUTTON是系统窗口类
	HWND hWnd = CreateWindow(TEXT("BUTTON"), TEXT("这是一个按钮"),WS_OVERLAPPEDWINDOW,100,100,500,500,NULL,NULL,hInstance,NULL);

	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	MSG nMsg;

	while (GetMessage(&nMsg,NULL,0,0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
	return 0;
}