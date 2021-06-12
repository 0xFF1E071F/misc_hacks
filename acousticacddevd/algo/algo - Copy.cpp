#include <windows.h>
#include <stdio.h>
#include "miracl.h"
#include "mirdef.h"
#include "md5.h"

#pragma comment(lib, "miracl.lib")
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")

void HexToChar(unsigned char*,int,unsigned char*);

/*
p = 4341515750913091969199358593716523
q = 3953900233164736959029259785415179
n= 17165920139823652402150828830687873417781581972343825315508187302617
d= 8041687598346976151652268897871108457617354876747430769819962623609
E = 65537

*/

char *N_pub = "A3000A54309B6ADCD781692370CB456CD2B60056BEC581CDF89C0AD9";
char *D_priv ="4C5C427A7A62F4C70CB67578C2E7D7BD92EC6177A3992EE5B920C679";
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



void process_serial(char *name, char *serial_out)
{
	char name_buffer[255]={0};
	char serialbuffer[255]={0};
	char original[255]={0};
	char md5_out[16]={0};
	char md5_string[60]={0};

	big N,D,E,message, ciphertext;
	
	miracl *mip = mirsys(50, 0);
	mip->IOBASE=16;
	N=mirvar(0);
	D=mirvar(0);
	E=mirvar(0);

	ciphertext=mirvar(0);
	message=mirvar(0);
	//public/private keys
	cinstr(D,D_priv);
	cinstr(N,N_pub);
	cinstr(E,E_pub);
	//name hash
	strcpy(name_buffer,name);
	int name_len=strlen(name);
	 md5((unsigned char*)name_buffer,name_len, (unsigned char*)md5_out );
	 HexToChar((unsigned char*)md5_out,0x10,(unsigned char*)md5_string);

	//RSA of SHA-1 hashes
	cinstr(message,md5_string);
	mip->IOBASE=16;
	//bytes_to_big(0x10,md5_out,message);
	powmod(message,D,N,ciphertext);
	cotstr(ciphertext, (char*)&serialbuffer);
	//0xFF - BF + 2 = 42 - business license
	//C is a personal license
	strcat(serialbuffer,"0B");

	


	/*
	powmod(ciphertext,E,N,ciphertext);

	mip->IOBASE=16;
	cotstr(ciphertext, (char*)&original);
	*/

	
	wsprintf(serial_out,"%s",serialbuffer);	
	mirkill(E);
	mirkill(N);
	mirkill(D);
	mirkill(message);
}

