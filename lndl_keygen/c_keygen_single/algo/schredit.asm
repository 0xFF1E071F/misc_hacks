.586
.model flat, stdcall
option casemap: none

include keygen.inc
.const

.data

.data?
.code

GetRandomByte proc min:BYTE,max:BYTE
        @loop1:
                invoke nrandom, max
                cmp al,min
                jl @loop1
                cmp al,max
                jg @loop1
        ret
GetRandomByte endp


KeygenProc PROC  _serial
	LOCAL buffer[7]	:BYTE
	LOCAL buffer2[3]	:BYTE
           LOCAL  xor_result: BYTE
           invoke RtlZeroMemory,ADDR buffer,SIZEOF buffer
           invoke RtlZeroMemory,ADDR buffer2,SIZEOF buffer2
	xor edi,edi
	mov xor_result, 0
 	.while edi != 5
           invoke GetRandomByte, '0','9'
 	mov bl,al
 	mov byte ptr[buffer+edi], bl
 	 xor xor_result,bl
 	 inc edi
 	.endw
 	mov byte ptr[buffer+5],'0'
 	mov al, byte ptr[buffer+0]
 	fnc wsprintf,addr buffer2, chr$("%.2d"),xor_result
	fnc wsprintf,_serial,chr$("%s%s"),addr buffer,addr buffer2
  	ret
KeygenProc ENDP

END