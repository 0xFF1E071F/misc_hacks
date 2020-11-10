#include "hookbase.h"
#include "minhook/include/MinHook.h"


uAddr uBase;

extern "C" int crackedbymudlord()
{
	return 0x1988;
}


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

void StartPatch(HMODULE base)
{
	uBase = uAddr(base);
	PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(uBase);
	PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS(uAddr(uBase) + pDsHeader->e_lfanew);
	auto hExecutableInstance = (size_t)GetModuleHandle(NULL);
	IMAGE_NT_HEADERS* ntHeader = (IMAGE_NT_HEADERS*)(hExecutableInstance + ((IMAGE_DOS_HEADER*)hExecutableInstance)->e_lfanew);
	SIZE_T size = ntHeader->OptionalHeader.SizeOfImage;
	DWORD oldProtect;
	VirtualProtect((VOID*)hExecutableInstance, size, PAGE_EXECUTE_READWRITE, &oldProtect);

	dprintf("Let's patch!\n");
	uBase = uAddr(base);

	//Do hooks and patches here
	/*
	MH_Initialize();
	MH_CreateHookApiEx(L"user32.dll", "SetDlgItemTextA", &hooksetwindow, reinterpret_cast<LPVOID*>(&settext), NULL);
	MH_CreateHookApiEx(L"user32.dll", "MessageBoxA", &message, reinterpret_cast<LPVOID*>(&timeout), NULL);
	MH_EnableHook(MH_ALL_HOOKS);
	*/

}