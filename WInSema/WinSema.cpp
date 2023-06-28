#pragma once
#include <Windows.h>
#include <iostream>
#include <tuple>
using namespace std;
HANDLE g_sema = 0;
DWORD WINAPI ThreadProc(LPVOID parameter) {
	while (true)
	{
		WaitForSingleObject(g_sema, INFINITE);
		Sleep(1000);
		cout << "********************" << endl;

	}
}
int main() {
	DWORD threadID = 0;
	g_sema = CreateSemaphore(NULL, 4, 10, NULL);
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, NULL, &threadID);
	if (hThread) {
	g_sema = CreateSemaphore(NULL, 7, 10, NULL);
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
	}
	return 0;
}