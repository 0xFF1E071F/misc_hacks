.386

.MODEL flat,stdcall

OPTION CASEMAP:NONE

Include windows.inc
Include user32.inc
Include kernel32.inc

IncludeLib user32.lib
IncludeLib kernel32.lib

.DATA


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
        ;call needed functions or operations here
         
	ret	
Patch endp

End DllEntry
