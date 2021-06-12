#include <windows.h>

void process_serial(char *name, char *serial_out)
{
	unsigned char buffer[32]={0};
	byte bufctr=0;
	byte ctr = 5;

	while(ctr)
	{
		byte val = (name[bufctr] ^ 0x29) + ctr;
		if(val < 0x41 || val > 0x5A)
			val = 0x52 + ctr;
        buffer[bufctr]=val;
		bufctr++;
		ctr--;
	}
	bufctr = 0;
	ctr = 5;

	while(ctr)
	{
		byte val = (name[bufctr] ^ 0x27) + ctr;
		val++;
		if(val < 0x41 || val > 0x5A)
			val = 0x4D + ctr;
		buffer[bufctr+5]=val;
		bufctr++;
		ctr--;
	}
	ctr = 0;

	while(1)
	{
		byte val=(buffer[ctr]) + 5;
		if(val>0x5A)val -=0xD;
		val^=0xC;
		if(val<0x41)
			val=0x4B + ctr;
		if(val>0x5A)
			val=0x4B - ctr;
		buffer[ctr]=val;
		ctr++;
		if(!buffer[ctr])break;	
	}
	wsprintf(serial_out,"%s", buffer);
}


