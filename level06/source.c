#include <stdio.h>
#include <stdlib.h>

// ebp + 8 = login, ebp + 12 = serial
int auth(char *login, unsigned int serial)
{
	/*
08048748 <auth>:
 8048748: 55                            push    ebp
 8048749: 89 e5                         mov     ebp, esp
 804874b: 83 ec 28                      sub     esp, 40
 804874e: c7 44 24 04 63 8a 04 08       mov     dword ptr [esp + 4], 134515299
 8048756: 8b 45 08                      mov     eax, dword ptr [ebp + 8]
 8048759: 89 04 24                      mov     dword ptr [esp], eax
 804875c: e8 bf fd ff ff                call     <strcspn@plt>
	*/
	size_t len = strcspn(login, "\n");
	/*
 8048761: 03 45 08                      add     eax, dword ptr [ebp + 8]
 8048764: c6 00 00                      mov     byte ptr [eax], 0
	*/
	login[len] = 0;
	/*
 8048767: c7 44 24 04 20 00 00 00       mov     dword ptr [esp + 4], 32
 804876f: 8b 45 08                      mov     eax, dword ptr [ebp + 8]
 8048772: 89 04 24                      mov     dword ptr [esp], eax
 8048775: e8 56 fe ff ff                call     <strnlen@plt>
	*/
	len = strnlen(login, 32);
	/*
 804877a: 89 45 f4                      mov     dword ptr [ebp - 12], eax
 804877d: 50                            push    eax
 804877e: 31 c0                         xor     eax, eax
 8048780: 74 03                         je       <L0>
 8048782: 83 c4 04                      add     esp, 4
<L0>:
 8048785: 58                            pop     eax
 8048786: 83 7d f4 05                   cmp     dword ptr [ebp - 12], 5
 804878a: 7f 0a                         jg       <L1>
 804878c: b8 01 00 00 00                mov     eax, 1
 8048791: e9 e1 00 00 00                jmp      <L2>
<L1>:
 8048796: c7 44 24 0c 00 00 00 00       mov     dword ptr [esp + 12], 0
 804879e: c7 44 24 08 01 00 00 00       mov     dword ptr [esp + 8], 1
 80487a6: c7 44 24 04 00 00 00 00       mov     dword ptr [esp + 4], 0
 80487ae: c7 04 24 00 00 00 00          mov     dword ptr [esp], 0
 80487b5: e8 36 fe ff ff                call     <ptrace@plt>
 80487ba: 83 f8 ff                      cmp     eax, -1
 80487bd: 75 2e                         jne      <L3>
 80487bf: c7 04 24 68 8a 04 08          mov     dword ptr [esp], 134515304
 80487c6: e8 c5 fd ff ff                call     <puts@plt>
 80487cb: c7 04 24 8c 8a 04 08          mov     dword ptr [esp], 134515340
 80487d2: e8 b9 fd ff ff                call     <puts@plt>
 80487d7: c7 04 24 b0 8a 04 08          mov     dword ptr [esp], 134515376
 80487de: e8 ad fd ff ff                call     <puts@plt>
 80487e3: b8 01 00 00 00                mov     eax, 1
 80487e8: e9 8a 00 00 00                jmp      <L2>
<L3>:
 80487ed: 8b 45 08                      mov     eax, dword ptr [ebp + 8]
 80487f0: 83 c0 03                      add     eax, 3
 80487f3: 0f b6 00                      movzx   eax, byte ptr [eax]
 80487f6: 0f be c0                      movsx   eax, al
 80487f9: 35 37 13 00 00                xor     eax, 4919
 80487fe: 05 ed ed 5e 00                add     eax, 6221293
 8048803: 89 45 f0                      mov     dword ptr [ebp - 16], eax
 8048806: c7 45 ec 00 00 00 00          mov     dword ptr [ebp - 20], 0
 804880d: eb 4c                         jmp      <L4>
<L6>:
 804880f: 8b 45 ec                      mov     eax, dword ptr [ebp - 20]
 8048812: 03 45 08                      add     eax, dword ptr [ebp + 8]
 8048815: 0f b6 00                      movzx   eax, byte ptr [eax]
 8048818: 3c 1f                         cmp     al, 31
 804881a: 7f 07                         jg       <L5>
 804881c: b8 01 00 00 00                mov     eax, 1
 8048821: eb 54                         jmp      <L2>
<L5>:
 8048823: 8b 45 ec                      mov     eax, dword ptr [ebp - 20]
 8048826: 03 45 08                      add     eax, dword ptr [ebp + 8]
 8048829: 0f b6 00                      movzx   eax, byte ptr [eax]
 804882c: 0f be c0                      movsx   eax, al
 804882f: 89 c1                         mov     ecx, eax
 8048831: 33 4d f0                      xor     ecx, dword ptr [ebp - 16]
 8048834: ba 2b 3b 23 88                mov     edx, 2284010283
 8048839: 89 c8                         mov     eax, ecx
 804883b: f7 e2                         mul     edx
 804883d: 89 c8                         mov     eax, ecx
 804883f: 29 d0                         sub     eax, edx
 8048841: d1 e8                         shr     eax
 8048843: 01 d0                         add     eax, edx
 8048845: c1 e8 0a                      shr     eax, 10
 8048848: 69 c0 39 05 00 00             imul    eax, eax, 1337
 804884e: 89 ca                         mov     edx, ecx
 8048850: 29 c2                         sub     edx, eax
 8048852: 89 d0                         mov     eax, edx
 8048854: 01 45 f0                      add     dword ptr [ebp - 16], eax
 8048857: 83 45 ec 01                   add     dword ptr [ebp - 20], 1
<L4>:
 804885b: 8b 45 ec                      mov     eax, dword ptr [ebp - 20]
 804885e: 3b 45 f4                      cmp     eax, dword ptr [ebp - 12]
 8048861: 7c ac                         jl       <L6>
 8048863: 8b 45 0c                      mov     eax, dword ptr [ebp + 12]
 8048866: 3b 45 f0                      cmp     eax, dword ptr [ebp - 16]
 8048869: 74 07                         je       <L7>
 804886b: b8 01 00 00 00                mov     eax, 1
 8048870: eb 05                         jmp      <L2>
<L7>:
 8048872: b8 00 00 00 00                mov     eax, 0
<L2>:
 8048877: c9                            leave
 8048878: c3                            ret
	*/
}

int main(void)
{
	/*
08048879 <main>:
 8048879: 55                            push    ebp
 804887a: 89 e5                         mov     ebp, esp
 804887c: 83 e4 f0                      and     esp, -16
 804887f: 83 ec 50                      sub     esp, 80
 8048882: 8b 45 0c                      mov     eax, dword ptr [ebp + 12]
 8048885: 89 44 24 1c                   mov     dword ptr [esp + 28], eax
 8048889: 65 a1 14 00 00 00             mov     eax, dword ptr gs:[20]
 804888f: 89 44 24 4c                   mov     dword ptr [esp + 76], eax
 8048893: 31 c0                         xor     eax, eax
 8048895: 50                            push    eax
 8048896: 31 c0                         xor     eax, eax
 8048898: 74 03                         je       <L0>
 804889a: 83 c4 04                      add     esp, 4
	*/
	// esp+80 - esp+76 = 4
	int ret = 0; // esp+76
	// esp+76 - esp+44 = 32
	char login[32]; // esp+44
	// esp+44 - esp+40 = 4
	unsigned int serial; // esp+40
	// esp+40 - esp+36 = 4
	/*
<L0>:
 804889d: 58                            pop     eax
 804889e: c7 04 24 d4 8a 04 08          mov     dword ptr [esp], 134515412
 80488a5: e8 e6 fc ff ff                call     <puts@plt>
 80488aa: c7 04 24 f8 8a 04 08          mov     dword ptr [esp], 134515448
 80488b1: e8 da fc ff ff                call     <puts@plt>
 80488b6: c7 04 24 d4 8a 04 08          mov     dword ptr [esp], 134515412
 80488bd: e8 ce fc ff ff                call     <puts@plt>
 80488c2: b8 08 8b 04 08                mov     eax, 134515464
 80488c7: 89 04 24                      mov     dword ptr [esp], eax
 80488ca: e8 41 fc ff ff                call     <printf@plt>
 80488cf: a1 60 a0 04 08                mov     eax, dword ptr [134520928]
 80488d4: 89 44 24 08                   mov     dword ptr [esp + 8], eax
 80488d8: c7 44 24 04 20 00 00 00       mov     dword ptr [esp + 4], 32
 80488e0: 8d 44 24 2c                   lea     eax, [esp + 44]
 80488e4: 89 04 24                      mov     dword ptr [esp], eax
 80488e7: e8 64 fc ff ff                call     <fgets@plt>
 80488ec: c7 04 24 d4 8a 04 08          mov     dword ptr [esp], 134515412
 80488f3: e8 98 fc ff ff                call     <puts@plt>
 80488f8: c7 04 24 1c 8b 04 08          mov     dword ptr [esp], 134515484
 80488ff: e8 8c fc ff ff                call     <puts@plt>
 8048904: c7 04 24 d4 8a 04 08          mov     dword ptr [esp], 134515412
 804890b: e8 80 fc ff ff                call     <puts@plt>
 8048910: b8 40 8b 04 08                mov     eax, 134515520
 8048915: 89 04 24                      mov     dword ptr [esp], eax
 8048918: e8 f3 fb ff ff                call     <printf@plt>
	*/
	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(login, 32, stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	/*
 804891d: b8 60 8a 04 08                mov     eax, 134515296
 8048922: 8d 54 24 28                   lea     edx, [esp+40]
 8048926: 89 54 24 04                   mov     dword ptr [esp + 4], edx
 804892a: 89 04 24                      mov     dword ptr [esp], eax
 804892d: e8 ae fc ff ff                call     <__isoc99_scanf@plt>
	*/
	scanf("%u", &serial);
	/*
 8048932: 8b 44 24 28                   mov     eax, dword ptr [esp+40]
 8048936: 89 44 24 04                   mov     dword ptr [esp + 4], eax
 804893a: 8d 44 24 2c                   lea     eax, [esp + 44]
 804893e: 89 04 24                      mov     dword ptr [esp], eax
 8048941: e8 02 fe ff ff                call     <auth>
 8048946: 85 c0                         test    eax, eax
 8048948: 75 1f                         jne      <L1>
	*/
	if (auth(login, serial) == 0)
	{
		/*
 804894a: c7 04 24 52 8b 04 08          mov     dword ptr [esp], 134515538
 8048951: e8 3a fc ff ff                call     <puts@plt>
 8048956: c7 04 24 61 8b 04 08          mov     dword ptr [esp], 134515553
 804895d: e8 3e fc ff ff                call     <system@plt>
		*/
		puts("Authenticated!");
		system("/bin/sh");
		/*
 8048962: b8 00 00 00 00                mov     eax, 0
 8048967: eb 05                         jmp      <L2>
		*/
		return 0;
	}
	/*
<L1>:
 8048969: b8 01 00 00 00                mov     eax, 1
	*/
	return 1;
	/*
<L2>:
 804896e: 8b 54 24 4c                   mov     edx, dword ptr [esp + 76]
 8048972: 65 33 15 14 00 00 00          xor     edx, dword ptr gs:[20]
 8048979: 74 05                         je       <L3>
 804897b: e8 00 fc ff ff                call     <__stack_chk_fail@plt>
<L3>:
 8048980: c9                            leave
	*/
}
