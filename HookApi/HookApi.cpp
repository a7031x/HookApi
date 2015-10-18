// HookApi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "hookapi.hpp"

int
WINAPI
MyMessageBoxA(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType)
{
	lpText = "hooked text";
	return hookapi::call_origin(MessageBoxA)(hWnd, lpText, lpCaption, uType);
}

int main()
{
	hookapi::hook(MessageBoxA, MyMessageBoxA);
	MessageBoxA(nullptr, "text", "caption", MB_OK);
    return 0;
}

