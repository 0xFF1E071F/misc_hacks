#include <windows.h>
char buffer[10];
int index; //global vars are BAD, mmkay?


void copytobuf_help(int val);

unsigned char serial_table[16];

void InitLUT()
/*We init the serial LUT.
  We do this since the main algo alters the table.
  Figured this is easier than using the C routines
  for memory copying/moving, if we use a preallocated
  LUT.....*/
{
    //ripped from crackme the values
	//and did this for size.....instead of the
	//monsterous per byte allocation used.
	_asm
	{
		MOV DWORD PTR DS:[serial_table],0X414B4A53
		MOV DWORD PTR DS:[serial_table+4],0x5456425A
		MOV DWORD PTR DS:[serial_table+8],0x49474345
		MOV DWORD PTR DS:[serial_table+12],0x474E4644
	}
}

void process_serial(char *name, char *serial_out)
{
	int len=lstrlen(name);
	unsigned char serial_formatted[33];
	const char    *hex_table = "0123456789ABCDEF";
	DWORD sum1;

	InitLUT();


	//1st part, fake serial and alterations on LUT......
	__asm
	{
        XOR EBX,EBX
        XOR ECX,ECX
        XOR EDX,EDX
        XOR EDI,EDI
        XOR ESI,ESI
		MOV EDI, name
d2k2_crk_00401147:
        MOV BL,BYTE PTR DS:[ECX+EDI] //get letter
        CMP BL,0X41
        JL d2k2_crk_00401159
d2k2_crk_00401152:
        CMP BL,0X5A
        JG d2k2_crk_00401165
d2k2_crk_00401157:
        JMP d2k2_crk_00401178
d2k2_crk_00401159:
        ADD BL,0X20
        CMP BL,0X41
        JGE d2k2_crk_00401163
        MOV BL,0X46
d2k2_crk_00401163:
        JMP d2k2_crk_00401152
d2k2_crk_00401165:
        SUB BL,0X20
        CMP BL,0X5A
        JLE d2k2_crk_0040116F
        MOV BL,0X47
d2k2_crk_0040116F:
        CMP BL,0X41
        JGE d2k2_crk_00401176
        MOV BL,0X53
d2k2_crk_00401176:
        JMP d2k2_crk_00401157
d2k2_crk_00401178:
        MOV BYTE PTR DS:[EDX+serial_table],BL //alter table
        ADD EDX,2
        INC ECX
        CMP ECX,EAX
        JNZ d2k2_crk_00401147
        XOR ECX,ECX
        XOR EDX,EDX
        XOR EBX,EBX
d2k2_crk_0040118C:
        MOV BL,BYTE PTR DS:[ECX+serial_table] //get component of LUT
        ADD EDX,EBX
        INC ECX
        CMP ECX,0X10
        JNZ d2k2_crk_0040118C
        IMUL EAX,EAX,0XFF
        IMUL EDX,EAX
        XOR EDX,0XACEBDFAB
        BSWAP EDX
		MOV sum1, EDX
	}
	wsprintf(buffer,"%1X",sum1);

    //2nd part, real serial calculation
	//and permutations on LUT.
	//We then use LUT as serial in the end...
	__asm
	{
		XOR EBX,EBX
        XOR ECX,ECX
d2k2_crk_004011C2:
        MOV BL,BYTE PTR DS:[ECX+buffer]
        CMP BL,0X3A
        JL d2k2_crk_004011CF
        JMP d2k2_crk_004011D8
d2k2_crk_004011CF:
        ADD BL,0X11
        MOV BYTE PTR DS:[ECX+buffer],BL
d2k2_crk_004011D8:
        INC ECX
        CMP ECX,8
        JNZ d2k2_crk_004011C2
        XOR EBX,EBX
        XOR ECX,ECX
        XOR EDX,EDX
d2k2_crk_004011E4:
        MOV BL,BYTE PTR DS:[ECX+buffer]
        MOV BYTE PTR DS:[EDX+serial_table+1],BL
        ADD EDX,2
        INC ECX
        CMP EDX,0X10
        JNZ d2k2_crk_004011E4
        XOR EDX,EDX
        XOR EAX,EAX
d2k2_crk_00401201:
		//optimize?
        MOV AL,BYTE PTR DS:[EDX+serial_table+1] //load byte of LUT into AL
        ADD AL,5 //add five to AL register
        MOV BYTE PTR DS:[EDX+serial_table+1],AL //insert byte into LUT
        ADD EDX,2
        CMP EDX,0X10 //have we done the LUT?
        JNZ d2k2_crk_00401201
	}

    //our output serial
	//we use complete LUT with permutations....
	wsprintf(serial_out,"%.16s", serial_table);
}

void copytobuf_help(int val)
{
	buffer[index++] = val;
}

