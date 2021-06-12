#include <windows.h>

char buffer[10];
int index; //global vars are BAD, mmkay?

void copytobuf_help(int val);

void process_serial(char *name, char *serial_out)
{
	int len=lstrlen(name);
	unsigned char serial_formatted[33];
	const char    *hex_table = "0123456789ABCDEF";

	//1st part, fake serial!
	__asm
	{
	    MOV EBX,name      ; NAME!
        XOR ECX,ECX
        MOV AL,5
        XOR EDX,EDX
d2k2_cra_0040127D:
        MOV CL,BYTE PTR DS:[EDX+EBX]         ; GET LETTER OF NAME
        XOR CL,0X29
        ADD CL,AL
        CMP CL,0X41
        JL d2k2_cra_004012A6
        CMP CL,0X5A
        JG d2k2_cra_004012A6
d2k2_cra_0040128F:
        MOV BYTE PTR DS:[EDX+buffer],CL    ; ADD TO SERIAL BUFFER
        INC DL
        DEC AL
        CMP AL,0
        JE d2k2_cra_004012AC
        JMP d2k2_cra_0040127D
d2k2_cra_004012A6:
        MOV CL,0X52
        ADD CL,AL
        JMP d2k2_cra_0040128F
d2k2_cra_004012AC:
        XOR EDX,EDX
        MOV EAX,5
d2k2_cra_004012B3:
        MOV CL,BYTE PTR DS:[EDX+EBX]
        XOR CL,0X27
        ADD CL,AL
        ADD CL,1
        CMP CL,0X41
        JL d2k2_cra_004012DF
        CMP CL,0X5A
        JG d2k2_cra_004012DF
d2k2_cra_004012C8:
        MOV BYTE PTR DS:[EDX+buffer+5],CL    ; ADD TO SERIAL BUFFER
        INC DL
        DEC AL
        CMP AL,0
        JE d2k2_cra_004012E5
        JMP d2k2_cra_004012B3
d2k2_cra_004012DF:
        MOV CL,0X4D
        ADD CL,AL
        JMP d2k2_cra_004012C8
d2k2_cra_004012E5:
        XOR EAX,EAX
	}

    //2nd part, real serial calculation
	__asm
	{
        XOR EAX,EAX
        XOR EBX,EBX
        XOR ECX,ECX
        XOR EDX,EDX
		//diablo2oo2 might not like this,....
		//Oh well, least the target is keygenned. =]
        mov EAX,offset buffer
d2k2_cra_00401313:
        MOV BL,BYTE PTR DS:[ECX+EAX]
        MOV DL,BYTE PTR DS:[ECX+buffer]    ; serial_buffer
        CMP BL,0
        JE d2k2_cra_004013A6                 ;jmp to end
        ADD DL,5
        CMP DL,0X5A
        JG d2k2_cra_00401341
d2k2_cra_0040132D:
        XOR DL,0XC
        CMP DL,0X41
        JL d2k2_cra_00401346
        CMP DL,0X5A
        JG d2k2_cra_0040134C
d2k2_cra_0040133A:
		MOV BYTE PTR DS:[ECX+buffer],DL ;overwrite contents of buffer with proper serial
        INC ECX
        JMP d2k2_cra_00401313
d2k2_cra_00401341:
        SUB DL,0X0D
        JMP d2k2_cra_0040132D
d2k2_cra_00401346:
        MOV DL,0X4B
        ADD DL,CL
        JMP d2k2_cra_0040133A
d2k2_cra_0040134C:
        MOV DL,0X4B
        SUB DL,CL
        JMP d2k2_cra_0040133A
d2k2_cra_004013A6:
	   //just some shit
	   //might be useful for tagging for lamers.....
	   mov edx, 0XB00BFACE 

end:
	
	}

	 //convert serial buffer to hex
	 //stolen from my hash calc ;P
//	 for(int i = 0, x = 0; i < 10; i++) {
    //    serial_formatted[x++] = hex_table[buffer[i] >> 4];
    //    serial_formatted[x++] = hex_table[buffer[i] & 0xf];
  //  }
   // serial_formatted[x] = 0;

    //our output serial!
	wsprintf(serial_out,"%s", buffer);
	memset(buffer,0, 0xA);
	index = 0;
}

void copytobuf_help(int val)
{
	buffer[index++] = val;


}

