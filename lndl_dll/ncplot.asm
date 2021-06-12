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

mov ecx,dataLen                 ; amount to copy
mov esi,DataPtr             ; location to copy from
mov edi,MemOffset               ; location to copy to
 rep movsb                  ; copy

invoke VirtualProtect, MemOffset, dataLen, OldProt, addr OldProt
popad
ret

WriteMem endp
Patch proc
           jmp code1
           db "looky looky, I got hookie!",0
           code1:
            mov eax, 0057425Ch ;addr 
            mov edi, 0003A8E9h ;var
            mov dword ptr[eax],edi
             ;mov dword ptr[0064074Fh],660000BBh
            mov eax, 0064074Fh ;addr 
            mov edi, 660000BBh ;var
	 mov dword ptr[eax],edi
	; mov dword ptr[00640757h],900000BFh
	  mov eax, 00640757h ;addr 
            mov edi, 900000BFh ;var
	  mov dword ptr[eax],edi
	 ;mov dword ptr[00640753h],66000FB8h
	   mov eax, 00640753h ;addr 
            mov edi, 66000FB8h ;var
	    mov dword ptr[eax],edi
	 ;mov dword ptr[0064075Bh],90903FEBh
	   mov eax, 0064075Bh ;addr 
             mov edi, 90903FEBh ;var
	   mov dword ptr[eax],edi
	   jmp code2
	    db "you do realize it is lame looking at this?",0
           code2:
	 ;mov word ptr[0064075Fh],9090h
	  mov eax, 0064075Fh ;addr 
             mov edi, 9090h ;var
	   mov word ptr[eax],di
	 ;mov byte ptr[006407ABh],00h
	   mov eax, 006407ABh ;addr 
	    mov byte ptr[eax],0
	 ;mov byte ptr[00574260h],00h
	   mov eax, 00574260h ;addr 
	    mov byte ptr[eax],0
	ret	
Patch endp

End DllEntry
