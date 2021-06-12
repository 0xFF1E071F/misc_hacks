#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif
	DWORD __stdcall mars_setkey(DWORD,DWORD);
	DWORD __stdcall mars_encrypt(DWORD,DWORD);
#ifdef __cplusplus
}
#endif 

void process_serial(char *name, char *serial_out)
{
	char name_buffer[255]={0};
	strcpy(name_buffer,name);
	char encryption_src[1024]= {0};
	char *encsrc_ptr = encryption_src;
	char mars_output[1024] = {0};
	char *marsout_ptr = mars_output;
	char mars_formatted[1024]= {0};
	char *marsformatted_ptr = mars_formatted;
	char tempbuf[1024]= {0};
	char *tempbuf_ptr = tempbuf;

	char *format1 = "%lX";
	char *format2 = "%d";
	char *encryption_key = "FEABCBFFFF183461";
	
	char shitbuf[1024]= {0};
	char *shitbuf_ptr = shitbuf;
	char skshit[] = "SK2K7";
	char twothoushit[] = "2K7";
	char encryptoshit[] = "ENCRYPTO//tKm";

	int len=strlen(encryption_key);
	__asm
	{
		push len
		PUSH encryption_key
		//set the MARS encryption key
		call mars_setkey 
		push name
		call DWORD PTR[strlen]
		MOV EDX,EAX
		XOR EAX,EAX
		XOR EBX,EBX
		XOR ECX,ECX
		jmp1:
		//do some shit with the name
		//this gets fed into mars_encrypt
			MOV AL,BYTE PTR [EBX+name_buffer] 
			ADD ECX,EAX
			INC EBX
			DEC EDX
		JNE jmp1
		PUSH ECX 
		PUSH format1
		PUSH encsrc_ptr
		CALL DWORD PTR[wsprintf]
		ADD ESP,0x0C
		//do encryption with MARS
		PUSH marsout_ptr
	    PUSH encsrc_ptr
		CALL mars_encrypt
		LEA EAX, mars_output 
		PUSH EAX
		call DWORD PTR[strlen]
		MOV EBX,EAX
		IMUL EBX,EBX,2
		XOR ECX,ECX
        //format MARS output string into something remotely usable
		L0000:
			PUSH DWORD PTR [ECX+mars_output]
			PUSH format2
			LEA EAX,[ECX*2+mars_formatted]
			PUSH EAX
			CALL DWORD PTR[wsprintf]
			ADD ESP,0x0C
			ADD BYTE PTR [tempbuf],4
			MOV ECX,DWORD PTR [tempbuf]
			CMP EBX,ECX
		JNE L0000
		PUSH 1024
		PUSH 0
		LEA EAX, tempbuf 
		PUSH EAX
		CALL DWORD PTR[memset]
		LEA EAX, mars_formatted 
		PUSH EAX
		call DWORD PTR[strlen]
		//do actual serial creation
		//herp derp :3
		MOV CL,BYTE PTR [EAX+mars_formatted-1]
		MOV BYTE PTR [tempbuf],CL
		MOV CL,BYTE PTR [EAX+mars_formatted-2]
		MOV BYTE PTR [tempbuf+1],CL
		MOV CL,BYTE PTR [EAX+mars_formatted-3]
		MOV BYTE PTR [tempbuf+2],CL
		MOV CL,BYTE PTR [EAX+mars_formatted-4]
		MOV BYTE PTR [tempbuf+5],0x2D
		MOV CL,BYTE PTR [EAX+mars_formatted-5]
		MOV BYTE PTR [tempbuf+3],CL
		MOV CL,BYTE PTR [EAX+mars_formatted-6]
		MOV BYTE PTR [tempbuf+4],CL
		

	  MOV AL,BYTE PTR [skshit]
		MOV CL,BYTE PTR [encryptoshit]
		XOR AL,CL
		IMUL AX,WORD PTR [twothoushit]
		ROL EAX,2
		PUSH 0
		PUSH AX
		PUSH format2
		LEA EAX, shitbuf
		PUSH EAX
		CALL DWORD PTR[wsprintf]
		LEA EAX, shitbuf
		PUSH EAX
		LEA EAX, tempbuf
		PUSH EAX
		CALL DWORD PTR[strcat]
	}
	wsprintf(serial_out,"%s",tempbuf);
	
}

