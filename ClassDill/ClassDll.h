#pragma once
#ifdef DLLEXPORT
#define DLLAPI _declspec(dllexport)
#else
#define DLLAPI _declspec(dllimport)
#endif // DLLEXPORT

class DLLAPI CMath
{
public:
	int Add(int a,int b); 
	int Sub(int a,int b);
	int Mul(int a,int b);
};
