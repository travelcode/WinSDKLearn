#pragma once

#include <Windows.h>  
#include <tchar.h>

HANDLE gStadOutPut = 0;//接收标准输出句柄
LPCTSTR lpMainWinClsName = TEXT("Main");
LPCTSTR lpMainWinTitle = TEXT("测试窗口消息");
VOID OnCreate(UINT msgID) {
	if (msgID == WM_CREATE) {
		MessageBox(NULL, TEXT("正在创建窗口"), TEXT("创建窗口标题"), NULL);
	}
}
VOID OnExit(UINT msgID) {
	if (msgID == WM_DESTROY) {
		PostQuitMessage(WM_QUIT);
	}
}
VOID OnSysCommand(UINT msgID, WPARAM wParam, LPARAM lParam) {
	if (msgID != WM_SYSCOMMAND) {
		return;
	}
	switch (wParam)
	{
	case SC_CLOSE:
		MessageBox(NULL, TEXT("正在关闭窗口"), TEXT("关闭提示"), MB_OK);
		break;
	default:
		break;
	}
}
VOID OnReSize(UINT msgID, WPARAM wParam, LPARAM lParam) {
	if (msgID != WM_SIZE) {
		return;
	}
	short width = LOWORD(lParam);
	short height = HIWORD(lParam);
	TCHAR szText[256];
	wsprintf(szText, TEXT("WM_SIZE=>width:%d height:%d"), width, height);
	WriteConsole(gStadOutPut, szText, lstrlen(szText), NULL, NULL);

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {

	OnCreate(msgID);
	OnReSize(msgID, wParam, lParam);
	OnSysCommand(msgID, wParam, lParam);
	OnExit(msgID);
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}
VOID RegisterWndClass(HINSTANCE hInstance) {
	WNDCLASS wc{};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = lpMainWinClsName;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
}
HWND CreateAndShowWindow(HINSTANCE hInstance, int nCmdShow) {
	HWND hWnd = CreateWindow(lpMainWinClsName, lpMainWinTitle, WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return hWnd;
}
VOID Loop() {
	MSG nMsg;
	// 阻塞模式
	//while (GetMessage(&nMsg, NULL, 0, 0))
	//{
	//	TranslateMessage(&nMsg);
	//	DispatchMessage(&nMsg);
	//}
	while (1) {
		if (PeekMessage(&nMsg, NULL, 0, 0, PM_NOREMOVE)) {
			if (GetMessage(&nMsg, NULL, 0, 0)) {
				TranslateMessage(&nMsg);
				DispatchMessage(&nMsg);
			}
			else {
				return;
			}
		}
		else {
			//无消息,进行空闲处理
			const TCHAR* msg = TEXT("OnIdle\n");
			WriteConsole(gStadOutPut, msg, lstrlen(msg), NULL, NULL);
		}
	}
}
int APIENTRY _tWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow
) {
	AllocConsole();//增加dos窗口
	gStadOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
	RegisterWndClass(hInstance);
	CreateAndShowWindow(hInstance, nCmdShow);
	Loop();
	return 0;
}