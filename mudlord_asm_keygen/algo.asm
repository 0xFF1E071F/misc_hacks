.586
.model flat, stdcall
option casemap: none

include keygen.inc
GenKey 	PROTO

.const

.data

 Alphabet \
db 030h, 031h, 032h, 033h, 034h, 035h, 036h, 037h
db 038h, 039h, 041h, 042h, 043h, 044h, 045h, 046h
db 047h, 048h, 049h, 04Ah, 04Bh, 04Ch, 04Dh, 04Eh
db 04Fh, 050h, 051h, 052h, 053h, 054h, 055h, 056h
db 057h, 058h, 059h, 05Ah

.data?

.code

KeygenProc PROC  _name,_serial
  	LOCAL name_len	:DWORD
  	LOCAL buffer[4]	:BYTE
  	LOCAL count 		:BYTE
  	
  	fn lstrlen,_name
	.if eax==0
		fnc lstrcpy,_serial,chr$("No name entered! Enter a sequence of characters.")
		xor eax,eax
		ret
	.endif
	mov name_len, eax
	
	invoke RtlZeroMemory,ADDR buffer,SIZEOF buffer
	xor edi,edi
	
 	.while edi != SIZEOF buffer
 	invoke nrandom, 15
 	mov al,byte ptr [Alphabet+eax]
 	mov byte ptr[buffer+edi], al
 	inc edi
 	mov byte ptr[buffer+edi], 0 ;zero terminate the string
 	.endw
 	
 	
 	

	fnc wsprintf,_serial,chr$("%s"),addr buffer
  	ret
KeygenProc ENDP

END