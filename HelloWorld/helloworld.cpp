#include <windows.h>

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hprevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
  	return MessageBox(NULL,TEXT("你好,世界。"),TEXT("消息框"),MB_OK);
}
