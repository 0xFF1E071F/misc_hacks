#include <windows.h>
#include <stdio.h>
#include "miracl.h"
#include "mirdef.h"
#include "sha1.h"
#include "../resource1.h"

#pragma comment(lib, "miracl.lib")
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")

void HexToChar(unsigned char*,int,unsigned char*);

char *N_pub = "CA6D2AFB88915908DE99F99FA12CA895";
char *E_pub = "10001";

void __cdecl HexToChar(unsigned char *pIn,int pLen,unsigned char *pOut)
{
	__asm
	{
		xor eax,eax
			xor edx,edx
			mov esi,pIn
			mov edi,pOut
			mov ecx,pLen
__HexToChar__:
		lodsb
			mov ah,al
			and ah,0x0f
			shr al,4
			add al,0x30
			add ah,0x30
			cmp al,0x39
			jbe a1
			add al,0x41-0x39-0x01
a1:
		cmp ah,0x39
			jbe a2
			add ah,0x41-0x39-0x01
a2:
		stosw
			loop __HexToChar__
			mov al,0
			stosb
	}
}

void substring(char *out, char const *in, size_t len) { 
	memcpy(out, in, len);
	out[len] = '\0';
}

int cust_hash(char* buffer,int len)
{
	DWORD sum = 0;
	for (int i=0;i<len;i++)
	{
		sum += buffer[i];
		sum |= 0xB00B;
		sum += sum + 0xFACE;
		sum >>= 1;
		sum-=sum*0xF;
	}
	return sum;
}

void process_serial(char *name, char *serial_in)
{
	char name_buffer[255]={0};
	char serialbuffer[255]={0};

	char name_hash[255]={0};
	DWORD name_sum = 0;
	unsigned char sha1_hashout[255]={0};
	unsigned char sha1_hash[255]={0};
	char sha1_bytehash[255]={0};
	DWORD sha1_sum = 0;

	big N,E,message, hash_big;

	strcpy(name_buffer,name);
	int name_len=strlen(name);

	miracl *mip = mirsys(100, 0);
	mip->IOBASE=16;
	N=mirvar(0);
	E=mirvar(0);
	hash_big=mirvar(0);
	message=mirvar(0);
	cinstr(N,N_pub);
	cinstr(E,E_pub);

	if (strlen(serial_in) < 32) return;
	if (strlen(name) < 5) return;

	for (int i=0;i<32;i+=8)
	{
		char tempstr[10];
		memset(tempstr,0,10);
		substring(tempstr,serial_in+i,8);
		strcat((char*)serialbuffer,tempstr);
		if (i<24)serial_in++;
	}


	wsprintf(name_hash,"%X",cust_hash(name_buffer,name_len));
	sha1((unsigned char*)name_hash, strlen(name_hash),sha1_hashout);
	HexToChar(sha1_hashout,20,(unsigned char*)sha1_hash);
	wsprintf(sha1_bytehash,"%X",cust_hash((char*)sha1_hash,strlen((char*)sha1_hash)));
	cinstr(message,serialbuffer);
	powmod(message,E,N,message);
	mip->IOBASE=256;
	cotstr(message, (char*)&serialbuffer);

	if (strcmp(serialbuffer,(char*)sha1_bytehash) == 0){
		MessageBox(NULL,"Now make a keygen!","Hazzuh!",MB_ICONINFORMATION);
	}

	mirkill(N);
	mirkill(E);
	mirkill(hash_big);
	mirkill(message);	
}

