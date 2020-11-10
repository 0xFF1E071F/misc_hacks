
#include "hookbase.h"
#include "victim.h"
#include <cctype>
#include <vector>
#include <string>

using namespace std;

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

void WriteRelativeAddress(uAddr address, uAddr content)
{
	WriteUAddr(address, content - address - 4);
}

uAddr ReadRelativeAddress(uAddr address)
{
	// 00007FFD612A133E | E9 ED 0E 00 00 | jmp 7FFD612A2230
	// 7FFD612A2230 - 00007FFD612A133E - 5 = 0E ED

	return address + 4 + *reinterpret_cast<i32*>(address);
}

void WriteMemBytes(LPVOID lpAddress, LPVOID lpBuffer, DWORD nSize)
{
	DWORD oldprotect;
	VirtualProtect((LPVOID)lpAddress, nSize, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(lpAddress, lpBuffer, nSize);
	VirtualProtect(LPVOID(lpAddress), nSize, oldprotect, &oldprotect);
}

void ReadMem(LPVOID lpAddress, LPVOID lpBuffer, DWORD nSize)
{
	DWORD oldprotect;
	VirtualProtect((LPVOID)lpAddress, nSize, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(lpBuffer, lpAddress, nSize);
	VirtualProtect(LPVOID(lpAddress), nSize, oldprotect, &oldprotect);
}

struct PatternByte
{
	struct PatternNibble
	{
		unsigned char data;
		bool wildcard;
	} nibble[2];
};

static string formathexpattern(string patterntext)
{
	string result;
	int len = patterntext.length();
	for (int i = 0; i < len; i++)
		if (patterntext[i] == '?' || isxdigit(patterntext[i]))
			result += toupper(patterntext[i]);
	return result;
}

static int hexchtoint(char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	else if (ch >= 'A' && ch <= 'F')
		return ch - 'A' + 10;
	else if (ch >= 'a' && ch <= 'f')
		return ch - 'a' + 10;
	return 0;
}

static bool patterntransform(string patterntext, vector<PatternByte>& pattern)
{
	pattern.clear();
	patterntext = formathexpattern(patterntext);
	int len = patterntext.length();
	if (!len)
		return false;

	if (len % 2) //not a multiple of 2
	{
		patterntext += '?';
		len++;
	}

	PatternByte newByte;
	for (int i = 0, j = 0; i < len; i++)
	{
		if (patterntext[i] == '?') //wildcard
		{
			newByte.nibble[j].wildcard = true; //match anything
		}
		else //hex
		{
			newByte.nibble[j].wildcard = false;
			newByte.nibble[j].data = hexchtoint(patterntext[i]) & 0xF;
		}

		j++;
		if (j == 2) //two nibbles = one byte
		{
			j = 0;
			pattern.push_back(newByte);
		}
	}
	return true;
}

static bool patternmatchbyte(unsigned char byte, const PatternByte& pbyte)
{
	int matched = 0;

	unsigned char n1 = (byte >> 4) & 0xF;
	if (pbyte.nibble[0].wildcard)
		matched++;
	else if (pbyte.nibble[0].data == n1)
		matched++;

	unsigned char n2 = byte & 0xF;
	if (pbyte.nibble[1].wildcard)
		matched++;
	else if (pbyte.nibble[1].data == n2)
		matched++;

	return (matched == 2);
}

size_t patternfind(unsigned char* data, size_t datasize, const char* pattern)
{
	vector<PatternByte> searchpattern;
	if (!patterntransform(pattern, searchpattern))
		return -1;
	size_t searchpatternsize = searchpattern.size();
	for (size_t i = 0, pos = 0; i < datasize; i++) //search for the pattern
	{
		if (patternmatchbyte(data[i], searchpattern.at(pos))) //check if our pattern matches the current byte
		{
			pos++;
			if (pos == searchpatternsize) //everything matched
				return i - searchpatternsize + 1;
		}
		else if (pos > 0) //fix by Computer_Angel
		{
			i -= pos;
			pos = 0; //reset current pattern position
		}
	}
	return -1;
}

size_t patternfind(unsigned char* data, size_t datasize, unsigned char* pattern, size_t patternsize)
{
	if (patternsize > datasize)
		patternsize = datasize;
	for (size_t i = 0, pos = 0; i < datasize; i++)
	{
		if (data[i] == pattern[pos])
		{
			pos++;
			if (pos == patternsize)
				return i - patternsize + 1;
		}
		else if (pos > 0)
		{
			i -= pos;
			pos = 0; //reset current pattern position
		}
	}
	return -1;
}

static void patternwritebyte(unsigned char* byte, const PatternByte& pbyte)
{
	unsigned char n1 = (*byte >> 4) & 0xF;
	unsigned char n2 = *byte & 0xF;
	if (!pbyte.nibble[0].wildcard)
		n1 = pbyte.nibble[0].data;
	if (!pbyte.nibble[1].wildcard)
		n2 = pbyte.nibble[1].data;
	*byte = ((n1 << 4) & 0xF0) | (n2 & 0xF);
}

void patternwrite(unsigned char* data, size_t datasize, const char* pattern)
{
	vector<PatternByte> writepattern;
	if (!patterntransform(pattern, writepattern))
		return;
	size_t writepatternsize = writepattern.size();
	if (writepatternsize > datasize)
		writepatternsize = datasize;
	for (size_t i = 0; i < writepatternsize; i++)
		patternwritebyte(&data[i], writepattern.at(i));
}

bool patternsnr(unsigned char* data, size_t datasize, const char* searchpattern, const char* replacepattern)
{
	size_t found = patternfind(data, datasize, searchpattern);
	if (found == -1)
		return false;
	patternwrite(data + found, datasize - found, replacepattern);
	return true;
}

bool patternsnr_mem(unsigned char* data, size_t datasize, const char* searchpattern, const char* replacepattern)
{
	size_t sz = 0;
	uAddr ptr = (uAddr)(data);
	uAddr ptr_end = (uAddr)(data + datasize);
	vector<PatternByte> searchpattern1;
	if (!patterntransform(searchpattern, searchpattern1))
		return -1;
	size_t searchpatternsize = searchpattern1.size();
	vector<PatternByte> writepattern;
	if (!patterntransform(replacepattern, writepattern))
		return false;
	size_t writepatternsize = writepattern.size();
	int found_instances = 0;
	while (ptr < ptr_end)
	{
		int found = patternfind((unsigned char*)ptr, datasize, searchpattern);
		if (found == -1) break;
		{
			DWORD oldprotect;
			ptr += (uAddr)(found);
			unsigned char* ptr1 = (unsigned char*)ptr;
			dprintf("Found registered word at: %llx \n", ptr);
			VirtualProtect((void*)ptr, writepatternsize, PAGE_EXECUTE_READWRITE, &oldprotect);
			for (size_t i = 0; i < writepatternsize; i++)
				patternwritebyte((unsigned char*)&ptr1[i], writepattern.at(i));
			VirtualProtect((void*)ptr, writepatternsize, oldprotect, &oldprotect);
			ptr++;
			datasize -= found + 1;
			found_instances++;
		}
	}
	return true;
}

void OpenConsole()
{
	// Re-enable printf functions.
	FILE* stream;
	if (!AttachConsole(-1))
		AllocConsole();
	freopen_s(&stream, "CONOUT$", "w+", stdout);
#ifdef _DEBUG
	dprintf("Fixing library import..\n");
#endif
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		hInstance = hinstDLL;

		DisableThreadLibraryCalls(hinstDLL);
#if defined(_DEBUG) || defined(__ENABLE_CONSOLE)
		OpenConsole();
#endif
		StartPatch(GetModuleHandle(nullptr));
		break;

	case DLL_PROCESS_DETACH:
		FreeLibrary(hDll);
		break;
	}
	return TRUE;
}


