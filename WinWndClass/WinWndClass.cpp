#pragma once
#include <Windows.h>  
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID)
	{
	case WM_DESTROY: //�˳�Ӧ�ó���
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
	//������:ע�ᴰ����
	WNDCLASS wc{};
	wc.cbClsExtra = 0;							//�����฽������buff��С
	wc.cbWndExtra = 0;							//���ڸ�������buff��С
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);   //���ƴ��ڱ����Ļ�ˢ���
	wc.hCursor = NULL;							//���������
	wc.hIcon = NULL;							//����ͼ����
	wc.hInstance = hInstance;					//��ǰģ���ʵ�����
	wc.lpfnWndProc = WndProc;					//���ڴ�����	
	wc.lpszClassName = TEXT("Main");			//�����������
	wc.lpszMenuName = NULL;						//���ڲ˵��ĵ���ԴID�ַ���
	wc.style = CS_HREDRAW | CS_VREDRAW;			//������ķ��,CS_GLOBALCLASS��ʾȫ�ִ������ע��
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