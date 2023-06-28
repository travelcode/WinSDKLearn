#include <iostream>
#include "../ClassDill/ClassDll.h"
#pragma comment(lib,"../x64/Debug/ClassDill.lib")
using namespace std;
int main() {
	
	CMath cmath;
	cout <<"add:" << cmath.Add(1, 4) << endl;
	cout <<"sub:" << cmath.Sub(1, 4) << endl;
	cout <<"mul:" << cmath.Mul(1, 4) << endl;
	return 0;
}