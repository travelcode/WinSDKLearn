#pragma once
#include <Windows.h>
#include <iostream>
#include <tuple>
using namespace std;

DWORD WINAPI ThreadProc(LPVOID parameter) {
	char* value = (char*)(parameter);
	while (true)
	{
		cout << value;
		Sleep(1000);
	}
	return 0;
}

int main() {
	DWORD threadID = 0;
	const char* str1 = "*******************\n\0";
	HANDLE handle1 = CreateThread(NULL, 0, ThreadProc, (LPVOID)str1, 0, &threadID);
	//WaitForSingleObject(handle1, INFINITE);
	const char* str2 = "-------------------\n\0";
	HANDLE handle2 = CreateThread(NULL, 0, ThreadProc, (LPVOID)str2, CREATE_SUSPENDED, &threadID);
	std::ignore = getchar();
	if (handle1) {
		SuspendThread(handle1);
	}
	if (handle2) {
		ResumeThread(handle2);
	}
	std::ignore = getchar();
	return 0;
}