#include <windows.h>
#include "MemoryModule.h"
#include "ether.h"
#include "..\resource1.h"

struct
{
	unsigned char *blob;
	DWORD size;
} prottable[18] = {
	{dvdcreator,sizeof(dvdcreator) },
	{videotodvd,sizeof(videotodvd)},
	{divxtodvd,sizeof(divxtodvd)},
	{wmvtodvd,sizeof(wmvtodvd)},
	{rmtodvd,sizeof(rmtodvd)},
	{mpegtodvd,sizeof(mpegtodvd)},
	{cddvdcopy,sizeof(cddvdcopy)},
	{cdburner,sizeof(cdburner)},
	{audiocdburner,sizeof(audiocdburner)},
	{mp3cdburner,sizeof(mp3cdburner)},
	{myvideoconv,sizeof(myvideoconv)},
	{easymovconv,sizeof(easymovconv)},
	{easyaviconv,sizeof(easyaviconv)},
	{easyvidtoipodconv,sizeof(easyvidtoipodconv)},
	{easyvidtopspconv,sizeof(easyvidtopspconv)},
	{easyvidto3gpconv,sizeof(easyvidto3gpconv)},
	{easyvidtomp4conv,sizeof(easyvidtomp4conv)},
	{easypodmp4psp3gpconv,sizeof(easypodmp4psp3gpconv)}
};

void process_serial(char *name, HWND hwnd, int prod)
{
	char buffer[255]; //key buffer
	char serial[255]; //key buffer
	char *buf; //pointer to buffer
	buf = buffer;
	memset(serial,0,255);
	memset(buffer,0,255);
	FARPROC reg_code;
	HMEMORYMODULE module = NULL;
	
	module = MemoryLoadLibrary(ether);
	reg_code=MemoryGetProcAddress(module, "reg_code");
	DWORD oldprot;
	VirtualProtect((void*)0x10005020,565,PAGE_READWRITE,&oldprot);
	memcpy((void*)0x10005020,prottable[prod].blob,prottable[prod].size);
	__asm
	{
		push buf
		push name
		call reg_code
		add esp, 0x08
	}
	wsprintf(serial,"%s", buffer);
	MemoryFreeLibrary(module);
	SetDlgItemText(hwnd, IDC_SERIAL,serial);
}

