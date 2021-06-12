#include <windows.h>
#include "loadpe.h"
void process_serial(char *name, char *serial)
{
	char buffer[71]; //key buffer
	char *buf; //pointer to buffer
	buf = buffer;
	memset(buffer,0, 71);
	HMODULE hDLL;
	FARPROC reg_code;
	hDLL=LoadLibrary("ether.dll");
	reg_code=GetProcAddress(hDLL,"reg_code");

	__asm
	{
		push buf
		push name
		call reg_code
		add esp, 0x08
	}

	//and we clean our buffer when done!
	wsprintf(serial,"%s", buffer);
	memset(buffer,0, 71);
	FreeLibrary(hDLL);

}

