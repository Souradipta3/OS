#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    }

    if (pid == 0) {
        printf("Executing 'ls' command in the child process:\n");
        execlp("ls", "ls", NULL);
    } else {
        wait(NULL);
        printf("Child process has completed.\n");
    }

    return 0;
}