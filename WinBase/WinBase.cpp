#pragma once
#include <Windows.h>  
//�ڶ���:���崰�ڴ�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd,msgID,wParam,lParam);
}
//��һ��:������ں���
int APIENTRY WinMain(
	_In_ HINSTANCE hInstance, //Ӧ�ó���ʵ�����,��ǰӦ�ó���Ψһ��־
	_In_opt_ HINSTANCE hPrevInstance,//��һ��Ӧ�ó���ʵ�����,�ò�����16λ����ϵͳ������,�ڸ߰汾����ϵͳ��������
	_In_ LPSTR lpCmdLine,//Ӧ�ó�������ʱ��������в���
	_In_ int nCmdShow//�ò������ڿ��ƴ�����ʾ�ķ�ʽ
) {
	//������:ע�ᴰ����
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
	//���Ĳ�:���ڴ��д�������
	HWND hWnd = CreateWindow("Main", "window",WS_OVERLAPPEDWINDOW,100,100,500,500,NULL,NULL,hInstance,NULL);
	//���岽:��ʾ����
	ShowWindow(hWnd, nCmdShow);
	//���´���,�Ǳ���,��ΪShowWindow�Ѿ������˴���
	UpdateWindow(hWnd);
	//������:��Ϣѭ��
	MSG nMsg;
	//��ȡ��Ϣ
	while (GetMessage(&nMsg,NULL,0,0))
	{
		//���߲�:��Ϣ����(������ɷ�)
		//������Ϣ
		TranslateMessage(&nMsg);
		//�ɷ���Ϣ,����Ϣ�������ڴ�����������Ϣ
		DispatchMessage(&nMsg);

	}
	//ע��:Ŀǰ����û���˳�
	return 0;
}