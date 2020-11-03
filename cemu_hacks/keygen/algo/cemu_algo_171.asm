PUBLIC keygen_code_171
_TEXT	SEGMENT
;returns in EAX the CPUID derived ID number
keygen_code_171 PROC
push rbp
mov rbp,rsp
sub rsp,80h
xor eax,eax
xor edi,edi
;part1
mov dword ptr [rbp-70h],eax
mov dword ptr [rbp-6Ch],eax
mov dword ptr [rbp-68h],eax
mov dword ptr [rbp-64h],eax
cpuid 
mov dword ptr [rbp-70h],eax
mov dword ptr [rbp-6Ch],ebx
mov dword ptr [rbp-68h],ecx
mov dword ptr [rbp-64h],edx
;part2
movzx eax,byte ptr [rbp-70h]
xor ecx,ecx
rol al,5
xor al,byte ptr [rbp-6Ch]
rol al,3
xor al,byte ptr [rbp-68h]
rol al,5
movzx edi,al
xor eax,eax
xor edi,dword ptr [rbp-64h]
mov dword ptr [rbp-70h],eax
mov dword ptr [rbp-6Ch],eax
mov dword ptr [rbp-68h],eax
mov dword ptr [rbp-64h],eax
mov eax,1
cpuid 
mov dword ptr [rbp-70h],eax
mov dword ptr [rbp-6Ch],ebx
mov dword ptr [rbp-68h],ecx
mov dword ptr [rbp-64h],edx
;part3
rol dil,3
xor eax,eax
xor ecx,ecx
xor dil,byte ptr [rbp-70h]
mov dword ptr [rbp-70h],eax
rol dil,7
xor dil,byte ptr [rbp-6Ch]
mov dword ptr [rbp-6Ch],eax
rol dil,3
xor dil,byte ptr [rbp-68h]
mov dword ptr [rbp-68h],eax
rol dil,7
movzx r8d,dil
xor r8d,dword ptr [rbp-64h]
mov dword ptr [rbp-64h],eax
mov eax,80000001h
cpuid 
mov dword ptr [rbp-70h],eax
rol r8b,3
mov dword ptr [rbp-6Ch],ebx
mov dword ptr [rbp-68h],ecx
mov dword ptr [rbp-64h],edx
movzx ebx,r8b
;part4
movzx eax,byte ptr [rbp-68h]
xor al,bl
rol al,3
movzx esi,al
xor esi,dword ptr [rbp-64h]
mov eax,esi ;cpuid
add rsp,80h
pop rbp
ret 
keygen_code_171 ENDP

cemu171customhash proc
mov qword ptr [rsp+018h],r8
mov dword ptr [rsp+010h],edx
push rbp
push rsi
push rdi
push r12
push r13
push r14
push r15
sub rsp,60h
mov r9d,ecx
mov r14d,ecx
mov r10d,ecx
mov r11d,ecx
mov ebx,ecx
mov edi,ecx
mov r8d,ecx
mov esi,ecx
mov ebp,ecx
shr r10d,4
shr r11d,8
shr ebx,0Ch
shr edi,10h
shr r8d,14h
shr esi,18h
shr ebp,01Ch
test cl,1
mov r12,0CEC4444EE5C67D92h
mov rcx,0C5B312B5116B3FBFh
mov r13,0AD9CDFE9A2557C35h
mov r15,0607354CC9F2A7BCEh
mov rax,r12
mov rdx,r13
cmovne rax,rcx
mov rcx,0AC8F08BB66A3FADBh
add rcx,rax
mov rax,06FC2833EFF006086h
add rcx,r9
mov qword ptr [rsp+050h],rax
rol rcx,7
xor rcx,r9
test r9b,2
cmovne rdx,rax
lea rax,qword ptr [r9+rcx]
mov rcx,r15
add rdx,rax
mov rax,0D039B154B9CD78FBh
rol rdx,7
xor rdx,r9
test r9b,4
cmovne rcx,rax
lea rax,qword ptr [r9+rdx]
add rcx,rax
mov rax,07CEFBB25F6C274CFh
rol rcx,7
xor rcx,r9
test r9b,8
mov r9,0E76F53FC5E6C3A80h
mov rdx,r9
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,r12
add rdx,rax
mov rax,0C5B312B5116B3FBFh
rol rdx,7
xor rdx,r14
test r10b,1
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r13
add rcx,rax
mov rax,06FC2833EFF006086h
rol rcx,7
xor rcx,r14
test r10b,2
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,r15
add rdx,rax
mov rax,0D039B154B9CD78FBh
rol rdx,7
xor rdx,r14
test r10b,4
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r9
add rcx,rax
mov rax,07CEFBB25F6C274CFh
rol rcx,7
xor rcx,r14
test r10b,8
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov r10,0C5B312B5116B3FBFh
add rax,rdx
mov rcx,r12
mov rdx,r13
rol rax,7
xor rax,r14
test r11b,1
cmovne rcx,r10
add rax,r14
add rcx,rax
mov rax,06FC2833EFF006086h
rol rcx,7
xor rcx,r14
test r11b,2
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,r15
add rdx,rax
mov rax,0D039B154B9CD78FBh
rol rdx,7
xor rdx,r14
test r11b,4
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r9
add rcx,rax
mov rax,07CEFBB25F6C274CFh
rol rcx,7
xor rcx,r14
test r11b,8
mov r11,06FC2833EFF006086h
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,r12
add rax,rdx
mov rdx,r13
rol rax,7
xor rax,r14
test bl,1
cmovne rcx,r10
add rax,r14
add rax,rcx
mov rcx,r15
rol rax,7
xor rax,r14
test bl,2
cmovne rdx,r11
add rax,r14
add rdx,rax
mov rax,0D039B154B9CD78FBh
rol rdx,7
xor rdx,r14
test bl,4
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r9
add rcx,rax
mov rax,07CEFBB25F6C274CFh
rol rcx,7
xor rcx,r14
test bl,8
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,r12
add rax,rdx
mov rdx,r13
rol rax,7
xor rax,r14
test dil,1
cmovne rcx,r10
add rax,r14
add rax,rcx
rol rax,7
xor rax,r14
test dil,2
cmovne rdx,r11
add rax,r14
add rax,rdx
rol rax,7
xor rax,r14
test dil,4
mov rbx,0D039B154B9CD78FBh
mov rcx,r15
mov rdx,r9
cmovne rcx,rbx
add rax,r14
add rax,rcx
mov rcx,r12
rol rax,7
xor rax,r14
test dil,8
mov rdi,07CEFBB25F6C274CFh
cmovne rdx,rdi
add rax,r14
add rax,rdx
mov rdx,r13
rol rax,7
xor rax,r14
test r8b,1
cmovne rcx,r10
add rax,r14
add rax,rcx
mov rcx,r15
rol rax,7
xor rax,r14
test r8b,2
cmovne rdx,r11
add rax,r14
add rax,rdx
mov rdx,r9
rol rax,7
xor rax,r14
test r8b,4
cmovne rcx,rbx
add rax,r14
add rax,rcx
mov rcx,r12
rol rax,7
xor rax,r14
test r8b,8
cmovne rdx,rdi
add rax,r14
add rax,rdx
mov rdx,r13
rol rax,7
xor rax,r14
test sil,1
cmovne rcx,r10
add rax,r14
add rax,rcx
mov rcx,r15
rol rax,7
xor rax,r14
test sil,2
cmovne rdx,r11
add rax,r14
add rax,rdx
mov rdx,r9
rol rax,7
xor rax,r14
test sil,4
cmovne rcx,rbx
add rax,r14
add rax,rcx
mov rcx,r12
rol rax,7
xor rax,r14
test sil,8
cmovne rdx,rdi
add rax,r14
add rax,rdx
rol rax,7
xor rax,r14
test bpl,1
cmovne rcx,r10
add rax,r14
add rax,rcx
rol rax,7
xor rax,r14
test bpl,2
mov rdx,r13
mov rcx,r15
cmovne rdx,r11
add rax,r14
add rax,rdx
mov rdx,r9
rol rax,7
xor rax,r14
test bpl,4
cmovne rcx,rbx
add rax,r14
add rax,rcx
rol rax,7
xor rax,r14
test bpl,8
cmovne rdx,rdi
add rax,r14
add rdx,rax
rol rdx,7
xor rdx,r14
mov qword ptr [rsp+0B8h],rdx
;;
;;part2
;;
movzx edx,al
mov eax,0
mov ecx,eax
mov eax,0
add eax,edx
mov edx,dword ptr [rsp+0A8h]
add ecx,eax
mov rax,qword ptr [rsp+0B0h] 
mov r14d,edx
mov r8d,edx
mov r9d,edx
mov r10d,edx
mov r11d,edx
mov ebx,edx
mov edi,edx
mov esi,edx
shr r8d,4
shr r9d,8
shr r10d,0Ch
shr r11d,010h
shr ebx,014h
shr edi,018h
shr esi,01Ch
mov rcx,0C5B312B5116B3FBFh
movzx r15d,byte ptr [rax]
mov rax,r12
movzx ebp,r15b
shr bpl,4
test dl,1
cmovne rax,rcx
mov rcx,r13
add rax,rdx
add rax,qword ptr [rsp+0B8h]
rol rax,7
xor rax,rdx
test dl,2
cmovne rcx,qword ptr [rsp+050h]
add rax,rdx
add rcx,rax
mov rax,0D039B154B9CD78FBh
rol rcx,7
xor rcx,rdx
test dl,4
mov rdx,0607354CC9F2A7BCEh
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,0E76F53FC5E6C3A80h
add rdx,rax
mov eax,dword ptr [rsp+0A8h]
rol rdx,7
xor rdx,r14
test al,8
mov rax,07CEFBB25F6C274CFh
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r12
add rcx,rax
mov rax,0C5B312B5116B3FBFh
rol rcx,7
xor rcx,r14
test r8b,1
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,r13
add rdx,rax
mov rax,06FC2833EFF006086h
rol rdx,7
xor rdx,r14
test r8b,2
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,0607354CC9F2A7BCEh
add rcx,rax
mov rax,0D039B154B9CD78FBh
rol rcx,7
xor rcx,r14
test r8b,4
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,0E76F53FC5E6C3A80h
add rdx,rax
mov rax,07CEFBB25F6C274CFh
rol rdx,7
xor rdx,r14
test r8b,8
mov r8,0607354CC9F2A7BCEh
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r12
add rcx,rax
mov rax,0C5B312B5116B3FBFh
rol rcx,7
xor rcx,r14
test r9b,1
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,r13
add rdx,rax
mov rax,06FC2833EFF006086h
rol rdx,7
xor rdx,r14
test r9b,2
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r8
add rcx,rax
mov rax,0D039B154B9CD78FBh
rol rcx,7
xor rcx,r14
test r9b,4
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
add rdx,rax
mov rax,07CEFBB25F6C274CFh
rol rdx,7
xor rdx,r14
test r9b,8
mov r9,0E76F53FC5E6C3A80h
mov rcx,r9
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r12
add rcx,rax
mov rax,0C5B312B5116B3FBFh
rol rcx,7
xor rcx,r14
test r10b,1
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,r13
add rdx,rax
mov rax,06FC2833EFF006086h
rol rdx,7
xor rdx,r14
test r10b,2
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r8
add rcx,rax
mov rax,0D039B154B9CD78FBh
rol rcx,7
xor rcx,r14
test r10b,4
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,r9
add rdx,rax
mov rax,07CEFBB25F6C274CFh
rol rdx,7
xor rdx,r14
test r10b,8
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov r10,0C5B312B5116B3FBFh
add rax,rcx
mov rdx,r12
mov rcx,r13
rol rax,7
xor rax,r14
test r11b,1
cmovne rdx,r10
add rax,r14
add rdx,rax
mov rax,06FC2833EFF006086h
rol rdx,7
xor rdx,r14
test r11b,2
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r8
add rcx,rax
mov rax,0D039B154B9CD78FBh
mov r8,06FC2833EFF006086h
rol rcx,7
xor rcx,r14
test r11b,4
cmovne rdx,rax
lea rax,qword ptr [r14+rcx]
mov rcx,r9
add rdx,rax
mov rax,07CEFBB25F6C274CFh
mov r9,0D039B154B9CD78FBh
rol rdx,7
xor rdx,r14
test r11b,8
mov r11,0607354CC9F2A7BCEh
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r12
add rax,rcx
mov rcx,r13
rol rax,7
xor rax,r14
test bl,1
cmovne rdx,r10
add rax,r14
add rax,rdx
mov rdx,r11
rol rax,7
xor rax,r14
test bl,2
cmovne rcx,r8
add rax,r14
add rax,rcx
rol rax,7
xor rax,r14
test bl,4
cmovne rdx,r9
add rax,r14
add rdx,rax
mov rax,07CEFBB25F6C274CFh
rol rdx,7
xor rdx,r14
test bl,8
mov rbx,0E76F53FC5E6C3A80h
mov rcx,rbx
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r12
add rax,rcx
mov rcx,r13
rol rax,7
xor rax,r14
test dil,1
cmovne rdx,r10
add rax,r14
add rax,rdx
rol rax,7
xor rax,r14
test dil,2
cmovne rcx,r8
add rax,r14
add rax,rcx
mov rdx,r11
mov rcx,rbx
rol rax,7
xor rax,r14
test dil,4
cmovne rdx,r9
add rax,r14
add rdx,rax
mov rax,07CEFBB25F6C274CFh
rol rdx,7
xor rdx,r14
test dil,8
cmovne rcx,rax
lea rax,qword ptr [r14+rdx]
mov rdx,r12
add rax,rcx
mov rcx,r13
rol rax,7
xor rax,r14
test sil,1
cmovne rdx,r10
add rax,r14
mov r10,07CEFBB25F6C274CFh
add rax,rdx
mov rdx,r11
rol rax,7
xor rax,r14
test sil,2
cmovne rcx,r8
add rax,r14
add rax,rcx
mov rcx,rbx
rol rax,7
xor rax,r14
test sil,4
cmovne rdx,r9
add rax,r14
add rax,rdx
mov rdx,r12
rol rax,7
xor rax,r14
test sil,8
cmovne rcx,r10
add rax,r14
add rax,rcx
mov rcx,r13
rol rax,7
xor rax,r14
test r15b,1
mov r14,0C5B312B5116B3FBFh
cmovne rdx,r14
add rax,r15
add rax,rdx
mov rdx,r11
rol rax,7
xor rax,r15
test r15b,2
cmovne rcx,r8
add rax,r15
add rax,rcx
mov rcx,rbx
rol rax,7
xor rax,r15
test r15b,4
cmovne rdx,r9
add rax,r15
add rax,rdx
mov rdx,r12
rol rax,7
xor rax,r15
test r15b,8
cmovne rcx,r10
add rax,r15
add rax,rcx
rol rax,7
xor rax,r15
test bpl,1
cmovne rdx,r14
add rax,r15
add rax,rdx
rol rax,7
mov rcx,r13
mov rdx,r11
xor rax,r15
test bpl,2
mov rdi,rbx
cmovne rcx,r8
add rax,r15
add rax,rcx
rol rax,7
xor rax,r15
test bpl,4
cmovne rdx,r9
add rax,r15
add rdx,rax
rol rdx,7
xor rdx,r15
test bpl,8
lea rax,qword ptr [r15+rdx]
cmovne rdi,r10
add rdi,rax
rol rdi,7
mov byte ptr [rsp+020h],al
xor rdi,r15
;;
;;part3
;;
mov rsi,qword ptr [rsp+0B0h]
movzx edx,al
mov ecx,eax
add eax,edx
add ecx,eax
mov rbp,06FC2833EFF006086h
mov r15,0D039B154B9CD78FBh
movzx r9d,byte ptr [rsi+1]
movzx r8d,r9b
mov rax,r12
mov r10,07CEFBB25F6C274CFh
shr r8b,4
test r9b,1
mov rcx,r13
cmovne rax,r14
mov rdx,r11
add rax,r9
add rax,rdi
mov rdi,rbx
rol rax,7
xor rax,r9
test r9b,2
cmovne rcx,rbp
add rax,r9
add rax,rcx
mov rcx,rbx
rol rax,7
xor rax,r9
test r9b,4
cmovne rdx,r15
add rax,r9
add rax,rdx
mov rdx,r12
rol rax,7
xor rax,r9
test r9b,8
cmovne rcx,r10
add rax,r9
add rax,rcx
mov rcx,r13
rol rax,7
xor rax,r9
test r8b,1
cmovne rdx,r14
add rax,r9
add rax,rdx
mov rdx,r11
rol rax,7
xor rax,r9
test r8b,2
cmovne rcx,rbp
add rax,r9
add rax,rcx
rol rax,7
xor rax,r9
test r8b,4
cmovne rdx,r15
add rax,r9
add rdx,rax
rol rdx,7
xor rdx,r9
test r8b,8
cmovne rdi,r10
lea rax,qword ptr [r9+rdx]
add rdi,rax
rol rdi,7
xor rdi,r9
;;
;;part4
;;
;movzx edx,al
mov r10,07CEFBB25F6C274CFh
mov ecx,eax
add eax,edx
add ecx,eax
mov rax,r12
mov rdx,r11
movzx r9d,byte ptr [rsi+2]
movzx r8d,r9b
mov rcx,r13
shr r8b,4
test r9b,1
cmovne rax,r14
add rax,r9
add rax,rdi
mov rdi,rbx
rol rax,7
xor rax,r9
test r9b,2
cmovne rcx,rbp
add rax,r9
add rax,rcx
mov rcx,rbx
rol rax,7
xor rax,r9
test r9b,4
cmovne rdx,r15
add rax,r9
add rax,rdx
mov rdx,r12
rol rax,7
xor rax,r9
test r9b,8
cmovne rcx,r10
add rax,r9
add rax,rcx
mov rcx,r13
rol rax,7
xor rax,r9
test r8b,1
cmovne rdx,r14
add rax,r9
add rax,rdx
mov rdx,r11
rol rax,7
xor rax,r9
test r8b,2
cmovne rcx,rbp
add rax,r9
add rax,rcx
rol rax,7
xor rax,r9
test r8b,4
cmovne rdx,r15
add rax,r9
add rdx,rax
rol rdx,7
xor rdx,r9
test r8b,8
cmovne rdi,r10
lea rax,qword ptr [r9+rdx]
add rdi,rax
rol rdi,7
xor rdi,r9
nop 
nop 
;;
;;part5
;;
mov r10,07CEFBB25F6C274CFh
mov ecx,eax
add eax,edx
add ecx,eax
mov rax,r12
mov rdx,r11
movzx r9d,byte ptr [rsi+3]
movzx r8d,r9b
mov rcx,r13
shr r8b,4
test r9b,1
cmovne rax,r14
add rax,r9
add rax,rdi
mov rdi,rbx
rol rax,7
xor rax,r9
test r9b,2
cmovne rcx,rbp
add rax,r9
add rax,rcx
mov rcx,rbx
rol rax,7
xor rax,r9
test r9b,4
cmovne rdx,r15
add rax,r9
add rax,rdx
mov rdx,r12
rol rax,7
xor rax,r9
test r9b,8
cmovne rcx,r10
add rax,r9
add rax,rcx
mov rcx,r13
rol rax,7
xor rax,r9
test r8b,1
cmovne rdx,r14
add rax,r9
add rax,rdx
mov rdx,r11
rol rax,7
xor rax,r9
test r8b,2
cmovne rcx,rbp
add rax,r9
add rax,rcx
rol rax,7
xor rax,r9
test r8b,4
cmovne rdx,r15
add rax,r9
add rdx,rax
rol rdx,7
xor rdx,r9
test r8b,8
cmovne rdi,r10
lea rax,qword ptr[r9+rdx]
add rdi,rax
rol rdi,7
xor rdi,r9
;;
;;part6
;;
mov r10,07CEFBB25F6C274CFh
mov ecx,eax
add eax,edx
add ecx,eax
mov rax,r12
mov rdx,r11
movzx r9d,byte ptr [rsi+4]
movzx r8d,r9b
mov rcx,r13
shr r8b,4
test r9b,1
cmovne rax,r14
add rax,r9
add rax,rdi
mov rdi,rbx
rol rax,7
xor rax,r9
test r9b,2
cmovne rcx,rbp
add rax,r9
add rax,rcx
mov rcx,rbx
rol rax,7
xor rax,r9
test r9b,4
cmovne rdx,r15
add rax,r9
add rax,rdx
mov rdx,r12
rol rax,7
xor rax,r9
test r9b,8
cmovne rcx,r10
add rax,r9
add rax,rcx
mov rcx,r13
rol rax,7
xor rax,r9
test r8b,1
cmovne rdx,r14
add rax,r9
add rax,rdx
mov rdx,r11
rol rax,7
xor rax,r9
test r8b,2
cmovne rcx,rbp
add rax,r9
add rax,rcx
rol rax,7
xor rax,r9
test r8b,4
cmovne rdx,r15
add rax,r9
add rdx,rax
rol rdx,7
xor rdx,r9
test r8b,8
lea rax,qword ptr[r9+rdx]
cmovne rdi,r10
add rdi,rax
rol rdi,7
xor rdi,r9
;;
;;final
;;
mov r10,07CEFBB25F6C274CFh
mov ecx,eax
add eax,edx
add ecx,eax
mov rax,r12
mov rdx,r11
mov rcx,r13
movzx r9d,byte ptr [rsi+5]
movzx r8d,r9b
shr r8b,4
test r9b,1
cmovne rax,r14
add rax,r9
add rax,rdi
rol rax,7
xor rax,r9
test r9b,2
cmovne rcx,rbp
add rax,r9
add rax,rcx
mov rcx,rbx
rol rax,7
xor rax,r9
test r9b,4
cmovne rdx,r15
add rax,r9
add rax,rdx
rol rax,7
xor rax,r9
test r9b,8
cmovne rcx,r10
add rax,r9
add rax,rcx
rol rax,7
xor rax,r9
test r8b,1
cmovne r12,r14
add rax,r9
add rax,r12
rol rax,7
xor rax,r9
test r8b,2
cmovne r13,rbp
add rax,r9
add rax,r13
rol rax,7
xor rax,r9
test r8b,4
cmovne r11,r15
add rax,r9
add rax,r11
rol rax,7
xor rax,r9
test r8b,8
cmovne rbx,r10
add rax,r9
add rax,rbx
mov rbx,qword ptr [rsp+0A0h]
rol rax,7
xor rax,r9
add rsp,060h
pop r15
pop r14
pop r13
pop r12
pop rdi
pop rsi
pop rbp
ret 


cemu171customhash endp



_TEXT	ENDS



END

