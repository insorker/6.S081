#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int pipefd[2], pid;

	if (pipe(pipefd) == -1) {
		fprintf(2, "pipe error");
		exit(1);
	}

	pid = fork();
	if (pid == 0) {
		read(pipefd[0], &pid, sizeof pid);
		fprintf(1, "%d: received ping\n", getpid());
		write(pipefd[1], &pid, sizeof pid);
	}
	else {
		write(pipefd[1], &pid, sizeof pid);
		wait(&pid);
		read(pipefd[0], &pid, sizeof pid);
		fprintf(1, "%d: received pong\n", getpid());
	}

	exit(0);
}
