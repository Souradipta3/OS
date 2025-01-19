#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int fd[2];
	pid_t pid;
	if (pipe(fd)==-1)
	{
		perror("pipe failed.\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid<0)
	{
		perror("fork failed.\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execl("/bin/sort","sort",NULL);
		perror("execl subroutine failed.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		close(fd[1]);
		execl("/bin/ls","ls",NULL);
		perror("execl subroutine failed.\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
