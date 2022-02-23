#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static char pipe_error[] = "Pipe Error";

int
main(int argc, char *argv[])
{
	int p[2], childpid;
	char psend = 'f', ssend = 's';
	char precv, srecv;

	if (pipe(p) == -1) {
		write(1, pipe_error, sizeof(pipe_error));
		exit(-1);
	}

	childpid = fork();
	
	if (childpid == 0) {
		read(p[0], &srecv, sizeof(srecv));
		printf("%d: received ping\n", getpid());

		write(p[1], &ssend, sizeof(ssend));
	}
	else {
		write(p[1], &psend, sizeof(&psend));

		wait(0);
		read(p[0], &precv, sizeof(precv));
		printf("%d: received pong\n", getpid());
		close(p[0]);
		close(p[1]);
	}

	exit(0);
}
