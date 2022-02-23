#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
	char *args[MAXARG], *p;
	int args_idx = 0;
	
	for (int i = 1; i < argc; i ++ ) {
		args[args_idx] = (char *)malloc(sizeof(argv[i]));
		memmove(args[args_idx], argv[i], sizeof(argv[i]));
		args_idx ++ ;
	}

	args[args_idx] = (char *)malloc(512 * sizeof(char));
	p = args[args_idx ++ ];
	while (read(0, p, sizeof(char))) {
		if (*p == ' ' || *p == '\n') {
			*p = 0;
			if (*p == '\n')
				break;
			args[args_idx] = (char *)malloc(512 * sizeof(char));
			p = args[args_idx ++ ];
		}
		else p ++ ;
	}

	/* for (int i = 0; i < args_idx; i ++ ) */
	/*     printf("%s\n", args[i]); */

	exec(args[0], args);

	exit(0);
}
