#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static char sleep_error[] = "Sleep Error: No Input";

int
main(int argc, char *argv[])
{
	if (argc == 1) {
		write(1, sleep_error, strlen(sleep_error));
		exit(1);
	}

	sleep(atoi(argv[1]));

	exit(0);
}
