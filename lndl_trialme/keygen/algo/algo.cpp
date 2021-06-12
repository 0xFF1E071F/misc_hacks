#include <windows.h>
#include <stdio.h>
#include "miracl.h"
#include "mirdef.h"
#include "sha1.h"

#pragma comment(lib, "miracl.lib")
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")

void HexToChar(unsigned char*,int,unsigned char*);

//P prime: D671642D9D718D3D
//Q prime: F1A7A20094446E39
//N public: CA6D2AFB88915908DE99F99FA12CA895
//D private: 03488804F26F21198B54E61DF5E7DFE1
//E public: 10001

char *N_pub = "CA6D2AFB88915908DE99F99FA12CA895";
char *D_priv = "03488804F26F21198B54E61DF5E7DFE1";
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

void process_serial(char *name, char *serial_out)
{
	char name_buffer[255]={0};
	char serialbuffer[255]={0};
	char* ser_ptr = serialbuffer;
	
	char destination[64]={0};

	char name_hash[255]={0};
	DWORD name_sum = 0;
	unsigned char sha1_hashout[255]={0};
	unsigned char sha1_hash[255]={0};
	char sha1_bytehash[255]={0};
	DWORD sha1_sum = 0;

	
	big N,D,message, ciphertext;
	
	
	miracl *mip = mirsys(100, 0);
	mip->IOBASE=16;
	N=mirvar(0);
	D=mirvar(0);
	ciphertext=mirvar(0);
	message=mirvar(0);
	
	//name hash
	strcpy(name_buffer,name);
	int name_len=strlen(name);

	//SHA-1 of checksum
	wsprintf(name_hash,"%X",cust_hash(name_buffer,name_len));
	sha1((unsigned char*)name_hash, strlen(name_hash),sha1_hashout);
	HexToChar(sha1_hashout,20,(unsigned char*)sha1_hash);
	wsprintf(sha1_bytehash,"%X",cust_hash((char*)sha1_hash,strlen((char*)sha1_hash)));

	//RSA of SHA-1 hashes
	cinstr(D,D_priv);
	cinstr(N,N_pub);
	bytes_to_big(strlen((const char*)sha1_bytehash),(char*)sha1_bytehash,message);
	powmod(message,D,N,ciphertext);
	
	cotstr(ciphertext, (char*)&serialbuffer);

	for (int i=0;i<32;i+=8)
	{
		char tempstr[10];
		memset(tempstr,0,10);
		substring(tempstr,ser_ptr+i,8);
		strcat((char*)destination,tempstr);
		if (i<24)strcat(destination,"-");
	}

	
	wsprintf(serial_out,"%s",destination);	
	mirkill(N);
	mirkill(D);
	mirkill(message);
}

