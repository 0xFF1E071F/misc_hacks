.386
.model	flat, stdcall
option	casemap :none
include	bones.inc
include    dlg_colors.asm

.code
start:
	invoke	GetModuleHandle, NULL
	mov		hInstance, eax
	invoke	InitCommonControls
	invoke	DialogBoxParam, hInstance, IDD_MAIN, 0, offset DlgProc, 0
	invoke	ExitProcess, eax

DlgProc proc hWin:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
        LOCAL ps:PAINTSTRUCT

	mov	eax,uMsg
	.if	eax == WM_INITDIALOG
		invoke	LoadIcon,hInstance,200
		invoke 	MakeOwnerDraw,hWin,IDB_PATCH
		invoke 	MakeOwnerDraw,hWin,IDB_ABOUTBOX
		invoke 	MakeOwnerDraw,hWin,IDB_EXIT
		invoke	SendMessage, hWin, WM_SETICON, 1, eax
		invoke 	uFMOD_PlaySong,addr table,xmSize,XM_MEMORY
	.elseif eax==WM_DRAWITEM
		invoke 	DrawButtonColor,hWin,lParam,BUTTON_COLOR,BUTTON_TEXT_COLOR,BUTTON_FRAME_COLOR
		ret
	.elseif eax==WM_CTLCOLORDLG
		invoke 	GetWindowDC,hWin
		invoke 	SelectObject,eax,hWin
		invoke 	CreateSolidBrush,000000h
	         ret
	.elseif eax == WM_COMMAND
		mov	eax,wParam
		.if	eax == IDB_EXIT
			invoke	SendMessage, hWin, WM_CLOSE, 0, 0
		.endif
		.if       eax==IDB_ABOUTBOX
		         invoke	DialogBoxParam, hInstance, IDD_ABOUT, 0, offset AboutProc, 0
	         .endif
		.if       eax==IDB_PATCH
		         invoke FileProc_SnR,hWin
	         .endif
	.elseif	eax == WM_CLOSE
		invoke	EndDialog, hWin, 0
	.endif
	xor	eax,eax
	ret
DlgProc endp

end start