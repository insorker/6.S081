#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int isspace(char c)
{
	switch (c) {
		case ' ':
		case '\n':
		case '\t':
			return 1;
	}

	return 0;
}

int
main(int argc, char *argv[])
{
	int idx;
	char letter, buf[512];
	char *argv_xargs[MAXARG];

	for (int i = 1; i < argc; i++)
		argv_xargs[i - 1] = argv[i];
	argv_xargs[argc - 1] = buf;
	argv_xargs[argc] = 0;

	while (read(0, &letter, sizeof(letter))) {
		buf[idx++] = letter;

		if (isspace(letter)) {
			buf[idx - 1] = '\0';
			idx = 0;
			
			if (fork() == 0) {
				exec(argv_xargs[0], argv_xargs);
				fprintf(2, "exec failed\n");
				exit(1);
			}
			else wait(0);
		}
	}

	exit(0);
}
