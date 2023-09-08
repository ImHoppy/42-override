#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	size_t len;
	long lVar3;
	char password[112] = {0};
	char flag_buffer[48] = {0};
	char username[96] = {0};
	int readed;
	FILE *pass_file = NULL;

	readed = 0;
	pass_file = fopen("/home/users/level03/.pass", "r");
	if (pass_file == NULL)
	{
		fwrite("ERROR: failed to open password file\n", 1, 0x24, stderr);
		exit(1);
	}
	readed = fread(flag_buffer, 1, 41, pass_file);
	len = strcspn((char *)flag_buffer, "\n");
	flag_buffer[len] = 0;
	if (readed != 41)
	{
		fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
		exit(1);
	}
	fclose(pass_file);
	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	printf("--[ Username: ");
	fgets((char *)username, 100, stdin);
	len = strcspn((char *)username, "\n");
	username[len] = 0;
	printf("--[ Password: ");
	fgets((char *)password, 100, stdin);
	len = strcspn((char *)password, "\n");
	password[len] = 0;
	puts("*****************************************");
	int good_password = strncmp((char *)flag_buffer, (char *)password, 41);
	if (good_password == 0)
	{
		printf("Greetings, %s!\n", username);
		system("/bin/sh");
		return 0;
	}
	printf((char *)username);
	puts(" does not have access!");
	exit(1);
}
