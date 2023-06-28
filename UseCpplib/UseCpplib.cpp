#pragma once
#include <iostream>
#include <stdio.h>
#include "../CppLib/CppLib.h"
#include "../Clib/Clib.h"
#pragma comment(lib,"../x64/Debug/CppLib.lib")
#pragma comment(lib,"../x64/Debug/Clib.lib")
using namespace std;
int main() {
	cout<<"ADD=" << CppAdd(5, 9) << endl;
	cout<<"SUB=" << CppSub(5, 9) << endl;
	cout<<"CADD=" << libAdd(5, 9) << endl;
	cout<<"CSUB=" << libAdd(5, 9) << endl;
	
	return 0;
}