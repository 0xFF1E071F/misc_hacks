#pragma once

#include <stdio.h>
#include <assert.h>
#include <Windows.h>
//#include <VersionHelpers.h>

typedef __int8  i8;
typedef __int16 i16;
typedef __int32 i32;
typedef __int64 i64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

#ifdef _WIN64
typedef unsigned __int64 uAddr;
#else
typedef unsigned __int32 uAddr;
#endif
#define uAddr_defined

typedef u8  ubyte;
typedef u16 ushort;
typedef u32 uint;
typedef u64 ulong;

//#define __ENABLE_CONSOLE

#ifdef _DEBUG
#define dprintf(...)   printf(__VA_ARGS__)
#define dwprintf(...) wprintf(__VA_ARGS__)
#else
#ifdef __ENABLE_CONSOLE
#define dprintf(...)   printf(__VA_ARGS__)
#define dwprintf(...) wprintf(__VA_ARGS__)
#else
#define dprintf(...)  do {} while(0)
#define dwprintf(...) do {} while(0)
#endif
#endif

static HINSTANCE hInstance;
static HMODULE hDll;

bool IsBadReadPtr(void* p);
uAddr ReadRelativeAddress(uAddr address);
void WriteRelativeAddress(uAddr address, uAddr content);
void WriteMemBytes(LPVOID lpAddress, LPVOID lpBuffer, DWORD nSize);
void ReadMem(LPVOID lpAddress, LPVOID lpBuffer, DWORD nSize);

//returns: offset to data when found, -1 when not found
size_t patternfind(
	unsigned char* data, //data
	size_t datasize, //size of data
	const char* pattern //pattern to search
);

//returns: offset to data when found, -1 when not found
size_t patternfind(
	unsigned char* data, //data
	size_t datasize, //size of data
	unsigned char* pattern, //bytes to search
	size_t patternsize //size of bytes to search
);

//returns: nothing
void patternwrite(
	unsigned char* data, //data
	size_t datasize, //size of data
	const char* pattern //pattern to write
);

//returns: true on success, false on failure
bool patternsnr(
	unsigned char* data, //data
	size_t datasize, //size of data
	const char* searchpattern, //pattern to search
	const char* replacepattern //pattern to write
);

bool patternsnr_mem(
	unsigned char* data, //data
	size_t datasize, //size of data
	const char* searchpattern, //pattern to search
	const char* replacepattern //pattern to write
);

template<typename T>
void WriteMem(uAddr address, T value)
{
	DWORD oldProtect;
	VirtualProtect(LPVOID(address), sizeof T, PAGE_EXECUTE_READWRITE, &oldProtect);
	*reinterpret_cast<T*>(address) = value;
	VirtualProtect(LPVOID(address), sizeof T, oldProtect, &oldProtect);
}

template<typename T>
void WriteMemRaw(uAddr address, T value)
{
	*reinterpret_cast<T*>(address) = value;
}


#define WriteInt(address, value)  WriteMem(address, int(value))
#define WriteUInt(address, value)  WriteMem(address, uint(value))
#define WriteUAddr(address, value)  WriteMem(address, uAddr(value))

#define WriteShort(address, value)   WriteMem(address, short(value))
#define WriteUShort(address, value)  WriteMem(address, ushort(value))

#define WriteByte(address, value)  WriteMem(address, byte(value))


#define WriteIntRaw(address, value)  WriteMemRaw(address, int(value))
#define WriteUIntRaw(address, value)  WriteMemRaw(address, uint(value))
#define WriteUAddrRaw(address, value)  WriteMemRaw(address, uAddr(value))

#define WriteShortRaw(address, value)   WriteMemRaw(address, short(value))
#define WriteUShortRaw(address, value)  WriteMemRaw(address, ushort(value))

#define WriteByteRaw(address, value)  WriteMemRaw(address, byte(value))
