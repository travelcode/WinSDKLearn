#pragma once
#include <iostream>
#include "../CPPDll/CppDll.h"
//通知编译器到哪里去抓编号和dll文件名  
#pragma comment(lib,"../x64/Debug/CppDll.lib")

using namespace std;
int main() {
	int sum = DllAdd(10,2);
	cout << "sum=" << sum << endl;
	int sub = DllSub(10,2);
	cout << "sub=" << sub << endl;
	int mul = DllMul(10,2);
	cout << "mul=" << mul << endl;
	return 0;
}