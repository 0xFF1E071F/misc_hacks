/*0016C114   /$  C740 1C 01234567  MOV DWORD PTR DS:[EAX+1C],67452301
0016C11B   |.  C740 20 89ABCDEF  MOV DWORD PTR DS:[EAX+20],EFCDAB89
0016C122   |.  C740 24 FEDCBA98  MOV DWORD PTR DS:[EAX+24],98BADCFE
0016C129   |.  C740 28 76543210  MOV DWORD PTR DS:[EAX+28],10325476
0016C130   |.  C740 2C F0E1D2C3  MOV DWORD PTR DS:[EAX+2C],C3D2E1F0
0016C137   |.  33D2              XOR EDX,EDX
0016C139   |.  8950 30           MOV DWORD PTR DS:[EAX+30],EDX
0016C13C   |.  C640 18 00        MOV BYTE PTR DS:[EAX+18],0
0016C140   |.  33D2              XOR EDX,EDX
0016C142   |.  8950 74           MOV DWORD PTR DS:[EAX+74],EDX


0016CF5C=uzregist.0016CF5C (ASCII "$44§ds#hu&c1b76klhh")
EDX=00000020
uzregist.GetRegString+2C*/
#include <windows.h>
#include "MemoryModule.h"
#include "regcode_uzip.h"
#define _SL_STATIC 
#include "..\QuickHash.h"

void process_serial(char *name, char *serial)
{
	char buffer[71]; //key buffer
	char *buf; //pointer to buffer
	buf = buffer;
	char name_buffer[255]={0};
	char *format = "%s";
	strcpy(name_buffer,name);
	FARPROC reg_code;
	HMEMORYMODULE module;
	module = MemoryLoadLibrary(data);
	if (module == NULL)
	{
		wsprintf(serial,"Can't load DLL!");
		return;
	}
	reg_code=MemoryGetProcAddress(module, "GetRegString");
	__asm
	{
		push 0
		push 0
		push name
		call reg_code
		PUSH eax
		PUSH format
		PUSH serial
		CALL DWORD PTR[wsprintf]
		ADD ESP,0x0C
	}
	MemoryFreeLibrary(module);
}

 void toUpperCase (char * word)
 {  
  for (int i = 0; i< strlen (word); ++i)   
  {
	  if ((word[i] >= 'a') && (word[i] <= 'z'))
	  {
		   word [i] = word[i] - 'a' + 'A';
	  }
  }       
 } 

void process_serial2(char *name, char *serial)
{
	char serial_buffer[1024]={0};
	char checksumhex[1024]={0};
	char digesthex[1024]={0};
	char tempbuf[1024]={0};
	SL_CRC32_CalculateStrHex( checksumhex,name, 0 );
	toUpperCase (checksumhex);
	SL_SHA512_CalculateStrHex( digesthex, checksumhex, 0 );
	strcat(tempbuf,checksumhex);
	strcat(tempbuf,digesthex);
	strncat (serial_buffer, tempbuf, 4);
	strcat(serial_buffer, "-");
	strncat(serial_buffer,tempbuf+4,4);
	strcat(serial_buffer, "-");
	strncat(serial_buffer,tempbuf+0x20,4);
	strcat(serial_buffer, "-");
	strncat(serial_buffer,tempbuf+0x5c,4);
	strcat(serial_buffer, "-");
	strncat(serial_buffer,tempbuf+0x7c,4);
	toUpperCase (serial_buffer);
	wsprintf(serial,"%s",serial_buffer);
}