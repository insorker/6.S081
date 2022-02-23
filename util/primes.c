#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int pl[2], pr[2];

	pipe(pr);
	for (int i = 2; i <= 35; i ++ )
		write(pr[1], &i, sizeof(i));

	while (1) {
		int num = -1, prime;
		pl[0] = pr[0], close(pr[1]);

		if (fork() == 0) {
			pipe(pr);

			read(pl[0], &prime, sizeof(prime));
			printf("prime %d\n", prime);

			/* printf("num"); */
			while (read(pl[0], &num, sizeof(num))) {
				/* printf(" %d", num); */
				if (num % prime != 0)
					write(pr[1], &num, sizeof(num));
			}
			/* printf("\n"); */
			close(pl[0]);

			if (num == -1) {
				close(pr[0]);
				exit(0);
			}
		}
		else {
			wait(0);
			exit(0);
		}
	}
}
