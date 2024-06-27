#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	/*
08048444 <main>:
 8048444: 55                           	push	ebp
 8048445: 89 e5                        	mov	ebp, esp
 8048447: 57                           	push	edi
 8048448: 53                           	push	ebx
 8048449: 83 e4 f0                     	and	esp, -16
 804844c: 81 ec 90 00 00 00            	sub	esp, 144
 8048452: c7 84 24 8c 00 00 00 00 00 00 00     	mov	dword ptr [esp + 140], 0
 804845d: a1 f0 97 04 08               	mov	eax, dword ptr [134518768]			; stdin
 8048462: 89 44 24 08                  	mov	dword ptr [esp + 8], eax
 8048466: c7 44 24 04 64 00 00 00      	mov	dword ptr [esp + 4], 100
 804846e: 8d 44 24 28                  	lea	eax, [esp + 40]
 8048472: 89 04 24                     	mov	dword ptr [esp], eax
 8048475: e8 d6 fe ff ff               	call	 <fgets@plt>
	*/
	char buffer[100];
	fgets(buffer, 100, stdin);
	/*
 804847a: c7 84 24 8c 00 00 00 00 00 00 00     	mov	dword ptr [esp + 140], 0
	*/
	int i = 0; // esp + 140
	/*
 8048485: eb 4c                        	jmp	 <L0>
<L0>:
 80484d3: 8b 9c 24 8c 00 00 00         	mov	ebx, dword ptr [esp + 140]
 80484da: 8d 44 24 28                  	lea	eax, [esp + 40]
 80484de: c7 44 24 1c ff ff ff ff      	mov	dword ptr [esp + 28], 4294967295
 80484e6: 89 c2                        	mov	edx, eax
 80484e8: b8 00 00 00 00               	mov	eax, 0
 80484ed: 8b 4c 24 1c                  	mov	ecx, dword ptr [esp + 28]
 80484f1: 89 d7                        	mov	edi, edx
 80484f3: f2 ae                        	repne		scasb	al, byte ptr es:[edi]
 80484f5: 89 c8                        	mov	eax, ecx
 80484f7: f7 d0                        	not	eax
 80484f9: 83 e8 01                     	sub	eax, 1
 80484fc: 39 c3                        	cmp	ebx, eax
 80484fe: 72 87                        	jb	 <L2>
	*/
	while (i < strlen(buffer))
	{
		/*
<L2>:
 8048487: 8d 44 24 28                  	lea	eax, [esp + 40]
 804848b: 03 84 24 8c 00 00 00         	add	eax, dword ptr [esp + 140]
 8048492: 0f b6 00                     	movzx	eax, byte ptr [eax]
 8048495: 3c 40                        	cmp	al, 64
 8048497: 7e 32                        	jle	 <L1>
 8048499: 8d 44 24 28                  	lea	eax, [esp + 40]
 804849d: 03 84 24 8c 00 00 00         	add	eax, dword ptr [esp + 140]
 80484a4: 0f b6 00                     	movzx	eax, byte ptr [eax]
 80484a7: 3c 5a                        	cmp	al, 90
 80484a9: 7f 20                        	jg	 <L1>
 80484ab: 8d 44 24 28                  	lea	eax, [esp + 40]
 80484af: 03 84 24 8c 00 00 00         	add	eax, dword ptr [esp + 140]
 80484b6: 0f b6 00                     	movzx	eax, byte ptr [eax]
 80484b9: 89 c2                        	mov	edx, eax
 80484bb: 83 f2 20                     	xor	edx, 32
 80484be: 8d 44 24 28                  	lea	eax, [esp + 40]
 80484c2: 03 84 24 8c 00 00 00         	add	eax, dword ptr [esp + 140]
 80484c9: 88 10                        	mov	byte ptr [eax], dl
		*/
		if (buffer[i] > 64 && buffer[i] <= 90)
			buffer[i] ^= 32;
		i++;
	}
	/*
<L1>:
 80484cb: 83 84 24 8c 00 00 00 01      	add	dword ptr [esp + 140], 1
 8048500: 8d 44 24 28                  	lea	eax, [esp + 40]
 8048504: 89 04 24                     	mov	dword ptr [esp], eax
 8048507: e8 34 fe ff ff               	call	 <printf@plt>
	*/
	printf(buffer);
	/*
 804850c: c7 04 24 00 00 00 00         	mov	dword ptr [esp], 0
 8048513: e8 58 fe ff ff               	call	 <exit@plt>
	*/
	exit(0);
	return 0;
}
