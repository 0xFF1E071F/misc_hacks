#include <windows.h>

void process_serial(char *name, char *serial_out, int selection)
{
	char name_buffer[255]={0};
	strcpy(name_buffer,name);
	int name_len=strlen(name);
	
	char serialbuffer[255]={0};

	char serialtable[255]={0};
	strcpy(serialtable,"ACDEFGHJKLMNPRSTUWXY34679");
	int serialtablelen = strlen(serialtable);
	char notabene[255]={0};
	char* appname = "VitalSparks";
	
	//strcpy(notabene,"notabene");
	strcpy(notabene,"picospell");
	
	strncat(notabene,appname,4);
	int notabene_len = 12;
	
	

	DWORD name_sum;
	DWORD notabene_sum;
	DWORD keypos;
	DWORD letterbuf;
	DWORD notabenebuf;


	_asm
	{
		XOR EAX,EAX
		XOR EBX,EBX
		MOV name_sum, EAX
jmp1:
		//name sum
		MOVSX EAX,BYTE PTR [EBX+name_buffer] 
		ADD name_sum,EAX
		INC EBX
		CMP EBX,name_len
		JNE jmp1
		XOR EAX,EAX
		XOR EBX,EBX
		MOV notabene_sum, EAX
jmp2:
		//appsum sum
		MOVSX EAX,BYTE PTR [EBX+notabene] 
		ADD notabene_sum,EAX
		INC EBX
		CMP EBX,notabene_len
		JNE jmp2

		XOR EAX,EAX
		XOR EBX,EBX
		XOR ECX,ECX
		MOV keypos,EAX
		JMP License_00402360

		License_004022DB:
		MOV ECX,keypos                  ; load notabene buffer position
		MOVSX EAX,BYTE PTR SS:[ECX+notabene] ; get letter from notabene buffer
		MOV notabenebuf,EAX                   ; put letter into notabene buffer
		MOV EAX,keypos                  ; get pos
		MOV EDX,name_len
		MOV ECX,EDX
		XOR EDX,EDX
		DIV ECX
		MOV EAX,name                    ; load name from buffer
		MOVSX EAX,BYTE PTR DS:[EAX+EDX]      ; get letter from name
		MOV letterbuf,EAX                   ; put letter into letter buffer
		MOV EBX,notabene_len
		MOV EAX,notabenebuf
		MOV EDX,notabene_sum
		ADD EAX,EDX
		IMUL EBX,EAX
		MOV EAX,name_len
		MOV ECX,letterbuf
		MOV EDX,name_sum
		ADD ECX,EDX
		IMUL ECX
		ADD EBX,EAX
		MOV EAX,serialtablelen
		XCHG EAX,EBX
		XOR EDX,EDX
		DIV EBX
		MOV AL,BYTE PTR SS:[EDX+serialtable]    ; get element from serial table and append to genned serial
		MOV EDX, keypos
		MOV BYTE PTR [EDX+serialbuffer],AL
		INC keypos
		License_00402360:
		MOV EDX,keypos
		CMP notabene_len,EDX                          ; compare EDX result of notabene buffer strlen
		JA License_004022DB
	}
	wsprintf(serial_out,"%s",serialbuffer);	
}

