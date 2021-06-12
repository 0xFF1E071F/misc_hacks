#include <windows.h>
#include <stdio.h>
#include "resource1.h"	
#include "dlg_colors.c"
#include "ufmod.h"
#include "foxinbox.h"
static BOOL CALLBACK DialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
void process_serial_activeaudrec(char *serial);
void process_serial_dualaudrec(char *serial);
void process_serial_mp3cut(char *serial);
void process_serial_table(char *serial, int tableentry);
char *about   =
"Adrosoft All Products\n"
"gfx by fm212\n"
"msx: bubsy - A Fox in My Box\n"
"keygenned by mrb!/LnDL\n"
"\n\n"
"Protection for DAR/AAR: Custom + matrices\n"
"note to dev: game, set and match - try again next time ;)\n";

int prod_count = 7;
const char *products[] = { 
	"Dual Audio Recorder ",
	"Active Audio Recorder ",
	"AD Sound Recorder ", 
	"AD Stereo Changer ",
	"AD Stream Recorder ", 
	"Steady Recorder ",
	"AD MP3 Cutter"
};
#define MIN_NAME 1
#define MAX_NAME 50
#define MAX_SERIAL 70
#define BUTTON_COLOR			0x00000000
#define BUTTON_TEXT_COLOR		0x00FFFFFF
#define BUTTON_FRAME_COLOR		0x00FFFFFF

char *keygen_name = "Adrosoft All Prods Keygen";
char *default_name = "mrb!/LnDL";

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
	char serial[MAX_SERIAL];
	srand( GetTickCount());
	memset(serial,0,MAX_SERIAL);
	int selection = SendDlgItemMessage(hwnd, IDC_PRODCOMBO, CB_GETCURSEL, 0, 0);
    switch (selection)
	{
	    case 0:
		process_serial_dualaudrec(serial);
		SetDlgItemText(hwnd, IDC_SERIAL,serial);
		break;
		case 1:
		process_serial_activeaudrec(serial);
		SetDlgItemText(hwnd, IDC_SERIAL,serial);
		break;
		case 2:
		case 3:
		case 4:
		case 5:
			process_serial_table(serial, selection);
			SetDlgItemText(hwnd, IDC_SERIAL,serial);
		break;
		case 6: 
			process_serial_mp3cut(serial);
			SetDlgItemText(hwnd, IDC_SERIAL,serial);
		break;
	}
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
	HBRUSH BackBrush = CreateSolidBrush(RGB(0,0,0,));
	switch (msg) {
	case WM_INITDIALOG:
	srand(GetTickCount());
	SetWindowText(hwndDlg,keygen_name);
	uFMOD_PlaySong((void*)fox,(int*)fox_size,  XM_MEMORY);
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
		SendMessage(scrollbox, CB_ADDSTRING, 0, (LPARAM) products[combobox_count]);
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
