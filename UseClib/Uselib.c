#pragma once
#include <stdio.h>
#include "../Clib/Clib.h"
#pragma comment(lib,"../x64/Debug/Clib.lib")

int main() {
	int ret = libAdd(2,4);
	printf("ret=%d\n",ret);
	ret = libSub(5, 2);
	printf("ret=%d\n",ret);
	return 0;
}