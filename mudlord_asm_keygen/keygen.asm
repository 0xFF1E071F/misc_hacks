.586
.model	flat, stdcall
option	casemap :none
include	keygen.inc
include    dlg_colors.asm

.code
start:
	invoke	GetModuleHandle, NULL
	mov		hInstance, eax
	invoke	InitCommonControls
	invoke	DialogBoxParam, hInstance, IDD_MAIN, 0, offset DlgProc, 0
	invoke	ExitProcess, eax

DlgProc proc hWin:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
	LOCAL user_name[256]	:BYTE
	LOCAL user_serial[512]	:BYTE
	
	mov	eax,uMsg
	.if	eax == WM_INITDIALOG
		invoke 	GetTickCount                              
		invoke   	 nseed,EAX     
		invoke	LoadIcon,hInstance,200
		invoke	SendMessage, hWin, WM_SETICON, 1, eax
		invoke 	MakeOwnerDraw,hWin,IDB_ABOUTBOX
		invoke 	MakeOwnerDraw,hWin,IDB_GEN
		invoke 	MakeOwnerDraw,hWin,IDB_EXIT
		invoke 	SetDlgItemText, hWin, IDC_NAME, ADDR szDefaultName
		
		;we init the scroller and font usage for the scroll
		m2m scr.scroll_hwnd,hWin
		mov scr.scroll_text, offset ScrollerText
		mov scr.scroll_x,3
		mov scr.scroll_y,0
		mov scr.scroll_width,280
		mov scr.scroll_textcolor,00FFFFFFh
		invoke FindResource,NULL,ID_FONT,RT_RCDATA
		mov hFontRes,eax
		invoke LoadResource,NULL,eax
		.if eax
			invoke LockResource,eax
			mov ptrFont,eax
			invoke SizeofResource,NULL,hFontRes
			invoke AddFontMemResourceEx,ptrFont,eax,0,addr nFont
		.endif
		invoke CreateFontIndirect,addr lfFont
		mov scr.scroll_hFont,eax
		invoke CreateScroller,addr scr
		invoke uFMOD_PlaySong,addr table,xmSize,XM_MEMORY
		
	.elseif eax==WM_DRAWITEM
		invoke 	DrawButtonColor,hWin,lParam,BUTTON_COLOR,BUTTON_TEXT_COLOR,BUTTON_FRAME_COLOR
		ret
	.elseif eax==WM_CTLCOLORDLG
		invoke 	GetWindowDC,hWin
		invoke 	SelectObject,eax,hWin
		invoke 	CreateSolidBrush,000000h
	         ret
	.elseif eax==WM_CTLCOLOREDIT
		invoke 	SetTextColor, wParam, 0FFFFFFh
		invoke       SetBkMode, wParam, TRANSPARENT
		invoke 	CreateSolidBrush,000000h
		ret
	.elseif eax == WM_COMMAND
		mov	eax,wParam
		.if ax==IDC_NAME
			shr eax,16
		.if ax==EN_CHANGE
			jmp gen
		.endif
		.endif
		
		.if	eax == IDB_EXIT
			invoke	SendMessage, hWin, WM_CLOSE, 0, 0
		.endif
		.if       eax==IDB_ABOUTBOX
		         invoke	DialogBoxParam, hInstance, IDD_ABOUT, 0, offset AboutProc, 0
	         .endif
	         .if eax==IDB_GEN
	         		gen:
	         		fn GetDlgItemText,hWin,IDC_NAME,addr user_name,sizeof user_name
	             	fn KeygenProc,addr user_name, addr user_serial
	             	fn SetDlgItemText,hWin,IDC_SERIAL,addr user_serial
	          .endif
		
	.elseif	eax == WM_CLOSE
		invoke	EndDialog, hWin, 0
	.endif
	xor	eax,eax
	ret
DlgProc endp

end start