#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
000000000000088c <secret_backdoor>:
     88c: 55                           	push	rbp
     88d: 48 89 e5                     	mov	rbp, rsp
     890: 48 83 c4 80                  	add	rsp, -128
     894: 48 8b 05 1d 17 20 00         	mov	rax, qword ptr  <_DYNAMIC+0x198>
     89b: 48 8b 00                     	mov	rax, qword ptr [rax]
     89e: 48 89 c2                     	mov	rdx, rax
     8a1: 48 8d 45 80                  	lea	rax, [rbp - 128]
     8a5: be 80 00 00 00               	mov	esi, 128
     8aa: 48 89 c7                     	mov	rdi, rax
     8ad: e8 be fe ff ff               	call	 <fgets@plt>
     8b2: 48 8d 45 80                  	lea	rax, [rbp - 128]
     8b6: 48 89 c7                     	mov	rdi, rax
     8b9: e8 82 fe ff ff               	call	 <system@plt>
     8be: c9                           	leave
     8bf: c3                           	ret

00000000000008c0 <handle_msg>:
     8c0: 55                           	push	rbp
     8c1: 48 89 e5                     	mov	rbp, rsp
     8c4: 48 81 ec c0 00 00 00         	sub	rsp, 192
     8cb: 48 8d 85 40 ff ff ff         	lea	rax, [rbp - 192]
     8d2: 48 05 8c 00 00 00            	add	rax, 140
     8d8: 48 c7 00 00 00 00 00         	mov	qword ptr [rax], 0
     8df: 48 c7 40 08 00 00 00 00      	mov	qword ptr [rax + 8], 0
     8e7: 48 c7 40 10 00 00 00 00      	mov	qword ptr [rax + 16], 0
     8ef: 48 c7 40 18 00 00 00 00      	mov	qword ptr [rax + 24], 0
     8f7: 48 c7 40 20 00 00 00 00      	mov	qword ptr [rax + 32], 0
     8ff: c7 45 f4 8c 00 00 00         	mov	dword ptr [rbp - 12], 140
     906: 48 8d 85 40 ff ff ff         	lea	rax, [rbp - 192]
     90d: 48 89 c7                     	mov	rdi, rax
     910: e8 b8 00 00 00               	call	 <set_username>
     915: 48 8d 85 40 ff ff ff         	lea	rax, [rbp - 192]
     91c: 48 89 c7                     	mov	rdi, rax
     91f: e8 0e 00 00 00               	call	 <set_msg>
     924: 48 8d 3d 95 02 00 00         	lea	rdi,  <_IO_stdin_used+0x8>
     92b: e8 00 fe ff ff               	call	 <puts@plt>
     930: c9                           	leave
     931: c3                           	ret

0000000000000932 <set_msg>:
     932: 55                           	push	rbp
     933: 48 89 e5                     	mov	rbp, rsp
     936: 48 81 ec 10 04 00 00         	sub	rsp, 1040
     93d: 48 89 bd f8 fb ff ff         	mov	qword ptr [rbp - 1032], rdi
     944: 48 8d 85 00 fc ff ff         	lea	rax, [rbp - 1024]
     94b: 48 89 c6                     	mov	rsi, rax
     94e: b8 00 00 00 00               	mov	eax, 0
     953: ba 80 00 00 00               	mov	edx, 128
     958: 48 89 f7                     	mov	rdi, rsi
     95b: 48 89 d1                     	mov	rcx, rdx
     95e: f3 48 ab                     	rep		stosq	qword ptr es:[rdi], rax
     961: 48 8d 3d 65 02 00 00         	lea	rdi,  <_IO_stdin_used+0x15>
     968: e8 c3 fd ff ff               	call	 <puts@plt>
     96d: 48 8d 05 6b 02 00 00         	lea	rax,  <_IO_stdin_used+0x27>
     974: 48 89 c7                     	mov	rdi, rax
     977: b8 00 00 00 00               	mov	eax, 0
     97c: e8 cf fd ff ff               	call	 <printf@plt>
     981: 48 8b 05 30 16 20 00         	mov	rax, qword ptr  <_DYNAMIC+0x198>
     988: 48 8b 00                     	mov	rax, qword ptr [rax]
     98b: 48 89 c2                     	mov	rdx, rax
     98e: 48 8d 85 00 fc ff ff         	lea	rax, [rbp - 1024]
     995: be 00 04 00 00               	mov	esi, 1024
     99a: 48 89 c7                     	mov	rdi, rax
     99d: e8 ce fd ff ff               	call	 <fgets@plt>
     9a2: 48 8b 85 f8 fb ff ff         	mov	rax, qword ptr [rbp - 1032]
     9a9: 8b 80 b4 00 00 00            	mov	eax, dword ptr [rax + 180]
     9af: 48 63 d0                     	movsxd	rdx, eax
     9b2: 48 8d 8d 00 fc ff ff         	lea	rcx, [rbp - 1024]
     9b9: 48 8b 85 f8 fb ff ff         	mov	rax, qword ptr [rbp - 1032]
     9c0: 48 89 ce                     	mov	rsi, rcx
     9c3: 48 89 c7                     	mov	rdi, rax
     9c6: e8 55 fd ff ff               	call	 <strncpy@plt>
     9cb: c9                           	leave
     9cc: c3                           	ret

00000000000009cd <set_username>:
     9cd: 55                           	push	rbp
     9ce: 48 89 e5                     	mov	rbp, rsp
     9d1: 48 81 ec a0 00 00 00         	sub	rsp, 160
     9d8: 48 89 bd 68 ff ff ff         	mov	qword ptr [rbp - 152], rdi
     9df: 48 8d 85 70 ff ff ff         	lea	rax, [rbp - 144]
     9e6: 48 89 c6                     	mov	rsi, rax
     9e9: b8 00 00 00 00               	mov	eax, 0
     9ee: ba 10 00 00 00               	mov	edx, 16
     9f3: 48 89 f7                     	mov	rdi, rsi
     9f6: 48 89 d1                     	mov	rcx, rdx
     9f9: f3 48 ab                     	rep		stosq	qword ptr es:[rdi], rax
     9fc: 48 8d 3d e1 01 00 00         	lea	rdi,  <_IO_stdin_used+0x2c>
     a03: e8 28 fd ff ff               	call	 <puts@plt>
     a08: 48 8d 05 d0 01 00 00         	lea	rax,  <_IO_stdin_used+0x27>
     a0f: 48 89 c7                     	mov	rdi, rax
     a12: b8 00 00 00 00               	mov	eax, 0
     a17: e8 34 fd ff ff               	call	 <printf@plt>
     a1c: 48 8b 05 95 15 20 00         	mov	rax, qword ptr  <_DYNAMIC+0x198>
     a23: 48 8b 00                     	mov	rax, qword ptr [rax]
     a26: 48 89 c2                     	mov	rdx, rax
     a29: 48 8d 85 70 ff ff ff         	lea	rax, [rbp - 144]
     a30: be 80 00 00 00               	mov	esi, 128
     a35: 48 89 c7                     	mov	rdi, rax
     a38: e8 33 fd ff ff               	call	 <fgets@plt>
     a3d: c7 45 fc 00 00 00 00         	mov	dword ptr [rbp - 4], 0
     a44: eb 24                        	jmp	 <L0>
<L2>:
     a46: 8b 45 fc                     	mov	eax, dword ptr [rbp - 4]
     a49: 48 98                        	cdqe
     a4b: 0f b6 8c 05 70 ff ff ff      	movzx	ecx, byte ptr [rbp + rax - 144]
     a53: 48 8b 95 68 ff ff ff         	mov	rdx, qword ptr [rbp - 152]
     a5a: 8b 45 fc                     	mov	eax, dword ptr [rbp - 4]
     a5d: 48 98                        	cdqe
     a5f: 88 8c 02 8c 00 00 00         	mov	byte ptr [rdx + rax + 140], cl
     a66: 83 45 fc 01                  	add	dword ptr [rbp - 4], 1
<L0>:
     a6a: 83 7d fc 28                  	cmp	dword ptr [rbp - 4], 40
     a6e: 7f 11                        	jg	 <L1>
     a70: 8b 45 fc                     	mov	eax, dword ptr [rbp - 4]
     a73: 48 98                        	cdqe
     a75: 0f b6 84 05 70 ff ff ff      	movzx	eax, byte ptr [rbp + rax - 144]
     a7d: 84 c0                        	test	al, al
     a7f: 75 c5                        	jne	 <L2>
<L1>:
     a81: 48 8b 85 68 ff ff ff         	mov	rax, qword ptr [rbp - 152]
     a88: 48 8d 90 8c 00 00 00         	lea	rdx, [rax + 140]
     a8f: 48 8d 05 65 01 00 00         	lea	rax,  <_IO_stdin_used+0x43>
     a96: 48 89 d6                     	mov	rsi, rdx
     a99: 48 89 c7                     	mov	rdi, rax
     a9c: b8 00 00 00 00               	mov	eax, 0
     aa1: e8 aa fc ff ff               	call	 <printf@plt>
     aa6: c9                           	leave
     aa7: c3                           	ret

0000000000000aa8 <main>:
     aa8: 55                           	push	rbp
     aa9: 48 89 e5                     	mov	rbp, rsp
     aac: 48 8d 3d 5d 01 00 00         	lea	rdi,  <_IO_stdin_used+0x58>
     ab3: e8 78 fc ff ff               	call	 <puts@plt>
     ab8: e8 03 fe ff ff               	call	 <handle_msg>
     abd: b8 00 00 00 00               	mov	eax, 0
     ac2: 5d                           	pop	rbp
     ac3: c3                           	ret
*/
