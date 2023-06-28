//UNICODE����붨����Դ�ļ���ͷ,windows.h֮��,��ϵͳ�������ֶ�����ú���߿��ֽ�
#define UNICODE
#include <Windows.h>
#include <stdio.h>
//���Ҫ��wprintf֧�ֱ��ػ����������ͷ�ļ�
#include <locale.h>
//����C����ֽ�
void SingleChar() {
	const char* pszText = "hello char";
	size_t len = strlen(pszText);
	printf("char=%s,len=%llu\n",pszText,len);
}
//���Կ��ֽ�
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
//����Wprintf�����ĵ�֧��
void PrintUnicode() {

	wprintf(L"%s\n", L"�������ĺ���,���ڲ���wprintf�Ժ��ֵ�֧�ֶȡ�");
	//Ҫ����wprintf��ȷ�������,������и�����
	setlocale(LC_ALL, "chs");
	wprintf(L"%s\n", L"�������ĺ���,���ڲ���wprintf�Ժ��ֵ�֧�ֶȡ�");
}

//��writeConsole���Wprintf
void PrintByWriteConsole() {
	const wchar_t* text = L"ʹ��WriteConsole������֡�\n";
	//��ȡ����׼������,
	//STD_OUTPUT_HANDLE ��׼������
	//STD_INPUT_HANDLE ��׼������
	//STD_ERROR_HANDLE ��׼������
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(
	   handle,			//��׼������
	   text,			//��Ҫ������ı�
	   (DWORD)wcslen(text),	//׼������ַ��ĳ���
	   NULL,			//ʵ������ַ����ĳ���
	   NULL				//΢��ı�������
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