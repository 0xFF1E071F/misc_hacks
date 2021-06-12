include windows.inc
include user32.inc
include kernel32.inc
include comctl32.inc	;windows common controls
include masm32.inc
include comdlg32.inc 
include cryptohash.inc
include \masm32\macros\macros.asm
include TextScroller.inc
includelib TextScroller.lib
include ufmod.inc
includelib ufmod.lib
include winmm.inc
includelib winmm.lib
includelib	user32.lib
includelib masm32.lib
includelib	kernel32.lib
includelib	comctl32.lib	;windows common controls
includelib comdlg32.lib 
include gdi32.inc
includelib gdi32.lib
includelib cryptohash.lib

DlgProc		PROTO	:DWORD,:DWORD,:DWORD,:DWORD
AboutProc	PROTO	:DWORD,:DWORD,:DWORD,:DWORD
KeygenProc 	PROTO     :DWORD,:DWORD

.const
IDD_MAIN				equ	1000
IDB_EXIT					equ	1001
IDD_ABOUT     				equ 	1004
IDB_ABOUTBOX     			equ 	1005
IDB_GEN                                      	equ 	1006
IDC_NAME                                   	equ 	1007
IDC_SERIAL                                	equ 	1008
ID_FONT					equ	2000


BUTTON_COLOR			equ 00000000h
BUTTON_TEXT_COLOR		equ 00FFFFFFh
BUTTON_FRAME_COLOR	equ 00FFFFFFh
.data
szDefaultName TCHAR "mudlord", 0
ScrollerText TCHAR "Hello and welcome to this keygen! Please support the developer if you like this app.........",
				"Greetz fly out to all decent groups like RAiD, BRD, CORE, FFF another other nice people and groups.......",
				"Special mentions go to WRATH, ARMACREW, ARTeam, RES, Dima555, CU..................", 0
lfFont  LOGFONT	<8,0,0,0,FW_DONTCARE,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,\
									DEFAULT_QUALITY	,DEFAULT_PITCH or FF_DONTCARE,'ACKNOWLEDGE -BRK-'>
nFont				dd		1

include music.inc
xmSize equ $ - table


.data?
hInstance	dd	?
scr				SCROLLER_STRUCT <>
hFontRes				dd		?
ptrFont				dd		?

