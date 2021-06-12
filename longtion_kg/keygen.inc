include windows.inc
include user32.inc
include kernel32.inc
include comctl32.inc	;windows common controls
include masm32.inc
include comdlg32.inc 
include \masm32\macros\macros.asm
includelib	user32.lib
includelib masm32.lib
includelib	kernel32.lib
includelib	comctl32.lib	;windows common controls
includelib comdlg32.lib 
include gdi32.inc
includelib gdi32.lib

DlgProc		PROTO	:DWORD,:DWORD,:DWORD,:DWORD
AboutProc	PROTO	:DWORD,:DWORD,:DWORD,:DWORD
KeygenProc 	PROTO     :DWORD,:DWORD,:DWORD

longtion_md5 PROTO

.const
IDD_MAIN				equ	1000
IDB_EXIT					equ	1001
IDD_ABOUT     				equ 	1004
IDB_ABOUTBOX     			equ 	1005
IDB_GEN                                      	equ 	1006
IDC_NAME                                   	equ 	1007
IDC_SERIAL                                	equ 	1008
IDC_KEY                                	           equ 	1012
IDC_PRODLIST                                	           equ 	1014
ID_FONT					equ	2000


BUTTON_COLOR			equ 00000000h
BUTTON_TEXT_COLOR		equ 00FFFFFFh
BUTTON_FRAME_COLOR	equ 00FFFFFFh
.data
szDefaultName TCHAR "mrb!/LnDL", 0
String	db ' mrb!',0Ah
		db 'proudly presents',0Ah
		db 0Ah
		db 'Longtion All Products Keygen v1.00',0Ah
		db '      Protection: Some heavily modded MD5 routines ',0Ah
		db 0Ah
		db 'Cracked/coded/by mrb!',0Ah
		db 'gfx by fm121',0Ah
		db 'msx: Someone cool :)',0Ah
		db 0Ah
		db 0Ah
		db 'A special notice:',0Ah
		db 'Dev: Try harder.',0Ah
		db 'That is all. Bye!',0Ah
		db 0Ah,0
comboarray db "AutoRun Pro Enterprise II",0
                         db "AutoRun Pro Enterprise",0
                         db "AutoRun Pro",0
                         db "AutoRun Expert",0
                         db "Longtion Application Builder",0
                         db "FlashDemo Pro",0
                          db "SlideShow Pro",0
                         db "GIF Animator",0
                         db "Audio CD Burner",0
                         db "Data CD Burner",0,0
.data?
hInstance	dd	?

