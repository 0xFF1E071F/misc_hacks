#include <windows.h>




void process_serial(char *name, char *serial_out)
{
	unsigned char serial_buf[] ={0x414B4A53, 0x5456425A, 0x49474345, 0x474E4644};

	unsigned char buffer[32]={0};
	byte bufctr=0;
	byte ctr = 5;

	while(ctr)
	{
		byte ascii_val = (name[bufctr] ^ 0x29) + ctr;
		if(ascii_val < 'A' || ascii_val > 'Z')
			ascii_val = 0x52 + ctr;
        buffer[bufctr]=ascii_val;
		bufctr++;
		ctr--;
	}
	bufctr = 0;
	ctr = 5;

	while(ctr)
	{
		byte ascii_val = (name[bufctr] ^ 0x27) + ctr;
		ascii_val++;
		if(ascii_val < 'A' || ascii_val > 'Z')
			ascii_val = 0x4D + ctr;
		buffer[bufctr+5]=ascii_val;
		bufctr++;
		ctr--;
	}
	ctr = 0;

	while(1)
	{
		byte gen=(buffer[ctr]) + 5;
		if(gen>'Z')gen -=0xD;
		gen^=0xC;
		if(gen<'A')
			gen=0x4B + ctr;
		if(gen>'Z')
			gen=0x4B - ctr;
		buffer[ctr]=gen;
		ctr++;
		if(!buffer[ctr])break;	
	}
	wsprintf(serial_out,"%s", buffer);
}


