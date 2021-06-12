.586
.model flat, stdcall
option casemap: none

include keygen.inc
includelib wcrt.lib
strncpy PROTO C :DWORD,:DWORD,:DWORD
dw2ah proto :DWORD, :DWORD
GenKey 	PROTO
.const

.data
ptr1 DWORD 0;
ptr2  DWORD 0;

name_ptr DWORD 0;

 Alphabet \
db 030h, 031h, 032h, 033h, 034h, 035h, 036h, 037h
db 038h, 039h, 041h, 042h, 043h, 044h, 045h, 046h
db 047h, 048h, 049h, 04Ah, 04Bh, 04Ch, 04Dh, 04Eh
db 04Fh, 050h, 051h, 052h, 053h, 054h, 055h, 056h
db 057h, 058h, 059h, 05Ah

.data?

.code

KeygenProc PROC  _name,_serial,_key
  	LOCAL name_len	:DWORD
  	LOCAL name_rounds	:DWORD
  	
  	LOCAL name_buffer[255]:BYTE
  	LOCAL serial_buffer[16]:BYTE
  	LOCAL serial_key[16]:BYTE
  	LOCAL buffer1[4]:BYTE
  	LOCAL buffer2[4]:BYTE
  	LOCAL key1: DWORD
  	LOCAL key2: DWORD
 	LOCAL key3: DWORD
 	LOCAL  key4: DWORD
 	LOCAL keybuf1[10]:BYTE
 	LOCAL keybuf2[10]:BYTE
  	
  	
  	fn lstrlen,_name
	.if eax<4
		fnc lstrcpy,_serial,chr$("No name entered! Enter a sequence of characters.")
		xor eax,eax
		ret
	.endif
	.if eax>010h
		fnc lstrcpy,_serial,chr$("Enter a smaller sequence of characters.")
		xor eax,eax
		ret
	.endif
	mov name_len, eax
	
	invoke RtlZeroMemory,ADDR serial_buffer,SIZEOF serial_buffer
	invoke RtlZeroMemory,ADDR serial_key,SIZEOF serial_key
	invoke RtlZeroMemory,ADDR buffer1,SIZEOF buffer1
	invoke RtlZeroMemory,ADDR buffer2,SIZEOF buffer2
	invoke RtlZeroMemory,ADDR name_buffer,SIZEOF name_buffer
	fnc lstrcpy,addr name_buffer, _name
	xor edi,edi
 	
	mov EAX,name_len
	mov ebx, 4
	mov edx, 0
	div ebx
	.if name_len> 8h 
	.if edx != 0
	nop
	.endif
	.else
	inc eax
	.endif
	mov name_rounds,eax
        
	 ;reverse stringcpy/calculate name
	 mov esi,1
	 mov ptr2, 0
		mov ptr1, 0
	 .while esi != name_rounds
	 mov eax, esi
	 mov edi, 8
	 mul edi
	 mov edx,eax ; position of buffer
	 xor edi,edi
	 .while edi != 8
	 lea ecx,name_buffer
	 add ecx,edx ;bufferpos
	 mov al, [ecx-1]
	 .if edi < 4
	 mov byte ptr[buffer1+edi],al
	 .else
	 push edi
	 sub edi,4
	 mov byte ptr[buffer2+edi],al
	 pop edi
	 .endif
	 inc ebx
	 inc edi
	 dec edx
	 .endw
	 pushad
	 LEA EAX,buffer1
	 PUSH EAX
	 LEA ECX, buffer2
	 LEA EDX, ptr1
	 LEA EAX, ptr2
	 call longtion_md5
	 popad
	 
	 inc esi
	 .endw
	  
	  mov EAX, ptr2
	  push EAX
	  push chr$("0013%X1988")
	  push _serial
	  call wsprintf
	  
	  ;calc serial
	  invoke RtlZeroMemory,ADDR keybuf1,SIZEOF keybuf1
	invoke RtlZeroMemory,ADDR keybuf2,SIZEOF keybuf2
 	fnc lstrcpy,addr serial_buffer, _serial
	 fnc strncpy, addr keybuf1, addr serial_buffer,8
	 lea eax,serial_buffer
	add eax,8
	fnc strncpy, addr keybuf2, eax,8
	  
 	 fnc htodw, addr keybuf1
 	 mov key1,eax
 	mov key3,eax
	 fnc htodw, addr keybuf2
	 mov key2,eax
	  mov key4, eax
	  
	 LEA EAX,key2
	PUSH EAX
	 LEA ECX, key1
	 LEA EDX, key4
	 LEA EAX, key3
	 call longtion_md5
	 
	  fnc dw2ah, key3, addr keybuf1
	  fnc dw2ah,key4,addr keybuf2
	  fnc strncpy,addr serial_key, addr keybuf1, 8
	lea edx,serial_key
	 add edx,8
	fnc strncpy, edx, addr keybuf2,8
fnc wsprintf,_key,chr$("%.16s"),addr serial_key
	
	ret
KeygenProc ENDP

END