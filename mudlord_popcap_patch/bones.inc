include windows.inc
include user32.inc
include kernel32.inc
include comctl32.inc	;windows common controls
include masm32.inc
include comdlg32.inc 
include ufmod.inc
include winmm.inc

include \masm32\macros\macros.asm


includelib winmm.lib
includelib ufmod.lib
includelib	user32.lib
includelib	kernel32.lib
includelib	comctl32.lib	;windows common controls
includelib comdlg32.lib 
include gdi32.inc
includelib gdi32.lib

DlgProc		PROTO	:DWORD,:DWORD,:DWORD,:DWORD
AboutProc	PROTO	:DWORD,:DWORD,:DWORD,:DWORD
FileProc_SnR PROTO:HWND

.const
IDD_MAIN				equ	1000
IDD_ABOUT     				equ 1004
IDB_ABOUTBOX     			equ 1005
IDB_EXIT					equ	1001
IDB_PATCH 				equ 1003
BUTTON_COLOR			equ 00000000h
BUTTON_TEXT_COLOR		equ 00FFFFFFh
BUTTON_FRAME_COLOR	equ 00FFFFFFh

.data
include result.inc
xmSize equ $ - table

.data?
hInstance	dd	?