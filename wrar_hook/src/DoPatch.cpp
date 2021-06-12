#include "Common.h"
#include "DllLoader.h"
#include "DoPatch.h"
#include "PatchUtil.h"
#include "minhook/include/MinHook.h"
#include "libudis86/udis86.h"
#include "utf8conv.h"
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi")
using namespace std;
using namespace utf8util;
uAddr uBase;

extern "C" int crackedbymudlord()
{
	return 1988;
}


typedef INT_PTR(WINAPI *DIALOGPARAM)(
	HINSTANCE hInstance,
	LPCWSTR   lpTemplateName,
	HWND      hWndParent,
	DLGPROC   lpDialogFunc,
	LPARAM    dwInitParam
);
DIALOGPARAM dlgrun = NULL;

bool IsBadReadPtr(void* p)
{
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	if (::VirtualQuery(p, &mbi, sizeof(mbi)))
	{
		DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ 
		| PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
		bool b = !(mbi.Protect & mask);
		// check the page is not a guard page
		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;
		return b;
	}
	return true;
}

INT_PTR h_DialogBoxParamW(
	HINSTANCE hInstance,
	LPCWSTR   lpTemplateName,
	HWND      hWndParent,
	DLGPROC   lpDialogFunc,
	LPARAM    dwInitParam
)
{
	if(!IsBadReadPtr((LPVOID)lpTemplateName))
	if(wcscmp(lpTemplateName,L"REMINDER") ==0)return 0;
	return dlgrun(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

typedef HWND(WINAPI *CREATEWINDOW)(
	DWORD     dwExStyle,
	LPCWSTR   lpClassName,
	LPCWSTR   lpWindowName,
	DWORD     dwStyle,
	int       X,
	int       Y,
	int       nWidth,
	int       nHeight,
	HWND      hWndParent,
	HMENU     hMenu,
	HINSTANCE hInstance,
	LPVOID    lpParam
	);
CREATEWINDOW createwnd = NULL;

HWND h_CreateWindowExW(
	DWORD     dwExStyle,
	LPCWSTR   lpClassName,
	LPCWSTR   lpWindowName,
	DWORD     dwStyle,
	int       X,
	int       Y,
	int       nWidth,
	int       nHeight,
	HWND      hWndParent,
	HMENU     hMenu,
	HINSTANCE hInstance,
	LPVOID    lpParam
)
{
	if (!IsBadReadPtr((LPVOID)lpClassName))
	if (wcscmp(lpClassName, L"RarReminder") == 0)return 0;
	return createwnd(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>


void DLL_patch(HMODULE base) {
	uBase = uAddr(base);
	PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(uBase);
	PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS(uAddr(uBase) + pDsHeader->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;
	SIZE_T size1 = pOptionalHeader->SizeOfCode;
	
	dprintf("Let's patch!\n");
	wchar_t szExePath[MAX_PATH];
	GetModuleFileName(nullptr, szExePath, MAX_PATH);
	dwprintf(L"szExePath: %s\n", szExePath);
	if (0 != wcscmp(wcsrchr(szExePath, L'\\'), L"\\WinRAR.exe")) {
		// Not my_target
		//dwprintf(L"Is not my target: %s\n", wcsrchr(szExePath, L'\\') + 1);
	//	return;
	}
	uBase = uAddr(base);

	if (MH_Initialize() != MH_OK)
	{
		dprintf("Failed to initialize hooking library!\n");
		return;
	}
	if (MH_CreateHookApiEx(L"user32.dll", "DialogBoxParamW", &h_DialogBoxParamW, reinterpret_cast<LPVOID*>(&dlgrun), NULL) != MH_OK)
	{
		dprintf("Failed to hook dialog!\n");
		return;
	}

	if (MH_CreateHookApiEx(L"user32.dll", "CreateWindowExW", &h_CreateWindowExW, reinterpret_cast<LPVOID*>(&createwnd), NULL) != MH_OK)
	{
		dprintf("Failed to hook Internet functions!\n");
	return;
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
	{
		dprintf("Failed to hook!\n");
		return;
	}
}