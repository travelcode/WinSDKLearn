//UNICODE宏必须定义在源文件开头,windows.h之上,由系统或者是手动定义该宏后走宽字节
#define UNICODE
#include <Windows.h>
#include <stdio.h>
//如果要想wprintf支持本地化必须引入该头文件
#include <locale.h>
//测试C风格单字节
void SingleChar() {
	const char* pszText = "hello char";
	size_t len = strlen(pszText);
	printf("char=%s,len=%llu\n",pszText,len);
}
//测试宽字节
void WideChar() {
	const wchar_t* pszText = L"hello wchar";
	size_t len= wcslen(pszText);
	wprintf(L"wchar=%s,len=%llu\n",pszText,len);
} 

void TypeChar() {
	const TCHAR* text = TEXT("hello tchar");
#ifdef UNICODE
	size_t len = wcslen(text);
	wprintf(L"wchar=%s,len=%llu\n",text,len);
	
#else
	size_t len = strlen(text);
	printf("char=%s,len=%llu\n",text,len);

#endif // UNICODE

}
//测试Wprintf对中文的支持
void PrintUnicode() {

	wprintf(L"%s\n", L"这是中文汉字,用于测试wprintf对汉字的支持度。");
	//要想让wprintf正确输出中文,必须进行该设置
	setlocale(LC_ALL, "chs");
	wprintf(L"%s\n", L"这是中文汉字,用于测试wprintf对汉字的支持度。");
}

//用writeConsole替代Wprintf
void PrintByWriteConsole() {
	const wchar_t* text = L"使用WriteConsole输出文字。\n";
	//获取到标准输出句柄,
	//STD_OUTPUT_HANDLE 标准输出句柄
	//STD_INPUT_HANDLE 标准输入句柄
	//STD_ERROR_HANDLE 标准错误句柄
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(
	   handle,			//标准输出句柄
	   text,			//需要输出的文本
	   (DWORD)wcslen(text),	//准备输出字符的长度
	   NULL,			//实际输出字符串的长度
	   NULL				//微软的保留参数
	);
}
int main() {
	SingleChar();
	WideChar();
	TypeChar();
	PrintByWriteConsole();
	PrintUnicode();

	return 0;
}