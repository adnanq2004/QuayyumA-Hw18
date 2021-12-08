#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

int main() {

	int fd[2];
	int fds[2];
	pipe(fd);
	pipe(fds);
	char line[100];

	int i = 1;
	int f = fork();

	while (i) {
		if (f) {
			close(fd[READ]);
			close(fds[WRITE]);
			printf("please give a string\n");
			fgets(line, sizeof(line), stdin);
			write(fd[WRITE], line, sizeof(line));
			read(fds[READ], line, sizeof(line));
			printf("this is the altered line: %s\n", line);
		}
		else {
			close(fd[WRITE]);
			close(fds[READ]);
			//strcpy(line, fd[READ]);
			read(fd[READ], line, sizeof(line));
			line[1] = '2';
			write(fds[WRITE], line, sizeof(line));
		}
	}
	
	return 0;
}
