#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *a_user_name;

int verify_user_name(void)
{
	puts("verifying username....\n");
	return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *pass)
{
	return strncmp(pass, "admin", 5);
}

int main(void)
{
	int ret;	   // [ESP+0x5c]
	char pass[16]; // [ESP+0x1c]

	bzero(pass, 16);
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name, 256, stdin);
	ret = verify_user_name();
	if (ret == 0)
	{
		puts("Enter Password: ");
		fgets(pass, 100, stdin);
		ret = verify_user_pass(pass);
		if (ret == 0 || ret != 0)
		{
			puts("nope, incorrect password...\n");
			return 1;
		}
	}
	else
	{
		puts("nope, incorrect username...\n");
		return 1;
	}
	return 0;
}
