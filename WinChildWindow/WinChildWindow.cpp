#pragma once
#include <Windows.h>
#include <tchar.h>

LPCTSTR lpClassName = TEXT("MainWindow");
LPCTSTR lpWindowName = TEXT("������");

LPCTSTR lpChildClsName = TEXT("ChildWindow");
LPCTSTR lpChildWinName = TEXT("�Ӵ���");
//���崰�ڴ�������
LRESULT CALLBACK WinProc(HWND hwnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hwnd, msgID, wParam, lParam);
}
//�������
int APIENTRY _tWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow
) {
	//���崰����
	WNDCLASSEX wndClass{};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = lpClassName;
	wndClass.cbClsExtra = 0;
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.hCursor = NULL;
	wndClass.hIcon = NULL;
	wndClass.hIconSm = NULL;
	wndClass.lpfnWndProc = WinProc;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_DBLCLKS | CS_DROPSHADOW | CS_HREDRAW | CS_VREDRAW;
	//ע�ᴰ����
	RegisterClassEx(&wndClass);
	//��������
	HWND  hwnd = CreateWindowEx(0, lpClassName, lpWindowName, WS_OVERLAPPEDWINDOW, 200, 200, 800, 600, NULL, NULL, hInstance, NULL);

	//�����Ӵ���
	WNDCLASSEX childWndClass{};
	childWndClass.cbSize = sizeof(WNDCLASSEX);
	childWndClass.hInstance = hInstance;
	childWndClass.lpszClassName = lpChildClsName;
	childWndClass.cbClsExtra = 0;
	childWndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	childWndClass.hCursor = NULL;
	childWndClass.hIcon = NULL;
	childWndClass.hIconSm = NULL;
	childWndClass.lpfnWndProc = WinProc;
	childWndClass.lpszMenuName = NULL;
	childWndClass.style = CS_DBLCLKS | CS_DROPSHADOW | CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&childWndClass);
	//�����Ӵ���
	HWND  childHwnd = CreateWindowEx(0,
		lpChildClsName,
		lpChildWinName,
		WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE,
		0, 0, 300, 200,
		hwnd,
		NULL,
		hInstance,
		NULL);
	//��ʾ����
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);


	//��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//������Ϣ
		TranslateMessage(&msg);
		//�ַ���Ϣ
		DispatchMessage(&msg);
	}
	return 0;
}