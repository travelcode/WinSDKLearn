#pragma once
#include <Windows.h>
#include <tuple>
#include <iostream>
using namespace std;
HANDLE g_Event;
DWORD WINAPI ThreadPrintProc(LPVOID parameter) {
	while (true)
	{
		WaitForSingleObject(g_Event, INFINITE);
		cout << "*************" << endl;
		//ResetEvent(g_Event);
	}
	return TRUE;
}
DWORD WINAPI ThreadCtrlProc(LPVOID parameter) {
	while (true)
	{
		Sleep(1000);
		SetEvent(g_Event);
	}
}
int main() {
	DWORD nThreadID;
	HANDLE hThreads[2];
	g_Event = CreateEvent(NULL, FALSE, FALSE, NULL);
	hThreads[0] = CreateThread(NULL, 0, ThreadPrintProc, NULL, 0, &nThreadID);
	hThreads[1] = CreateThread(NULL, 0, ThreadCtrlProc, NULL, 0, &nThreadID);
	ignore = getchar();
	return 0;
}