#include <windows.h>
#include <stdio.h>
#include "resource1.h"	
#include "dlg_colors.c"
#include "ufmod.h"
#include "release_info.h"

static BOOL CALLBACK DialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);


#define MIN_NAME 1
#define MAX_NAME 50
#define MAX_SERIAL 1024
#define BUTTON_COLOR			0x00000000
#define BUTTON_TEXT_COLOR		0x00FFFFFF
#define BUTTON_FRAME_COLOR		0x00FFFFFF

void process_serial(char *name, char *serial, int selection);

int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	memset(&wc,0,sizeof(wc));
	wc.lpfnWndProc = DefDlgProc;
	wc.cbWndExtra = DLGWINDOWEXTRA;
	wc.hInstance = hinst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	wc.lpszClassName = "keygen";
	RegisterClass(&wc);
	return DialogBox(hinst, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, (DLGPROC) DialogFunc);
}



DWORD WINAPI GenerateSerial(HWND hwnd){
	unsigned char name[MAX_NAME];
	char serial[MAX_SERIAL];
	memset(serial,0,MAX_SERIAL);
	int selection = 0;
	if(GetDlgItemText(hwnd,IDC_NAME,(char*)name,MAX_NAME)<MIN_NAME)
	{
		SetDlgItemText(hwnd, IDC_SERIAL,"Please enter a longer name...");
		return 1;
	}
	srand(GetTickCount());
	memset(serial,0,MAX_SERIAL);
	selection = SendDlgItemMessage(hwnd, IDC_PRODCOMBO, CB_GETCURSEL, 0, 0);
	process_serial((char*)name, serial,selection);
	SetDlgItemText(hwnd, IDC_SERIAL,serial);
	return 0;
}





static BOOL CALLBACK DialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	RECT rect;
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	int width, height; 
	int px = 0;
	int py = 0;

    HBRUSH hBrush;
	HBRUSH BackBrush = CreateSolidBrush(RGB(0,0,0));
	switch (msg) {
	case WM_INITDIALOG:
	srand(GetTickCount());
	SetWindowText(hwndDlg,keygen_name);
	SetDlgItemText(hwndDlg, IDC_NAME,default_name);
//	uFMOD_PlaySong((void*)fox,(int*)fox_size,  XM_MEMORY);
	//centre window
	GetWindowRect(hwndDlg, &rect);
	width  = rect.right  - rect.left;
	height = rect.bottom - rect.top;
	if(cx > width) {

		px = (int)((cx - width)/2);
	}
	if(cy > height) {

		py = (int) ((cy - height)/2);
	}
	MoveWindow(hwndDlg, px, py,width, height, FALSE);

	int combobox_count;
	HWND scrollbox;
	scrollbox = GetDlgItem(hwndDlg, IDC_PRODCOMBO);
	for (combobox_count = 0; combobox_count < prod_count; combobox_count++){
		SendMessage(scrollbox, CB_ADDSTRING, 0, (LPARAM)products[combobox_count]);
	}
	SendMessage(scrollbox, CB_SETCURSEL, 0, (LPARAM) 0);

    GenerateSerial(hwndDlg);
	c_MakeOwnerDraw(hwndDlg,IDC_GENERATE);
	c_MakeOwnerDraw(hwndDlg,IDC_ABOUT);
	c_MakeOwnerDraw(hwndDlg,IDC_EXIT);

	return TRUE;
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			case IDC_GENERATE:
				GenerateSerial(hwndDlg);
				break;
			case IDC_PRODCOMBO:
				if(HIWORD(wParam)==CBN_SELCHANGE)
					GenerateSerial(hwndDlg);
				break;
			case IDC_EXIT:
				EndDialog(hwndDlg,0);
				break;
			case IDC_ABOUT:
				MessageBox(hwndDlg,about,"About this keygen....",MB_OK|MB_ICONEXCLAMATION);

		}
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg,0);
		return TRUE;
	case 	WM_DRAWITEM:
			return (c_DrawButtonColor(hwndDlg,lParam,BUTTON_COLOR,BUTTON_TEXT_COLOR,BUTTON_FRAME_COLOR));
			break;
	 case WM_CTLCOLORDLG:
         return (BOOL) BackBrush; 
	 case WM_CTLCOLORSTATIC:
	 case WM_CTLCOLORLISTBOX:
	 case WM_CTLCOLOREDIT:{
			SetTextColor((HDC)wParam, RGB(255,255,255));
            SetBkColor((HDC)wParam, RGB(0,0,0));
			hBrush = CreateSolidBrush(RGB(0,0,0));
			return (BOOL)hBrush;
		}
	}
	return FALSE;
}
