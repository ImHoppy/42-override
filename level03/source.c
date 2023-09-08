void decrypt(int)
{
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
	if (num > 21)
	{
		decrypt(rand());
	}
	else
	{
		decrypt(num);
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
