#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

sem_t sem;
char input[100];

void *count_characters(void *arg) {
    sem_wait(&sem);
    int length = strlen(input);
    printf("Child thread: Number of characters = %d\n", length);
    sem_post(&sem);
    return NULL;
}

int main() {
    pthread_t thread;

    sem_init(&sem, 0, 0);

    pthread_create(&thread, NULL, count_characters, NULL);

    printf("Main thread: Enter a string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    sem_post(&sem);

    pthread_join(thread, NULL);

    sem_destroy(&sem);

    return 0;
}