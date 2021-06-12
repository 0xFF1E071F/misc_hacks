#include <windows.h>

char buffer[25]; //key buffer
int index; //global vars are BAD, mmkay?

void copytobuf_help(int val); //replaced by ASM code

void process_serial(char *name, char *serial)
{
	char *product = "spycyspycy"; //product ID

	int len=lstrlen(name); //length of name
	int len_product=lstrlen(product); //length of product ID
	unsigned char serial_formatted[33];
	const char    *hex_table = "0123456789ABCDEF";

	__asm
	{
		MOV EBX,1
	    jmp start
loop1:
		MOV EAX,product //get product string
		MOV AL,BYTE PTR DS:[EAX+EBX-1]
		MOV EDX,name //get name
		MOV DL,BYTE PTR DS:[EDX+EBX-1]
		OR AL,DL     //do lame maths!
        MOV EDI,EAX
        AND EDI,0XFF
		MOV EDX,1
        MOV EAX,EDI
		MOV BYTE PTR DS:[EBX+buffer-1],AL  //add to serial buffer
        INC EBX //checks to see if whole name/product has been hashed
start:
		CMP EBX,len_product
		JLE loop1	
	}

	 //convert serial buffer to hex
	 //stolen from my hash calc ;P
	 for(int i = 0, x = 0; i < len_product; i++) {
        serial_formatted[x++] = hex_table[buffer[i] >> 4];
        serial_formatted[x++] = hex_table[buffer[i] & 0xf];
    }
    serial_formatted[x] = 0;

    //our output serial!
	//and we clean our counter and buffer when done!
	wsprintf(serial,"%s", serial_formatted);
	memset(buffer,0, 0xA);
}

void copytobuf_help(int val)
{
	buffer[index++] = val;
}

