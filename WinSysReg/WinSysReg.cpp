#pragma once
#include <Windows.h>  
// ����ϵͳ������

int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	//BUTTON��ϵͳ������
	HWND hWnd = CreateWindow(TEXT("BUTTON"), TEXT("����һ����ť"),WS_OVERLAPPEDWINDOW,100,100,500,500,NULL,NULL,hInstance,NULL);

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