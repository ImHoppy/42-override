#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void decrypt(int num)
{
	/*
 8048671:       31 c0                   xor    eax,eax
 8048673:       c7 45 e3 51 7d 7c 75    mov    DWORD PTR [ebp-0x1d],0x757c7d51	; str_1 "Q}|u"
 804867a:       c7 45 e7 60 73 66 67    mov    DWORD PTR [ebp-0x19],0x67667360	; str_2 "`sfg"
 8048681:       c7 45 eb 7e 73 66 7b    mov    DWORD PTR [ebp-0x15],0x7b66737e	; str_3 "~sf{"
 8048688:       c7 45 ef 7d 7c 61 33    mov    DWORD PTR [ebp-0x11],0x33617c7d	; str_4 "}|a3"
 804868f:       c6 45 f3 00             mov    BYTE PTR [ebp-0xd],0x0			; str_5 "\0"
 8048693:       50                      push   eax
 8048694:       31 c0                   xor    eax,eax
	*/
	char str[17] = "Q}|u`sfg~sf{}|a3"; // ebp-0x1d

	/*
 804869b:       58                      pop    eax
 804869c:       8d 45 e3                lea    eax,[ebp-0x1d]
 804869f:       c7 45 d4 ff ff ff ff    mov    DWORD PTR [ebp-0x2c],0xffffffff
 80486a6:       89 c2                   mov    edx,eax
 80486a8:       b8 00 00 00 00          mov    eax,0x0
 80486ad:       8b 4d d4                mov    ecx,DWORD PTR [ebp-0x2c]
 80486b0:       89 d7                   mov    edi,edx
 80486b2:       f2 ae                   repnz scas al,BYTE PTR es:[edi]
 80486b4:       89 c8                   mov    eax,ecx
 80486b6:       f7 d0                   not    eax
 80486b8:       83 e8 01                sub    eax,0x1
 80486bb:       89 45 dc                mov    DWORD PTR [ebp-0x24],eax
	*/
	int len = strlen(str); // ebp-0x24

	/*
 80486be:       c7 45 d8 00 00 00 00    mov    DWORD PTR [ebp-0x28],0x0			; i
 80486c5:       eb 1e                   jmp    80486e5 <decrypt+0x85>
 ...
 80486e5:       8b 45 d8                mov    eax,DWORD PTR [ebp-0x28]			; i
 80486e8:       3b 45 dc                cmp    eax,DWORD PTR [ebp-0x24]			; len
 80486eb:       72 da                   jb     80486c7 <decrypt+0x67>
	*/
	int i = 0; // ebp-0x28
	while (i < len)
	{
		/*
 80486c7:       8d 45 e3                lea    eax,[ebp-0x1d]
 80486ca:       03 45 d8                add    eax,DWORD PTR [ebp-0x28]
 80486cd:       0f b6 00                movzx  eax,BYTE PTR [eax]
 80486d0:       89 c2                   mov    edx,eax
 80486d2:       8b 45 08                mov    eax,DWORD PTR [ebp+0x8]
 80486d5:       31 d0                   xor    eax,edx
 80486d7:       89 c2                   mov    edx,eax
 80486d9:       8d 45 e3                lea    eax,[ebp-0x1d]
 80486dc:       03 45 d8                add    eax,DWORD PTR [ebp-0x28]
 80486df:       88 10                   mov    BYTE PTR [eax],dl
		*/
		str[i] ^= num;
		/*
 80486e1:       83 45 d8 01             add    DWORD PTR [ebp-0x28],0x1
		*/
		i++;
	}

	/*
 80486ed:       8d 45 e3                lea    eax,[ebp-0x1d]
 80486f0:       89 c2                   mov    edx,eax
 80486f2:       b8 c3 89 04 08          mov    eax,0x80489c3					; "Congratulations!"
 80486f7:       b9 11 00 00 00          mov    ecx,0x11
 80486fc:       89 d6                   mov    esi,edx
 80486fe:       89 c7                   mov    edi,eax
 8048700:       f3 a6                   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
 8048702:       0f 97 c2                seta   dl
 8048705:       0f 92 c0                setb   al
	*/
	const int cmpValue = strncmp(str, "Congratulations!", 0x11);
	/*
 804870a:       28 c1                   sub    cl,al
 804870c:       89 c8                   mov    eax,ecx
 804870e:       0f be c0                movsx  eax,al
 8048711:       85 c0                   test   eax,eax
 8048713:       75 0e                   jne    8048723 <decrypt+0xc3>
	*/
	if (cmpValue == 0)
	{
		/*
 8048715:       c7 04 24 d4 89 04 08    mov    DWORD PTR [esp],0x80489d4
 804871c:       e8 bf fd ff ff          call   80484e0 <system@plt>
		*/
		system("/bin/sh");
	}
	else
	{
		/*
 8048723:       c7 04 24 dc 89 04 08    mov    DWORD PTR [esp],0x80489dc		; "\nInvalid Password!"
 804872a:       e8 a1 fd ff ff          call   80484d0 <puts@plt>
		*/
		puts("\nInvalid Password");
	}
}

void test(int pass, int param)
{
	/*
 804874d:       8b 45 08                mov    eax,DWORD PTR [ebp+0x8]
 8048750:       8b 55 0c                mov    edx,DWORD PTR [ebp+0xc]
 8048753:       89 d1                   mov    ecx,edx
 8048755:       29 c1                   sub    ecx,eax
 8048757:       89 c8                   mov    eax,ecx
 8048759:       89 45 f4                mov    DWORD PTR [ebp-0xc],eax
	*/
	param = param - pass;
	int num = param; // ebp-0xc
	// Bitshift weird stuff check
	if (num >= 0x1 && num <= 0x9 || num >= 0x10 && num <= 0x15)
	{
		decrypt(num);
	}
	else
	{
		decrypt(rand());
	}
}

int main(void)
{
	int pass; // esp+0x1c

	srand(time(0));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &pass);
	test(pass, 322424845);
}
