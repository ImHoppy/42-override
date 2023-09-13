int get_unum(void)
{
	int tab_num [3];

	tab_num[0] = 0;
	fflush(stdout);
	__isoc99_scanf(&DAT_08048a60,tab_num);
	clear_stdin();
	return tab_num[0];
}

int auth(char *buf, uint serial)
{
	size_t len;
	int ret;
	long trace;
	int i;
	uint res;

	len = strcspn(buf,"\n");
	buf[len] = '\0';
	len = strnlen(buf,32);
	if ((int)len < 6) {
		ret = 1;
	}
	else {
		trace = ptrace(PTRACE_TRACEME);
		if (trace == -1) {
			puts("\x1b[32m.---------------------------.");
			puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
			puts("\x1b[32m\'---------------------------\'");
			ret = 1;
		}
		else {
			res = ((int)buf[3] ^ 0x1337U) + 0x5eeded;
			/* check if there is space (no needed) */
			for (i = 0; i < (int)len; i = i + 1) {
				if (buf[i] < ' ') {
					return 1;
				}
				res = res + ((int)buf[i] ^ res) % 0x539;
			}
			if (serial == res) {
				ret = 0;
			}
			else {
				ret = 1;
			}
		}
	}
	return ret;
}

bool main(int ac,char **av)
{
	int ret;
	int in_GS_OFFSET;
	uint serial;
	char buf [32];
	int local_14;

	local_14 = *(int *)(in_GS_OFFSET + 0x14);
	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(buf,32,stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	__isoc99_scanf();
	ret = auth(buf,serial);
	if (ret == 0) {
		puts("Authenticated!");
		system("/bin/sh");
	}
	if (local_14 != *(int *)(in_GS_OFFSET + 0x14)) {
		/* WARNING: Subroutine does not return */
		__stack_chk_fail();
	}
	return ret != 0;
}
