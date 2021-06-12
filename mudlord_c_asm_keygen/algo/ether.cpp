#include <windows.h>
void process_serial(char *name, char *serial)
{
	char buffer[71]; //key buffer
	char *buf; //pointer to buffer
	buf = buffer;

	HMODULE hDLL;
	FARPROC reg_code;
	hDLL=LoadLibrary("ether.dll");
	reg_code=GetProcAddress(hDLL,"reg_code");

	__asm
	{
		push buf
		push name
	}
    reg_code();

	//and we clean our buffer when done!
	wsprintf(serial,"%s", buffer);
	memset(buffer,0, 71);
	FreeLibrary(hDLL);

}

