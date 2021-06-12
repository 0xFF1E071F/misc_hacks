#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "miracl.lib")
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")

void HexToChar(unsigned char*,int,unsigned char*);


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


TCHAR* trimwhitespace(TCHAR *str_base) {
	TCHAR* buffer = str_base;
	while((buffer = wcschr(str_base, ' '))) {
		lstrcpy(buffer, buffer+1);
	}

	return str_base;
}




void process_serial(TCHAR *name, TCHAR *serial_out)
{
	TCHAR name_buffer[255]={0};
	TCHAR computed_hash[255]={0};


	TCHAR tempbuf1[255]={0};
	TCHAR tempbuf2[255]={0};
	TCHAR tempbuf3[255]={0};
	lstrcpy(name_buffer,wcsupr( trimwhitespace(name) ));
	int position =0;
	int counter=lstrlen(name_buffer);
	
	const TCHAR *label1 = L"cd215label";
	static TCHAR cd215la[64] = {0};
	//append cd215label according to length


	//copy string according to name length
	_asm
	{
            cdlabel_004EFDBB:
		    LEA ECX,cd215la
			PUSH ECX
			CALL wcslen                         ;<= Jump/Call Address Not Resolved
			ADD ESP,0x4
			CMP EAX,counter
			JGE cdlabel_004EFDE8
			PUSH label1                ; UNICODE "label_maker_ver:2.22"
			LEA EDX,cd215la
			PUSH EDX
			CALL wcscat                         ;<= Jump/Call Address Not Resolved
			ADD ESP,0x8
			JMP cdlabel_004EFDBB
cdlabel_004EFDE8:
			MOV EAX,counter
			MOV WORD PTR SS:[EAX*2+cd215la],0x0
			//LEA ECX,DWORD PTR SS:[EBP+<cd215la>]

	}
	CharUpperW(cd215la);


	_asm
	{

		//second portion of serial
		//makes a hash against a name + a table
		   JMP cdlabel_004EFE40
cdlabel_004EFE31:

		    MOV EAX,position ; move position to EAX
			INC EAX                          ; increment eax
			MOV position,EAX ; move incremented num to position
cdlabel_004EFE40:
		    MOV ECX,position ; move position to ecx
			CMP ECX,counter ; compare counter to position
			JGE cdlabel_004EFEF1                 ; jump if counter > position
			MOV EDX,position; move position to EDX
			MOVZX EAX,WORD PTR SS:[EDX*2+name_buffer] ; letter[position] into EAX
			MOV ECX,position ; position in ECX
			MOVZX EDX,WORD PTR SS:[ECX*2+cd215la] ; cd215la[position] into edx
			XOR EAX,EDX                          ; xor cd2la byte with name byte
			MOV BYTE PTR SS:[tempbuf1],AL  ; get lower byte to temp location
			MOVZX EAX,BYTE PTR SS:[tempbuf1] ; move temp var to EAX
			CDQ                                  ; split DWORD in EAX to two WORDs
			MOV ECX,0x1A                         ; 0x1A to ECX
			IDIV ECX                             ; divide EAX by ECX
			MOV DWORD PTR SS:[tempbuf2],EAX ; result into temp
			MOVZX EDX,BYTE PTR SS:[tempbuf1] ; temp into EDX
			MOV EAX,DWORD PTR SS:[tempbuf2]  ; temp2 into EAX
		    IMUL EAX,EAX,0x1A ;  multiply temp2 with 0x1A
			SUB EDX,EAX ; sub temp1 from temp2
			MOV DWORD PTR SS:[tempbuf3],EDX 
			CMP DWORD PTR SS:[tempbuf2],0x0
			JLE cdlabel_004EFECC
			MOV ESI,DWORD PTR SS:[tempbuf2]
			ADD ESI,0x30
			LEA ECX,DWORD PTR SS:[computed_hash]
			PUSH ECX
			CALL wcslen                         ;<= Jump/Call Address Not Resolved
			ADD ESP,0x4
			MOV WORD PTR SS:[EAX*2+computed_hash],SI
cdlabel_004EFECC:
			MOV ESI,DWORD PTR SS:[tempbuf3]
			ADD ESI,0x41
			LEA EDX,DWORD PTR SS:[computed_hash]
			PUSH EDX
			CALL wcslen                         ;<= Jump/Call Address Not Resolved
			ADD ESP,0x4
			MOV WORD PTR SS:[EAX*2+computed_hash],SI
			JMP cdlabel_004EFE31                 ;<= Jump/Call Address Not Resolved
            cdlabel_004EFEF1:
	}
	
	TCHAR tempbuf4[255]={0};
	TCHAR tempbuf5[255]={0};
	TCHAR tempbuf6[255]={0};
	TCHAR bytebuf[255]={0};
	TCHAR* rand_char= bytebuf;
	rand_char+=2;
	position = 0;
	int serial_len;
	//generate first portion of serial
	//uses random chars
	_asm
	{
		    MOV DWORD PTR SS:[tempbuf4],0x0
			MOV WORD PTR SS:[computed_hash+0x24],0x0
		    LEA EAX,DWORD PTR SS:[computed_hash] ; last bit of serial - calculated from name
			PUSH EAX
			CALL wcslen                        
			ADD ESP,0x4                          ; length of computed_hash
			MOV ECX,0x12
			SUB ECX,EAX                          ; sub 0x12 from length of computed_hash
			MOV DWORD PTR SS:[tempbuf4],ECX
			MOV EAX,DWORD PTR SS:[tempbuf4]
		    CDQ
			MOV ECX,0xA
			IDIV ECX
			ADD EAX,0x30
			MOV WORD PTR SS:[bytebuf],AX
			MOV EAX,DWORD PTR SS:[tempbuf4]
			CDQ
			MOV ECX,0xA
			IDIV ECX
			ADD EDX,0x30
			MOV WORD PTR SS:[bytebuf+2],DX
			JMP cdlabel_004EFF6B
            //copy random letters to buffer     
cdlabel_004EFF5C:

			MOV EDX,position
			ADD EDX,0x1
			MOV position,EDX

cdlabel_004EFF6B:
			MOV EAX,position
			CMP EAX,DWORD PTR SS:[tempbuf4]
			JGE cdlabel_004EFFA5
		    CALL rand                           ;<= Jump/Call Address Not Resolved
			CDQ
			MOV ECX,0x1A
			IDIV ECX
			MOV DWORD PTR SS:[tempbuf5],EDX
			MOV EDX,DWORD PTR SS:[tempbuf5]
			ADD EDX,0x41
			MOV EAX,position
			MOV WORD PTR SS:[EAX*2+bytebuf+4],DX
			JMP cdlabel_004EFF5C
cdlabel_004EFFA5:
			LEA ECX,DWORD PTR SS:[computed_hash]
			PUSH ECX
			MOV EDX,position
			LEA EAX,DWORD PTR SS:[EDX*2+bytebuf+4]
			PUSH EAX
			CALL wcscpy                         ;<= Jump/Call Address Not Resolved
			ADD ESP,0x8
			PUSH 0xFF
			PUSH 0x0
			LEA ECX,DWORD PTR SS:[computed_hash]
			PUSH ECX
			CALL memset                         ;<= Jump/Call Address Not Resolved
			ADD ESP,0xC
			MOV position,0x0
			JMP cdlabel_004F0002
cdlabel_004EFFE4:

			MOV EDX,position ; format computed serial into string
			ADD EDX,0x1
			MOV position,EDX
			MOV EAX,DWORD PTR SS:[tempbuf6]
			ADD EAX,0x1
			MOV DWORD PTR SS:[tempbuf6],EAX

cdlabel_004F0002:
			CMP position,0x14
			JGE cdlabel_004F0086
			LEA ECX,DWORD PTR SS:[computed_hash]
			PUSH ECX
			CALL wcslen                         ;<= Jump/Call Address Not Resolved
			ADD ESP,0x4
			MOV EDX,position
			MOV CX,WORD PTR SS:[EDX*2+bytebuf]
			MOV WORD PTR SS:[EAX*2+computed_hash],CX
			CMP position,0x4
			JE cdlabel_004F004B
			CMP position,0x9
			JE cdlabel_004F004B
			CMP position,0xE
			JNZ cdlabel_004F0064
cdlabel_004F004B:

			LEA EDX,DWORD PTR SS:[computed_hash]
			PUSH EDX
			CALL wcslen                         ;<= Jump/Call Address Not Resolved
			ADD ESP,0x4
			MOV WORD PTR SS:[EAX*2+computed_hash],0x2D

cdlabel_004F0064:

			CMP DWORD PTR SS:[tempbuf6],0x4
			JNB cdlabel_004F0081
			MOV EAX,position
			MOVZX ECX,WORD PTR SS:[EAX*2+bytebuf]
			MOV DWORD PTR SS:[tempbuf6],ECX

cdlabel_004F0081:
			JMP cdlabel_004EFFE4
cdlabel_004F0086:

	}
	wsprintf((TCHAR*)serial_out,L"%s",computed_hash);	
}

