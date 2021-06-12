#include <windows.h>
#include <stdio.h>
#include "patch.h"
#include "resource.h"
#include "croc.h"
#include "ufmod.h"
#include "scroller.h"

#pragma comment (lib, "scroller.lib")

char strTextTest[] = "Hello and welcome to the WOME all products patch by mudlord! Enjoy this release! Greets to Team RES, Team SND, Team CiM, and others I forgot.....Fuckings to: all lamers, all ripperz like WRATH, CU and co, all noobs in general....";
SCROLLSTRUCT scrTest = {310,SRCPAINT,0,55,0,strTextTest,0,0xFFFFFF,0};
static BOOL CALLBACK DialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
void process_serial(char *name, char *serial);


static BOOL CALLBACK DialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static BOOL getopenname(HWND hwndDlg,char []);
void patch(HWND hwndDlg,char [], int);

char *patch_name = "W.O.M.E All Products Patch";

char *about =
"wordofmouthexperiment.com All Products Patch\n"
"Version 1.0\n"
"coded by mudlord";

int apps_count = 3;
const char *appname[] = { 
"IQ Trainer", 
"Subliminal Flash 2.1", 
"Subliminal Images" ,
};


const char *app_filename[] = { 
"IQTrainer.exe", 
"SubliminalFlash.exe", 
"SubliminalImages.exe", 
};

int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	memset(&wc,0,sizeof(wc));
	wc.lpfnWndProc = DefDlgProc;
	wc.cbWndExtra = DLGWINDOWEXTRA;
	wc.hInstance = hinst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	wc.lpszClassName = "patch";
	RegisterClass(&wc);
	return DialogBox(hinst, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, (DLGPROC) DialogFunc);

}


DWORD WINAPI thProc(LPVOID lpParameter)
{
	//DWORD l = 0;
	Sleep(1000);
	LOGFONT LogFont;
	LogFont.lfStrikeOut = 0;
    LogFont.lfUnderline = 0;
    LogFont.lfHeight = 14;
    LogFont.lfEscapement = 0;
	LogFont.lfPitchAndFamily = FF_SWISS;

	HDC hDlgDC = GetDC((HWND)lpParameter);
	scrTest.hBkgDC = hDlgDC;
	HFONT hFnt = CreateFontIndirect(&LogFont);
	scrTest.hFont = hFnt;
	scrollCreate(&scrTest);

	while (true)
	{
		scrollPaint(&scrTest);
		Sleep(20);
	}
	return 0;
}


static BOOL CALLBACK DialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	char file1[60]="Journal.exe";
	int file_selector;
	
	
	switch (msg) {
	case WM_INITDIALOG:
	HWND scrollbox;
	int combobox_count;
	SetWindowText(hwndDlg, patch_name);
	DWORD tmp;
	CreateThread(0,0,thProc,hwndDlg,0,&tmp);

	uFMOD_PlaySong(croc,(void*)croc_size,XM_MEMORY);
	SetDlgItemText(hwndDlg,ID_TEXT,"Select a app and then click 'Patch!'!");
	scrollbox = GetDlgItem(hwndDlg, IDC_COMBOBOX);
	for (combobox_count = 0; combobox_count < apps_count; combobox_count++){
	SendMessage(scrollbox, CB_ADDSTRING, 0, (LPARAM) appname[combobox_count]);
	}
	SendMessage(scrollbox, CB_SETCURSEL, 0, (LPARAM) 0);
	return TRUE;
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			case ID_PATCH:
				file_selector = SendDlgItemMessage(hwndDlg, IDC_COMBOBOX, CB_GETCURSEL, 0, 0);
				sprintf(file1,"%s",app_filename[file_selector]);
				patch(hwndDlg,file1, file_selector);
				return 1;
			case ID_QUIT:
				EndDialog(hwndDlg,1);
				return 1;
			case ID_ABOUT:
		        MessageBox(hwndDlg,about,"About...",MB_OK|MB_TASKMODAL);
				return 1;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg,0);
		return TRUE;

	}
	return FALSE;
}


void patch(HWND hwndDlg,char filename[], int filetopatch)
{
	FILE * pFile, *test;
    //The patches and offsets
	//Use Ziggy/SnD's Code/Data Ripper plugins to get
	//patch data

	//8BC4
	BYTE IQTrainerPatch[2] = {0x32, 0xDB};
	//86B0
	BYTE SubliminalFlashPatch[1] = {0xC3};
	//6F2E
	BYTE SubliminalImagesPatch[2] = {0xB0, 0x01};


	pFile = fopen ( filename , "r+" ); //open for patching!
		if (pFile == NULL){
		SetDlgItemText(hwndDlg,ID_TEXT,"Error! Can't find file or file in use");
		return;
	}
	switch(filetopatch)
	{
	case 0:
		fseek(pFile,0x8BC4,SEEK_SET);
        fwrite(IQTrainerPatch,1,sizeof(IQTrainerPatch),pFile);
		break;
	case 1:  
		fseek(pFile,0x86B0,SEEK_SET);
        fwrite(SubliminalFlashPatch,1,sizeof(SubliminalFlashPatch),pFile);
		break;
	case 2: 
		fseek(pFile,0x6F2E,SEEK_SET);
        fwrite(SubliminalImagesPatch,1,sizeof(SubliminalImagesPatch),pFile);
		break;
	}
	SetDlgItemText(hwndDlg,ID_TEXT,"Patching Done!");
	fclose(pFile);
	return;
}
