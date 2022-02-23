#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define ALERT(x) printf("wrong => %d\n", x)

char*
fmtname(char *path)
{
	char *p;

	for (p = path + strlen(path); p >= path && *p != '/'; p -- )
		;
	p ++ ;

	return p;
}

void
find(char *path, char *file)
{
	char buf[512], *p;
	int fd;
	struct stat st;
	struct dirent de;

	if ((fd = open(path, 0)) < 0) {
		ALERT(3); return;
	}

	if (fstat(fd, &st) < 0) {
		ALERT(4); close(fd); return;
	}

	switch (st.type) {
		case T_FILE:
			if (strcmp(fmtname(path), file) == 0)
				printf("%s\n", path);
			break;
		case T_DIR:
			strcpy(buf, path);
			p = buf + strlen(buf);
			*p++ = '/';

			while (read(fd, &de, sizeof(de)) == sizeof(de)) {
				if (de.inum == 0)
					continue;
				memmove(p, de.name, DIRSIZ);
				if (strcmp(de.name, ".") == 0)
					continue;
				else if (strcmp(de.name, "..") == 0)
					continue;
				p[DIRSIZ] = 0;

				find(buf, file);
			}

			break;
	}

	close(fd);
}

int
main(int argc, char *argv[])
{
	if (argc < 3) {
		ALERT(0);
		exit(1);
	}

	for (int i = 2; i < argc; i ++ )
		find(argv[1], argv[i]);

	exit(0);
}
