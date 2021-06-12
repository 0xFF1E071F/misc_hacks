#include <windows.h>
#include <stdio.h>
#include "keygen.h"
#include "resource.h"
#include "music/hvlplay.h"
#include "music/sd.h"
static BOOL CALLBACK DialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
void process_serial(char *name, char *serial, int selection);
void CopyToClipboard(char * buf,DWORD MAXSIZE);
BOOL MagnetWindow(LPARAM *lParam);

#define MIN_NAME 10
#define MAX_NAME 100
#define MAX_SERIAL 20

;

int prod_count = 4;
const char *products[] = { 
"A Dot Mess", 
"Spycy", 
"SurfMemo", 
"VIPStegano",
};

char *keygen_name = "Axel Blume All Prods Keygen 1.0";
char *default_name = "mudlord/RED";

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

DWORD WINAPI GenerateSerial(HWND hwnd){
    unsigned char name[MAX_NAME];
	char serial[MAX_SERIAL];
	memset(serial,0,MAX_SERIAL);
    
	if(GetDlgItemText(hwnd,IDC_NAME,(char*)name,MAX_NAME)<MIN_NAME)
	{
		SetDlgItemText(hwnd, IDC_SERIAL,"Please enter a longer name...");
		return 1;
	}
	
	int selection = SendDlgItemMessage(hwnd, IDC_PRODCOMBO, CB_GETCURSEL, 0, 0);
	process_serial((char*)name, serial, selection);
	SetDlgItemText(hwnd, IDC_SERIAL,serial);
	CopyToClipboard(serial,MAX_NAME);
    return 0;
}

static BOOL CALLBACK DialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{	
    HBRUSH hBrush;
	HBRUSH BackBrush = CreateSolidBrush(RGB(0,0,0,));

	switch (msg) {

    case WM_MOVING:
		return MagnetWindow(&lParam);

	case WM_INITDIALOG:
	SetWindowText(hwndDlg,keygen_name);
    SetDlgItemText(hwndDlg, IDC_NAME,default_name);
	SetDlgItemText(hwndDlg, IDC_SERIAL,"Click 'Generate' to make a serial!");
	int combobox_count;
	HWND scrollbox;
	scrollbox = GetDlgItem(hwndDlg, IDC_PRODCOMBO);

	for (combobox_count = 0; combobox_count < prod_count; combobox_count++){
	SendMessage(scrollbox, CB_ADDSTRING, 0, (LPARAM) products[combobox_count]);
	}
	SendMessage(scrollbox, CB_SETCURSEL, 0, (LPARAM) 0);


    GenerateSerial(hwndDlg);

    HVLPlay_Load((char*)sd, sd_size);
	HVLPlay_Play();

	return TRUE;
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			case ID_QUIT:
				EndDialog(hwndDlg,1);
				return 1;
			case IDC_NAME:
   				if(HIWORD(wParam)==EN_CHANGE)
					GenerateSerial(hwndDlg);
				break;
			case IDC_PRODCOMBO:
				if(HIWORD(wParam)==CBN_SELCHANGE)
					GenerateSerial(hwndDlg);
				break;

		}
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg,0);
		return TRUE;

	 case WM_CTLCOLORDLG:
         return (BOOL) BackBrush; 

	 case WM_CTLCOLORSTATIC:
	 case WM_CTLCOLORLISTBOX:
	 case WM_CTLCOLOREDIT:{
			SetTextColor((HDC)wParam, RGB(255,0,0));
			SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
			return (BOOL)hBrush;
		}

	}
	return FALSE;
}

void CopyToClipboard(char * buf,DWORD MAXSIZE)
{
      HANDLE handle;
      char * str;            //This has the data that is to be copied to the clipboard
      if(OpenClipboard(NULL))
      {
            EmptyClipboard();

            handle = GlobalAlloc(GMEM_MOVEABLE,MAXSIZE+1);
            if(handle)
            {
                  str = (LPTSTR)GlobalLock(handle);
                  memcpy(str,buf,MAXSIZE);
                  GlobalUnlock(handle);
                  SetClipboardData(CF_TEXT, handle);
            }
            CloseClipboard();
      }
      delete buf;
}

BOOL MagnetWindow(LPARAM *lParam)
{
	RECT *pRect = (LPRECT) *lParam;	// screen coordinates
	static RECT rcOld = { 0, 0, 0, 0 };
	RECT rcDesktop;					// dimension of desktop work area
	INT	 iPower = 20;	// how long distance windows snap (in pixels)
	SIZE szSize;		// size of window

	// get the desktop work area dimension
	if(FALSE == SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0))
		return FALSE;

	szSize.cx = pRect->right -  pRect->left;
	szSize.cy = pRect->bottom - pRect->top;


	if(pRect->top < iPower && rcOld.top > pRect->top)
	{
		pRect->top = 0;
		pRect->bottom = szSize.cy;
	}
	else
	if(pRect->bottom > (rcDesktop.bottom - iPower) &&
	   rcOld.bottom  < pRect->bottom)
	{
		pRect->bottom = rcDesktop.bottom;
		pRect->top = rcDesktop.bottom - szSize.cy;
	}

	if(pRect->left < iPower && rcOld.left > pRect->left)
	{
		pRect->left = 0;
		pRect->right = szSize.cx;
	}
	else
	if(pRect->right > (rcDesktop.right - iPower) &&
		rcOld.right < pRect-> right)
	{
		pRect->right = rcDesktop.right;
		pRect->left =  rcDesktop.right - szSize.cx;
	}

	rcOld.top = pRect -> top;
	rcOld.bottom = pRect -> bottom;
	rcOld.left = pRect -> left;
	rcOld.right = pRect -> right;

	return TRUE;
}

