#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[50];

    if (pipe(pipe_fd) == -1) {
        printf("Pipe creation failed.\n");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    }

    if (pid == 0) {
        close(pipe_fd[1]);
        read(pipe_fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(pipe_fd[0]);
    } else {
        close(pipe_fd[0]);
        write(pipe_fd[1], write_msg, strlen(write_msg) + 1);
        close(pipe_fd[1]);
    }

    return 0;
}
