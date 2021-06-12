#ifndef _SCROLLER_H_
#define _SCROLLER_H_

#include "windows.h"

struct SCROLLSTRUCT
{
	//public:
	int ddWidth;
	DWORD ddROP;
	int X;
	int Y;
	HDC hBkgDC;
	LPCTSTR lpstrText;
	HFONT hFont;
	COLORREF ddTxtColor;
	COLORREF ddBkgColor;
	//private:
	HBITMAP hTxtBmp;
	HBITMAP hTmpBmp;
	HBITMAP hBakTmpBmp;
	HDC hInDC;
	int ddHeight;
	int ddPos;
	unsigned int ddTxtWidth;
	BYTE dbStop;
};

extern "C"
{
void __stdcall scrollCreate(SCROLLSTRUCT*);
void __stdcall scrollPaint(SCROLLSTRUCT*);
void __stdcall scrollPause(SCROLLSTRUCT*);
void __stdcall scrollDestroy(SCROLLSTRUCT*);
}

#endif