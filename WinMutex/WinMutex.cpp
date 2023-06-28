#include <Windows.h>
#include <tuple>
#include <iostream>
using namespace std;
HANDLE g_hMute = 0;//»¥³â¾ä±ú  
DWORD WINAPI ThreadProc(LPVOID parameter) {
	char* value = (char*)(parameter);
	while (true)
	{
		WaitForSingleObject(g_hMute, INFINITE);
		for (size_t i = 0; i < strlen(value); i++)
		{
			cout << value[i];
		    Sleep(125);
		}
		cout << endl;
		ReleaseMutex(g_hMute);
	}
	return 0;
}

int main() {
	
	DWORD threadID = 0;
	const char* str1 = "*******************";
	g_hMute = CreateMutex(NULL, FALSE,NULL);
	HANDLE handle1 = CreateThread(NULL, 0, ThreadProc, (LPVOID)str1, 0, &threadID);
	//WaitForSingleObject(handle1, INFINITE);
	const char* str2 = "-------------------";
	HANDLE handle2 = CreateThread(NULL, 0, ThreadProc, (LPVOID)str2, 0, &threadID);
	std::ignore = getchar();
	return 0;
}