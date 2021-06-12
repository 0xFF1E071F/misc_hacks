#include <windows.h>
#include <stdio.h>
#include "resource1.h"	
#include "release_info.h"
#include <commctrl.h>

#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif


static BOOL CALLBACK DialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);


#define MIN_NAME 1
#define MAX_NAME 50
#define MAX_SERIAL 255

void process_serial(char *name, char *serial);

int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	INITCOMMONCONTROLSEX icex;
	memset(&icex,0,sizeof(icex));
	InitCommonControlsEx(&icex); 
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
	unsigned char serial[MAX_SERIAL];
	int selection = 0;
	if(GetDlgItemText(hwnd,IDC_NAME,(char*)name,MAX_NAME)<MIN_NAME)
	{
		SetDlgItemText(hwnd, IDC_SERIAL,"Please enter a longer name...");
		return 1;
	}
	if(GetDlgItemText(hwnd,IDC_SERIAL,(char*)serial,MAX_SERIAL)<MIN_NAME)
	{
		SetDlgItemText(hwnd, IDC_SERIAL,"Please enter a longer serial...");
		return 1;
	}
	process_serial((char*)name, (char*)serial);
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

	return TRUE;
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			case IDC_GENERATE:
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
	}
	return FALSE;
}
