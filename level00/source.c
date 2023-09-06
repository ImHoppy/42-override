#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int buffer;

	puts("***********************************");
	puts("* 	     -Level00 -		  *");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &buffer);
	if (buffer != 5276)
	{
		puts("\nInvalid Password!");
	}
	else
	{
		puts("\nAuthenticated!");
		system("/bin/sh");
	}
	return buffer != 5276;
}
