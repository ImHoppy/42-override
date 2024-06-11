#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void clear_stdin(void)
{
	/*
080485c4 <clear_stdin>:
 80485c4: 55                            push    ebp
 80485c5: 89 e5                         mov     ebp, esp
 80485c7: 83 ec 18                      sub     esp, 24
 80485ca: c6 45 f7 00                   mov     byte ptr [ebp - 9], 0
	*/
	char c = 0; // ebp - 9
	/*
 80485ce: eb 01                         jmp      <L0>
<L2>:
 80485d0: 90                            nop
	*/
	do
	{
		/*
<L0>:
 80485d1: e8 ba fe ff ff                call     <getchar@plt>
 80485d6: 88 45 f7                      mov     byte ptr [ebp - 9], al
		*/
		c = getchar();
		/*
 80485d9: 80 7d f7 0a                   cmp     byte ptr [ebp - 9], 10
 80485dd: 74 06                         je       <L1>
		*/
		if (c == '\n')
			return;
		/*
 80485df: 80 7d f7 ff                   cmp     byte ptr [ebp - 9], -1
 80485e3: 75 eb                         jne      <L2>
		*/
	} while (c != -1);
	/*
<L1>:
 80485e5: c9                            leave
 80485e6: c3                            ret
	*/
}

unsigned int get_unum()
{
	/*
080485e7 <get_unum>:
 80485e7: 55                            push    ebp
 80485e8: 89 e5                         mov     ebp, esp
 80485ea: 83 ec 28                      sub     esp, 40
 80485ed: c7 45 f4 00 00 00 00          mov     dword ptr [ebp - 12], 0
	*/
	unsigned int input = 0; // [ebp - 12]
	/*
 80485f4: a1 60 a0 04 08                mov     eax, dword ptr [134520928]
 80485f9: 89 04 24                      mov     dword ptr [esp], eax
 80485fc: e8 7f fe ff ff                call     <fflush@plt>
	*/
	fflush(stdout);
	/*
 8048601: b8 d0 8a 04 08                mov     eax, 134515408 // "%u"
 8048606: 8d 55 f4                      lea     edx, [ebp - 12]
 8048609: 89 54 24 04                   mov     dword ptr [esp + 4], edx
 804860d: 89 04 24                      mov     dword ptr [esp], eax
 8048610: e8 eb fe ff ff                call     <__isoc99_scanf@plt>
	*/
	scanf("%u", &input); // esp, esp + 4
	/*
 8048615: e8 aa ff ff ff                call     <clear_stdin>
	*/
	clear_stdin();
	/*
 804861a: 8b 45 f4                      mov     eax, dword ptr [ebp - 12]
 804861d: c9                            leave
 804861e: c3                            ret
	*/
	return input;
}

int store_number(unsigned int *stockage)
{
	/*
08048630 <store_number>:
 8048630: 55                            push    ebp
 8048631: 89 e5                         mov     ebp, esp
 8048633: 83 ec 28                      sub     esp, 40
 8048636: c7 45 f0 00 00 00 00          mov     dword ptr [ebp - 16], 0
 804863d: c7 45 f4 00 00 00 00          mov     dword ptr [ebp - 12], 0
	*/
	/*
 8048644: b8 d3 8a 04 08                mov     eax, 134515411
 8048649: 89 04 24                      mov     dword ptr [esp], eax
 804864c: e8 1f fe ff ff                call     <printf@plt>
	*/
	printf(" Number: ");
	/*
 8048651: e8 91 ff ff ff                call     <get_unum>
 8048656: 89 45 f0                      mov     dword ptr [ebp - 16], eax
	*/
	unsigned int number = get_unum(); // ebp - 16
	/*
 8048659: b8 dd 8a 04 08                mov     eax, 134515421
 804865e: 89 04 24                      mov     dword ptr [esp], eax
 8048661: e8 0a fe ff ff                call     <printf@plt>
	*/
	printf(" Index: ");
	/*
 8048666: e8 7c ff ff ff                call     <get_unum>
 804866b: 89 45 f4                      mov     dword ptr [ebp - 12], eax
	*/
	unsigned int index = get_unum(); // ebp - 12
	/*
 804866e: 8b 4d f4                      mov     ecx, dword ptr [ebp - 12]
 8048671: ba ab aa aa aa                mov     edx, 2863311531
 8048676: 89 c8                         mov     eax, ecx
 8048678: f7 e2                         mul     edx ; index * 2863311531
 804867a: d1 ea                         shr     edx ; edx = index / 2
 804867c: 89 d0                         mov     eax, edx ; eax = edx
 804867e: 01 c0                         add     eax, eax ; eax = edx * 2
 8048680: 01 d0                         add     eax, edx ; eax = edx * 3
 8048682: 89 ca                         mov     edx, ecx ; edx = index
 8048684: 29 c2                         sub     edx, eax ; edx = index - (edx * 3)
 8048686: 85 d2                         test    edx, edx ; edx == 0
 8048688: 74 0d                         je       <L0>
 804868a: 8b 45 f0                      mov     eax, dword ptr [ebp - 16]
 804868d: c1 e8 18                      shr     eax, 24
 8048690: 3d b7 00 00 00                cmp     eax, 183
 8048695: 75 2b                         jne      <L1>
	*/
	if (index % 3 == 0 || (number >> 24) == 183)
	{
		/*
<L0>:
 8048697: c7 04 24 e6 8a 04 08          mov     dword ptr [esp], 134515430
 804869e: e8 1d fe ff ff                call     <puts@plt>
		*/
		puts(" *** ERROR! ***");
		/*
 80486a3: c7 04 24 f8 8a 04 08          mov     dword ptr [esp], 134515448
 80486aa: e8 11 fe ff ff                call     <puts@plt>
		*/
		puts("   This index is reserved for wil!");
		/*
 80486af: c7 04 24 e6 8a 04 08          mov     dword ptr [esp], 134515430
 80486b6: e8 05 fe ff ff                call     <puts@plt>
		*/
		puts(" *** ERROR! ***");
		/*
 80486bb: b8 01 00 00 00                mov     eax, 1
 80486c0: eb 13                         jmp      <L2>
		*/
		return 1;
	}
	else
	{
		/*
<L1>:
 80486c2: 8b 45 f4                      mov     eax, dword ptr [ebp - 12]		; INDEX
 80486c5: c1 e0 02                      shl     eax, 2							; INDEX * 4
 80486c8: 03 45 08                      add     eax, dword ptr [ebp + 8]		; INDEX + STOCKAGE
 80486cb: 8b 55 f0                      mov     edx, dword ptr [ebp - 16]
 80486ce: 89 10                         mov     dword ptr [eax], edx
		*/
		stockage[index] = number;
	}
	/*
 80486d0: b8 00 00 00 00                mov     eax, 0
	*/
	return 0;
	/*
<L2>:
 80486d5: c9                            leave
 80486d6: c3                            ret
	*/
}

int read_number(int stockage[])
{
	/*
 080486d7 <read_number>:
 80486d7: 55                            push    ebp
 80486d8: 89 e5                         mov     ebp, esp
 80486da: 83 ec 28                      sub     esp, 40
 80486dd: c7 45 f4 00 00 00 00          mov     dword ptr [ebp - 12], 0
	*/
	unsigned int input = 0; // ebp - 12
	/*
 80486e4: b8 dd 8a 04 08                mov     eax, 134515421
 80486e9: 89 04 24                      mov     dword ptr [esp], eax
 80486ec: e8 7f fd ff ff                call     <printf@plt>
	*/
	printf(" Index: ");
	/*
 80486f1: e8 f1 fe ff ff                call     <get_unum>
 80486f6: 89 45 f4                      mov     dword ptr [ebp - 12], eax
	*/
	input = get_unum();
	/*
 80486f9: 8b 45 f4                      mov     eax, dword ptr [ebp - 12]
 80486fc: c1 e0 02                      shl     eax, 2
 80486ff: 03 45 08                      add     eax, dword ptr [ebp + 8]
 8048702: 8b 10                         mov     edx, dword ptr [eax]
 8048704: b8 1b 8b 04 08                mov     eax, 134515483
 8048709: 89 54 24 08                   mov     dword ptr [esp + 8], edx
 804870d: 8b 55 f4                      mov     edx, dword ptr [ebp - 12]
 8048710: 89 54 24 04                   mov     dword ptr [esp + 4], edx
 8048714: 89 04 24                      mov     dword ptr [esp], eax
 8048717: e8 54 fd ff ff                call     <printf@plt>
	*/
	printf(" Number at data[%u] is %u\n", input, stockage[input]);
	/*
 804871c: b8 00 00 00 00                mov     eax, 0
 8048721: c9                            leave
 8048722: c3                            ret
	*/
	return 0;
}

int main(int ac, char **av, char **env)
{
	/*
08048723 <main>:
 8048723: 55                            push    ebp
 8048724: 89 e5                         mov     ebp, esp
 8048726: 57                            push    edi
 8048727: 56                            push    esi
 8048728: 53                            push    ebx
 8048729: 83 e4 f0                      and     esp, -16
 804872c: 81 ec d0 01 00 00             sub     esp, 464						; Stack size = 464
 8048732: 8b 45 0c                      mov     eax, dword ptr [ebp + 12]
 8048735: 89 44 24 1c                   mov     dword ptr [esp + 28], eax
 8048739: 8b 45 10                      mov     eax, dword ptr [ebp + 16]
 804873c: 89 44 24 18                   mov     dword ptr [esp + 24], eax
 8048740: 65 a1 14 00 00 00             mov     eax, dword ptr gs:[20]
 8048746: 89 84 24 cc 01 00 00          mov     dword ptr [esp + 460], eax
 804874d: 31 c0                         xor     eax, eax
 804874f: c7 84 24 b4 01 00 00 00 00 00 00      mov     dword ptr [esp + 436], 0
	*/
	int ret = 0; // esp + 436
	/*
 804875a: c7 84 24 b8 01 00 00 00 00 00 00      mov     dword ptr [esp + 440], 0
	*/
	char line[20] = {0}; // esp + 440 (+ 4)
	/*
 8048765: c7 84 24 bc 01 00 00 00 00 00 00      mov     dword ptr [esp + 444], 0
 8048770: c7 84 24 c0 01 00 00 00 00 00 00      mov     dword ptr [esp + 448], 0
 804877b: c7 84 24 c4 01 00 00 00 00 00 00      mov     dword ptr [esp + 452], 0
 8048786: c7 84 24 c8 01 00 00 00 00 00 00      mov     dword ptr [esp + 456], 0

 8048791: 8d 5c 24 24                   lea     ebx, [esp + 36]
 8048795: b8 00 00 00 00                mov     eax, 0
 804879a: ba 64 00 00 00                mov     edx, 100
 804879f: 89 df                         mov     edi, ebx
 80487a1: 89 d1                         mov     ecx, edx
 80487a3: f3 ab                         rep             stosd   dword ptr es:[edi], eax
	*/
	unsigned int stockage[100]; // esp + 36
	bzero(stockage, 100);
	/*
 80487a5: eb 43                         jmp      <L0>
<L0>:
 80487ea: 8b 44 24 1c                   mov     eax, dword ptr [esp + 28]
 80487ee: 8b 00                         mov     eax, dword ptr [eax]
 80487f0: 85 c0                         test    eax, eax
 80487f2: 75 b3                         jne      <L1>
 80487f4: eb 43                         jmp      <L2>
	*/
	while (*av)
	{
		/*
<L1>:
 80487a7: 8b 44 24 1c                   mov     eax, dword ptr [esp + 28]
 80487ab: 8b 00                         mov     eax, dword ptr [eax]
 80487ad: c7 44 24 14 ff ff ff ff       mov     dword ptr [esp + 20], 4294967295
 80487b5: 89 c2                         mov     edx, eax
 80487b7: b8 00 00 00 00                mov     eax, 0
 80487bc: 8b 4c 24 14                   mov     ecx, dword ptr [esp + 20]
 80487c0: 89 d7                         mov     edi, edx
 80487c2: f2 ae                         repne           scasb   al, byte ptr es:[edi]
		*/
		size_t len = strlen(*av);
		/*
 80487c4: 89 c8                         mov     eax, ecx
 80487c6: f7 d0                         not     eax
 80487c8: 8d 50 ff                      lea     edx, [eax - 1]
 80487cb: 8b 44 24 1c                   mov     eax, dword ptr [esp + 28]
 80487cf: 8b 00                         mov     eax, dword ptr [eax]
 80487d1: 89 54 24 08                   mov     dword ptr [esp + 8], edx
 80487d5: c7 44 24 04 00 00 00 00       mov     dword ptr [esp + 4], 0
 80487dd: 89 04 24                      mov     dword ptr [esp], eax
 80487e0: e8 0b fd ff ff                call     <memset@plt>
		*/
		memset(*av, 0, len - 1);
		/*
 80487e5: 83 44 24 1c 04                add     dword ptr [esp + 28], 4
		*/
		++av;
	}

	/*
<L2>:
 8048839: 8b 44 24 18                   mov     eax, dword ptr [esp + 24]
 804883d: 8b 00                         mov     eax, dword ptr [eax]
 804883f: 85 c0                         test    eax, eax
 8048841: 75 b3                         jne      <L3>
	*/
	while (*env)
	{
		/*
<L3>:
 80487f6: 8b 44 24 18                   mov     eax, dword ptr [esp + 24]
 80487fa: 8b 00                         mov     eax, dword ptr [eax]
 80487fc: c7 44 24 14 ff ff ff ff       mov     dword ptr [esp + 20], 4294967295
 8048804: 89 c2                         mov     edx, eax
 8048806: b8 00 00 00 00                mov     eax, 0
 804880b: 8b 4c 24 14                   mov     ecx, dword ptr [esp + 20]
 804880f: 89 d7                         mov     edi, edx
 8048811: f2 ae                         repne           scasb   al, byte ptr es:[edi]
		*/
		size_t len = strlen(*env);
		/*
 8048813: 89 c8                         mov     eax, ecx
 8048815: f7 d0                         not     eax
 8048817: 8d 50 ff                      lea     edx, [eax - 1]
 804881a: 8b 44 24 18                   mov     eax, dword ptr [esp + 24]
 804881e: 8b 00                         mov     eax, dword ptr [eax]
 8048820: 89 54 24 08                   mov     dword ptr [esp + 8], edx
 8048824: c7 44 24 04 00 00 00 00       mov     dword ptr [esp + 4], 0
 804882c: 89 04 24                      mov     dword ptr [esp], eax
 804882f: e8 bc fc ff ff                call     <memset@plt>
		*/
		memset(*env, 0, len - 1);
		/*
 8048834: 83 44 24 18 04                add     dword ptr [esp + 24], 4
		*/
		++env;
	}
	/*
 8048843: c7 04 24 38 8b 04 08          mov     dword ptr [esp], 134515512
 804884a: e8 71 fc ff ff                call     <puts@plt>
	*/
	puts(
		"----------------------------------------------------\n"
		"  Welcome to wil's crappy number storage service!   \n"
		"----------------------------------------------------\n"
		" Commands:                                          \n"
		"    store - store a number into the data storage    \n"
		"    read  - read a number from the data storage     \n"
		"    quit  - exit the program                        \n"
		"----------------------------------------------------\n"
		"   wil has reserved some storage :>                 \n"
		"----------------------------------------------------\n");
	do
	{
		/*
<L10>:
 804884f: b8 4b 8d 04 08                mov     eax, 134516043
 8048854: 89 04 24                      mov     dword ptr [esp], eax
 8048857: e8 14 fc ff ff                call     <printf@plt>
		*/
		printf("Input command: ");
		/*
 804885c: c7 84 24 b4 01 00 00 01 00 00 00      mov     dword ptr [esp + 436], 1
		*/
		ret = 1;
		/*
 8048867: a1 40 a0 04 08                mov     eax, dword ptr [134520896]
 804886c: 89 44 24 08                   mov     dword ptr [esp + 8], eax
 8048870: c7 44 24 04 14 00 00 00       mov     dword ptr [esp + 4], 20
 8048878: 8d 84 24 b8 01 00 00          lea     eax, [esp + 440]
 804887f: 89 04 24                      mov     dword ptr [esp], eax
 8048882: e8 19 fc ff ff                call     <fgets@plt>
		*/
		fgets(line, 20, stdin);
		/*
 8048887: 8d 84 24 b8 01 00 00          lea     eax, [esp + 440]
 804888e: c7 44 24 14 ff ff ff ff       mov     dword ptr [esp + 20], 4294967295
 8048896: 89 c2                         mov     edx, eax
 8048898: b8 00 00 00 00                mov     eax, 0
 804889d: 8b 4c 24 14                   mov     ecx, dword ptr [esp + 20]
 80488a1: 89 d7                         mov     edi, edx
 80488a3: f2 ae                         repne           scasb   al, byte ptr es:[edi]
 80488a5: 89 c8                         mov     eax, ecx
 80488a7: f7 d0                         not     eax
 80488a9: 83 e8 01                      sub     eax, 1
 80488ac: 83 e8 01                      sub     eax, 1
 80488af: c6 84 04 b8 01 00 00 00       mov     byte ptr [esp + eax + 440], 0
		*/
		line[strlen(line) - 1] = 0; // Sub -1 instead of -2 cause repne include \0 size
		/*
 80488b7: 8d 84 24 b8 01 00 00          lea     eax, [esp + 440]
 80488be: 89 c2                         mov     edx, eax
 80488c0: b8 5b 8d 04 08                mov     eax, 134516059
 80488c5: b9 05 00 00 00                mov     ecx, 5
 80488ca: 89 d6                         mov     esi, edx
 80488cc: 89 c7                         mov     edi, eax
 80488ce: f3 a6                         rep             cmpsb   byte ptr [esi], byte ptr es:[edi]
 80488d0: 0f 97 c2                      seta    dl
 80488d3: 0f 92 c0                      setb    al
 80488d6: 89 d1                         mov     ecx, edx
 80488d8: 28 c1                         sub     cl, al
 80488da: 89 c8                         mov     eax, ecx
 80488dc: 0f be c0                      movsx   eax, al
 80488df: 85 c0                         test    eax, eax
 80488e1: 75 15                         jne      <L4>
		*/
		if (strncmp(line, "store", 5) == 0)
		{
			/*
 80488e3: 8d 44 24 24                   lea     eax, [esp + 36]
 80488e7: 89 04 24                      mov     dword ptr [esp], eax
 80488ea: e8 41 fd ff ff                call     <store_number>
 80488ef: 89 84 24 b4 01 00 00          mov     dword ptr [esp + 436], eax
 80488f6: eb 6d                         jmp      <L5>
			*/
			ret = store_number(stockage);
		}
		/*
 <L4>:
 80488f8: 8d 84 24 b8 01 00 00          lea     eax, [esp + 440]
 80488ff: 89 c2                         mov     edx, eax
 8048901: b8 61 8d 04 08                mov     eax, 134516065
 8048906: b9 04 00 00 00                mov     ecx, 4
 804890b: 89 d6                         mov     esi, edx
 804890d: 89 c7                         mov     edi, eax
 804890f: f3 a6                         rep             cmpsb   byte ptr [esi], byte ptr es:[edi]
 8048911: 0f 97 c2                      seta    dl
 8048914: 0f 92 c0                      setb    al
 8048917: 89 d1                         mov     ecx, edx
 8048919: 28 c1                         sub     cl, al
 804891b: 89 c8                         mov     eax, ecx
 804891d: 0f be c0                      movsx   eax, al
 8048920: 85 c0                         test    eax, eax
 8048922: 75 15                         jne      <L6>
		*/
		else if (strncmp(line, "read", 4) == 0)
		{
			/*
 8048924: 8d 44 24 24                   lea     eax, [esp + 36]
 8048928: 89 04 24                      mov     dword ptr [esp], eax
 804892b: e8 a7 fd ff ff                call     <read_number>
 8048930: 89 84 24 b4 01 00 00          mov     dword ptr [esp + 436], eax
 8048937: eb 2c                         jmp      <L5>
			*/
			ret = read_number(stockage);
		}
		/*
<L6>:
 8048939: 8d 84 24 b8 01 00 00          lea     eax, [esp + 440]
 8048940: 89 c2                         mov     edx, eax
 8048942: b8 66 8d 04 08                mov     eax, 134516070
 8048947: b9 04 00 00 00                mov     ecx, 4
 804894c: 89 d6                         mov     esi, edx
 804894e: 89 c7                         mov     edi, eax
 8048950: f3 a6                         rep             cmpsb   byte ptr [esi], byte ptr es:[edi]
 8048952: 0f 97 c2                      seta    dl
 8048955: 0f 92 c0                      setb    al
 8048958: 89 d1                         mov     ecx, edx
 804895a: 28 c1                         sub     cl, al
 804895c: 89 c8                         mov     eax, ecx
 804895e: 0f be c0                      movsx   eax, al
 8048961: 85 c0                         test    eax, eax
 8048963: 74 6a                         je       <L7>
			*/
		else if (strncmp(line, "quit", 4) == 0)
		{
			return 0;
		}
		/*
<L5>:
 8048965: 83 bc 24 b4 01 00 00 00       cmp     dword ptr [esp + 436], 0
 804896d: 74 1a                         je       <L8>
		*/
		if (ret != 0)
		{
			/*
 804896f: b8 6b 8d 04 08                mov     eax, 134516075
 8048974: 8d 94 24 b8 01 00 00          lea     edx, [esp + 440]
 804897b: 89 54 24 04                   mov     dword ptr [esp + 4], edx
 804897f: 89 04 24                      mov     dword ptr [esp], eax
 8048982: e8 e9 fa ff ff                call     <printf@plt>
 8048987: eb 18                         jmp      <L9>
			*/
			printf(" Failed to do %s command\n", line);
		}
		else
		{
			/*
<L8>:
 8048989: b8 88 8d 04 08                mov     eax, 134516104
 804898e: 8d 94 24 b8 01 00 00          lea     edx, [esp + 440]
 8048995: 89 54 24 04                   mov     dword ptr [esp + 4], edx
 8048999: 89 04 24                      mov     dword ptr [esp], eax
 804899c: e8 cf fa ff ff                call     <printf@plt>
			*/
			printf(" Completed %s command successfully\n", line);
		}
		/*
<L9>:
 80489a1: 8d 84 24 b8 01 00 00          lea     eax, [esp + 440]
 80489a8: c7 00 00 00 00 00             mov     dword ptr [eax], 0
 80489ae: c7 40 04 00 00 00 00          mov     dword ptr [eax + 4], 0
 80489b5: c7 40 08 00 00 00 00          mov     dword ptr [eax + 8], 0
 80489bc: c7 40 0c 00 00 00 00          mov     dword ptr [eax + 12], 0
 80489c3: c7 40 10 00 00 00 00          mov     dword ptr [eax + 16], 0
 80489ca: e9 80 fe ff ff                jmp      <L10>
		*/
		bzero(line, 20);
	} while (true);
	/*
<L7>:
 80489cf: 90                            nop
<L11>:
	*/
	return 0;
}
