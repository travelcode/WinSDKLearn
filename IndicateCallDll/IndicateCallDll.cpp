#pragma once
#include <Windows.h>
#include <iostream>
using namespace std;
typedef int(*Add)(int a, int b);
typedef int(*Sub)(int a, int b);
typedef int(*Mul)(int a, int b);

int main() {
	HINSTANCE hInstance = LoadLibrary(TEXT("../x64/Debug/CPPDll.dll"));
	if (hInstance == NULL) {
		cout << "加载DLL失败" << endl;
		return 0;
	}
	cout << "hInstance:" << hInstance << endl;
	//加法
	Add add = (Add)GetProcAddress(hInstance, "DllAdd");
	cout << "addAdress=" << add << endl;
	cout << "add=" << add(4, 5) << endl;
	//减法
	Sub sub = (Sub)GetProcAddress(hInstance, "DllSub");
	cout << "subAdress=" << sub << endl;
	cout << "sub=" <<sub(4, 5) << endl;
	//乘法
	Mul mul = (Mul)GetProcAddress(hInstance, "DllMul");
	cout << "mulAdress=" << mul << endl;
	cout << "mul=" << mul(4, 5) << endl;
	FreeLibrary(hInstance);
	//cout << "add=" << add(4,5) << endl;
	return 0;
}