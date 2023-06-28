#pragma once
#include <Windows.h>  
//第二步:定义窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd,msgID,wParam,lParam);
}
//第一步:定义入口函数
int APIENTRY WinMain(
	_In_ HINSTANCE hInstance, //应用程序实例句柄,当前应用程序唯一标志
	_In_opt_ HINSTANCE hPrevInstance,//上一个应用程序实例句柄,该参数在16位操作系统下有用,在高版本操作系统中无意义
	_In_ LPSTR lpCmdLine,//应用程序启动时候的命令行参数
	_In_ int nCmdShow//该参数用于控制窗口显示的方式
) {
	//第三步:注册窗口类
	WNDCLASS wc{};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground =(HBRUSH)(COLOR_WINDOW);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
	//第四步:在内存中创建窗口
	HWND hWnd = CreateWindow("Main", "window",WS_OVERLAPPEDWINDOW,100,100,500,500,NULL,NULL,hInstance,NULL);
	//第五步:显示窗口
	ShowWindow(hWnd, nCmdShow);
	//更新窗口,非必须,因为ShowWindow已经更新了窗口
	UpdateWindow(hWnd);
	//第六步:消息循环
	MSG nMsg;
	//获取消息
	while (GetMessage(&nMsg,NULL,0,0))
	{
		//第七步:消息处理(翻译和派发)
		//翻译消息
		TranslateMessage(&nMsg);
		//派发消息,将消息交给窗口处理函数处理消息
		DispatchMessage(&nMsg);

	}
	//注意:目前程序并没有退出
	return 0;
}