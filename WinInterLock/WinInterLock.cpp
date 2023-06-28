#pragma once
#include <Windows.h>
#include <iostream>
using namespace std;
long g_value = 0;
DWORD WINAPI ThreadProc1(_In_ LPVOID lpParameter) {
	for (size_t i = 0; i < 1000000; i++)
	{
		//g_value++;
		InterlockedIncrement(&g_value);
	}
	return TRUE;
}
DWORD WINAPI ThreadProc2(_In_ LPVOID lpParameter) {
	for (size_t i = 0; i < 1000000; i++)
	{
		//g_value++;
		InterlockedIncrement(&g_value);
	}
	return TRUE;
}
int main() {
	DWORD threadID = 0;
	HANDLE hThread[2];
	hThread[0]= CreateThread(NULL, 0, ThreadProc1, NULL, 0, &threadID);
	hThread[1]= CreateThread(NULL, 0, ThreadProc2, NULL, 0, &threadID);
	WaitForMultipleObjects(sizeof(hThread) / sizeof(HANDLE), hThread, TRUE, INFINITE);
	cout << "g_value=" << g_value << endl;
	return TRUE;
}