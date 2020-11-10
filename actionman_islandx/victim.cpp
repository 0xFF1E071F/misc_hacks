#include "hookbase.h"
#include "minhook/include/MinHook.h"
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi")

/* 
Action Man: Raid on Island X
--------------------------------------------------------
SHA-1 of image: EC0D22B6AE8793800ACA21DD5AC0273ACB4E5511
Set executable in Windows 98/Me compatibility mode always before
and when you run the game*/


uAddr uBase;

typedef DWORD(WINAPI* GetLogicalDriveString)(
	DWORD nBufferLength,
	LPSTR lpBuffer
	);

typedef UINT(WINAPI* GetDriveTypeDr)(LPCSTR lpRootPathName);

UINT WINAPI drivetype(LPCSTR lpRootPathName)
{
	return 0x05;
}

typedef BOOL(WINAPI* GetVolumeInformation2)(
	LPCSTR  lpRootPathName,
	LPSTR   lpVolumeNameBuffer,
	DWORD   nVolumeNameSize,
	LPDWORD lpVolumeSerialNumber,
	LPDWORD lpMaximumComponentLength,
	LPDWORD lpFileSystemFlags,
	LPSTR   lpFileSystemNameBuffer,
	DWORD   nFileSystemNameSize
	);

char maxpath[MAX_PATH] = { 0 };

BOOL WINAPI volumeinfo(
	LPCSTR  lpRootPathName,
	LPSTR   lpVolumeNameBuffer,
	DWORD   nVolumeNameSize,
	LPDWORD lpVolumeSerialNumber,
	LPDWORD lpMaximumComponentLength,
	LPDWORD lpFileSystemFlags,
	LPSTR   lpFileSystemNameBuffer,
	DWORD   nFileSystemNameSize)
{
	lstrcpyA(lpVolumeNameBuffer, "ISLANDX");
	nVolumeNameSize = strlen("ISLANDX");
	lpRootPathName = maxpath;
	return TRUE;
}

DWORD WINAPI logicalstr(DWORD nBufferLength, LPSTR lpBuffer)
{
	strcpy(lpBuffer, maxpath);
	nBufferLength = lstrlenA(maxpath);
	return nBufferLength;
}

void StartPatch(HMODULE base)
{
	uBase = uAddr(base);
	PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(uBase);
	PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS(uAddr(uBase) + pDsHeader->e_lfanew);
	HMODULE hExecutableInstance = (HMODULE)GetModuleHandle(NULL);
	IMAGE_NT_HEADERS* ntHeader = (IMAGE_NT_HEADERS*)(hExecutableInstance + ((IMAGE_DOS_HEADER*)hExecutableInstance)->e_lfanew);
	SIZE_T size = ntHeader->OptionalHeader.SizeOfImage;
	DWORD oldProtect;
	VirtualProtect((VOID*)hExecutableInstance, size, PAGE_EXECUTE_READWRITE, &oldProtect);

	dprintf("Let's patch!\n");
	uBase = uAddr(base);

	GetCurrentDirectoryA(MAX_PATH, maxpath);
	MH_Initialize();
	MH_CreateHookApiEx(L"kernel32.dll", "GetLogicalDriveStringsA", &logicalstr, NULL, NULL);
	MH_CreateHookApiEx(L"kernel32.dll", "GetDriveTypeA", &drivetype, NULL, NULL);
	MH_CreateHookApiEx(L"kernel32.dll", "GetVolumeInformationA", &volumeinfo, NULL, NULL);
	MH_EnableHook(MH_ALL_HOOKS);
}