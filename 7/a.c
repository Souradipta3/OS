#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
    printf("New thread: Thread ID = %lu, Process ID = %d\n", pthread_self(), getpid());
    return NULL;
}

int main() {
    pthread_t thread;

    // Create a new thread
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        printf("Failed to create thread.\n");
        return 1;
    }

    // Print main thread details
    printf("Main thread: Thread ID = %lu, Process ID = %d\n", pthread_self(), getpid());

    // Wait for the new thread to complete
    pthread_join(thread, NULL);

    return 0;
}