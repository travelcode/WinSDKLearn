#pragma once
#include "pch.h"
#define DLLEXPORT
#include "ClassDll.h"

int CMath::Add(int a, int b)
{
    return a+b;
}

int CMath::Sub(int a, int b)
{
    return a-b;
}

int CMath::Mul(int a, int b)
{
    return a*b;
}
