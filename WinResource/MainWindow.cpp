﻿// MiniWindow.cpp : 定义应用程序的入口点。
//
#pragma once
#include "framework.h"
#include "MainWindow.h"
#include "resource.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
TCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                RegisterWndClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
HWND hMainWnd = 0;
VOID OnCommand(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
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
	//此处设置图标  
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINIWINDOW));
	wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU);
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
	hMainWnd = hWnd;
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
	case WM_COMMAND:
		OnCommand(hWnd, message, wParam, lParam);
		break;
	case WM_SETCURSOR:
		if (LOWORD(lParam) == HTCAPTION) {
			HCURSOR hCurSor = LoadCursor(NULL, IDC_ARROW);
			SetCursor(hCurSor);
			return 0;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

VOID OnCommand(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(wParam) == ID_NEW) {
		MessageBox(hwnd, TEXT("点击了新建菜单!"), TEXT("点击新建菜单提示"), MB_OK);
	}
	return VOID();
}

int LoopMessage()
{
    HACCEL hAccel = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATOR));
	MSG msg;
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE)) {
			if (GetMessage(&msg, NULL, NULL, NULL)) {
				if (!TranslateAccelerator(hMainWnd, hAccel, &msg)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
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
