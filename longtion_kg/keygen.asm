.586
.model	flat, stdcall
option	casemap :none
include	keygen.inc

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
	LOCAL user_key[512]	:BYTE
	LOCAL combohwnd             :HWND
	
	mov	eax,uMsg
	.if	eax == WM_INITDIALOG
		invoke 	GetTickCount                              
		invoke   	 nseed,EAX     
		invoke	LoadIcon,hInstance,200
		invoke	SendMessage, hWin, WM_SETICON, 1, eax
		invoke 	SetDlgItemText, hWin, IDC_NAME, ADDR szDefaultName
		invoke GetDlgItem,hWin,IDC_PRODLIST
		mov combohwnd, eax
		lea ecx,comboarray
		PrintArray:
		push ecx
		invoke SendMessage,combohwnd, CB_ADDSTRING, 0,ecx
		pop ecx
		@@:
		.if byte ptr [ecx] != 0
  		inc ecx
  		jmp @B
		.else
 	;test to see if it is the end of the array
  		.if byte ptr [ecx+1] != 0
     		inc ecx      ;point next chain
     		jmp PrintArray
  		.endif
		.endif
		invoke SendMessage,combohwnd, CB_SETCURSEL, 0,0
		
		
		
	.elseif eax == WM_COMMAND
		mov	eax,wParam
		
		.if	eax == IDB_EXIT
			invoke	SendMessage, hWin, WM_CLOSE, 0, 0
		.endif
		.if       eax==IDB_ABOUTBOX
		         invoke	DialogBoxParam, hInstance, IDD_ABOUT, 0, offset AboutProc, 0
	         .endif
	         .if eax==IDB_GEN
	         		gen:
	         		invoke RtlZeroMemory,ADDR user_key,SIZEOF user_key
	         		fn GetDlgItemText,hWin,IDC_NAME,addr user_name,sizeof user_name
	         		invoke SendMessage,combohwnd, CB_GETCURSEL, 0,0
	             	fn KeygenProc,addr user_name, addr user_serial, addr user_key
	             	fn SetDlgItemText,hWin,IDC_SERIAL,addr user_serial
	             	fn SetDlgItemText,hWin,IDC_KEY,addr user_key
	          .endif
		
	.elseif	eax == WM_CLOSE
		invoke	EndDialog, hWin, 0
	.endif
	xor	eax,eax
	ret
DlgProc endp

end start