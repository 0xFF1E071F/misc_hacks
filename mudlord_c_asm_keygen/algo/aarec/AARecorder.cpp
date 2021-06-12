#include <windows.h>
#include <time.h>
#include "miracl.h"
#include "mirdef.h"
#include "../resource.h"

#pragma comment (lib, "ms32.lib")
#pragma comment (lib, "libc.lib")
void GetPixelFromBitmap (UINT uiBitmapID, signed long x, signed long y,LPRGBQUAD lpRGBQuad);
char base36enc (int num);

void process_serial(char *name, char *serial)
{
	unsigned char buf1[5],buf2[5],buf3[5],buf4[5];
	int len=lstrlen(name); //length of name
	int x,y;
	srand( (unsigned int) time(NULL));
	//clear the serial buffers
	memset (buf1,0,5);
	memset (buf2,0,5);
	memset (buf3,0,5);
	memset (buf4,0,5);

	/*
	Do initial PRNG seed.

    Then
	1) Randomize X and Y.
	2) Read the pixel values at the location specified at X and Y
	3) Then
	   - X coord is first value encoded in base 36
	   - Y coord is second value encoded in base 36
	   - Red component is third value encoded in base 36
	   - Green component is fourth value encoded in base 36
	   - Blue component is last value encoded in base 36
	4) Rinse and repeat for parts two to four.

    Bottom line: BMP files are used as lookup tables!
	*/
	x = rand()%36;
	y = rand()%36;

	RGBQUAD buf1_col; 
	GetPixelFromBitmap ((unsigned int)MAKEINTRESOURCE(IDB_CODE1), x, y, &buf1_col);
	buf1[0] = base36enc(x);
	buf1[1] = base36enc(y);
	buf1[2] = base36enc(buf1_col.rgbRed);
	buf1[3] = base36enc(buf1_col.rgbGreen);
	buf1[4] = base36enc(buf1_col.rgbBlue);


    x = rand()%36;
	y = rand()%36;
	RGBQUAD buf2_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_CODE2), x, y, &buf2_col);
	buf2[0] = base36enc(x);
	buf2[1] = base36enc(y);
	buf2[2] = base36enc(buf2_col.rgbRed);
	buf2[3] = base36enc(buf2_col.rgbGreen);
	buf2[4] = base36enc(buf2_col.rgbBlue);

    x = rand()%36;
	y = rand()%36;
	RGBQUAD buf3_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_CODE3), x, y, &buf3_col);
	buf3[0] = base36enc(x);
	buf3[1] = base36enc(y);
	buf3[2] = base36enc(buf3_col.rgbRed);
	buf3[3] = base36enc(buf3_col.rgbGreen);
	buf3[4] = base36enc(buf3_col.rgbBlue);

	x = rand()%36;
	y = rand()%36;
	RGBQUAD buf4_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_CODE4), x, y, &buf4_col);
	buf4[0] = base36enc(x);
	buf4[1] = base36enc(y);
	buf4[2] = base36enc(buf4_col.rgbRed);
	buf4[3] = base36enc(buf4_col.rgbGreen);
	buf4[4] = base36enc(buf4_col.rgbBlue);

    //our output serial!
	wsprintf(serial,"%.5s-%.5s-%.5s-%.5s", buf1,buf2,buf3,buf4);
}

char base36enc (int num)
{
	const char    *alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return (alphabet[num]);
}

HBITMAP CreateDIB (LPBITMAPINFO lpBMI, unsigned char** lppBitmapPixels, signed long ulWidth, signed long ulHeight)
{
	HBITMAP hBitmap;
	memset(lpBMI, 0, sizeof (BITMAPINFO));
	lpBMI->bmiHeader.biSize				=sizeof(BITMAPINFOHEADER);
	lpBMI->bmiHeader.biWidth			=ulWidth ;
	lpBMI->bmiHeader.biHeight			=-ulHeight ;
	lpBMI->bmiHeader.biPlanes			=1;
	lpBMI->bmiHeader.biBitCount			=32;  //16 = 16 bits  24 = 24 bits and 32 = 32 bits
	lpBMI->bmiHeader.biCompression		=BI_RGB;
	lpBMI->bmiHeader.biSizeImage		=0;
	lpBMI->bmiHeader.biXPelsPerMeter	=0;
	lpBMI->bmiHeader.biYPelsPerMeter	=0;
	lpBMI->bmiHeader.biClrUsed			=0;
	lpBMI->bmiHeader.biClrImportant		=0;
	hBitmap=CreateDIBSection(NULL,lpBMI,DIB_RGB_COLORS,(void **)lppBitmapPixels,NULL,0); // It needs DC only if you want DIB_PAL_COLORS
	GdiFlush();
	return(hBitmap);
}

void GetPixelFromBitmap (UINT uiBitmapID, signed long x, signed long y, LPRGBQUAD lpRGBQuad)
{
	HBITMAP hBitmap;
	BITMAP sBitmap;
	HDC hDC_1;
	HDC hDC_2;
	HBITMAP hBMP;
	BITMAPINFO bmi;
	LPRGBQUAD lpBitmapPixels;
	LPRGBQUAD lpCurrentPixel;
	hBitmap = LoadBitmap(GetModuleHandle(NULL),MAKEINTRESOURCE(uiBitmapID));
	memset(&sBitmap, 0, sizeof (sBitmap));
	GetObject(hBitmap, sizeof(BITMAP), &sBitmap);
	hDC_1 = CreateCompatibleDC(0);
	SetBkMode(hDC_1,TRANSPARENT);
	hDC_2 = CreateCompatibleDC(0);
	SetBkMode(hDC_2,TRANSPARENT);
	SelectObject(hDC_1, hBitmap);
	hBMP = CreateDIB (&bmi,(unsigned char**)&lpBitmapPixels ,sBitmap.bmWidth, sBitmap.bmHeight);
	SelectObject(hDC_2, hBMP);
	BitBlt(hDC_2,0,0,sBitmap.bmWidth, sBitmap.bmHeight,hDC_1,0,0,SRCCOPY);
	lpCurrentPixel = (LPRGBQUAD)lpBitmapPixels;
	lpCurrentPixel += ((sBitmap.bmWidth * y) + x);
	memcpy(lpRGBQuad,lpCurrentPixel,sizeof(RGBQUAD));
	DeleteObject(hBitmap);
	DeleteObject(hBMP);			
	DeleteDC(hDC_1);
	DeleteDC(hDC_2);
}

