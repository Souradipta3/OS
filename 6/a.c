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
        // Child process
        close(pipe_fd[1]); // Close unused write end
        read(pipe_fd[0], read_msg, sizeof(read_msg)); // Read from pipe
        printf("Child received: %s\n", read_msg);
        close(pipe_fd[0]);
    } else {
        // Parent process
        close(pipe_fd[0]); // Close unused read end
        write(pipe_fd[1], write_msg, strlen(write_msg) + 1); // Write to pipe
        close(pipe_fd[1]);
    }

    return 0;
}
