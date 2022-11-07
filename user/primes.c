#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
Pipe(int *pipefd)
{
	if (pipe(pipefd) == 1) {
		fprintf(2, "pipe error");
		exit(1);
	}
}

int
main(int argc, char *argv[])
{
	int pipefd_le[2], pipefd_ri[2], p, n;

	Pipe(pipefd_ri);
	for (int n = 2; n <= 35; n++)
		write(pipefd_ri[1], &n, sizeof n);

	while (1) {
		pipefd_le[0] = pipefd_ri[0];
		close(pipefd_ri[1]);

		if (fork() == 0) {
			Pipe(pipefd_ri);

			if (!read(pipefd_le[0], &p, sizeof p))
				exit(0);
			fprintf(1, "prime %d\n", p);

			while (read(pipefd_le[0], &n, sizeof n))
				if (n % p)
					write(pipefd_ri[1], &n, sizeof n);	
		}
		else {
			wait(0);
			exit(0);
		}
	}
}
