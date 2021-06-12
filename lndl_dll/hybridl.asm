.386

.MODEL flat,stdcall

OPTION CASEMAP:NONE

Include windows.inc
Include user32.inc
Include kernel32.inc

IncludeLib user32.lib
IncludeLib kernel32.lib

.DATA

Patch1 \
db 066h, 0FFh, 080h, 0CAh, 002h, 000h, 000h, 090h ,0EBh, 010h

Patch2 \
db 0E9h, 0E9h, 000h, 000h, 000h, 090h
Patch3 \
db 0E9h, 0A2h, 000h, 000h, 000h, 090h
Patch4 \
db 0E9h, 007h, 002h, 000h, 000h, 090h
Patch5 \
db 0BAh, 0B0h, 030h, 05Ah, 000h

Patch	PROTO
.code
DllEntry proc hInstance:HINSTANCE, reason:DWORD, reserved1:DWORD
	.if reason==DLL_PROCESS_ATTACH
		invoke Patch
	.endif
	mov  eax,TRUE
	ret
DllEntry Endp
; See skeleton.def: This is an exported function


WriteMem proc   MemOffset:DWORD, DataPtr:DWORD, dataLen:DWORD
LOCAL OldProt:DWORD

pushad
invoke VirtualProtect, MemOffset, dataLen, PAGE_EXECUTE_READWRITE, addr OldProt
invoke RtlMoveMemory, MemOffset, DataPtr, dataLen

invoke VirtualProtect, MemOffset, dataLen, OldProt, addr OldProt
popad
ret

WriteMem endp
Patch proc
          invoke WriteMem,  00481B35h, addr Patch1, sizeof Patch1
           invoke WriteMem,  0058395Dh, addr Patch2, sizeof Patch2
          invoke WriteMem,  00583A98h, addr Patch3, sizeof Patch3
          invoke WriteMem,  00583B49h, addr Patch4, sizeof Patch4
           invoke WriteMem,  0058C981h, addr Patch5, sizeof Patch5
         
	ret	
Patch endp

End DllEntry
