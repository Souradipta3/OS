#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t rw_mutex;  
sem_t mutex;     
int read_count = 0;  

void* reader(void* arg) {
    int id = *(int*)arg; 

    sem_wait(&mutex);
    read_count++;
    if (read_count == 1) { 
        sem_wait(&rw_mutex);
    }
    sem_post(&mutex);

    printf("Reader %d is in the critical section.\n", id);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0) {  
        sem_post(&rw_mutex);
    }
    sem_post(&mutex);

    printf("Reader %d has left the critical section.\n", id);
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;  

    sem_wait(&rw_mutex);

    printf("Writer %d is in the critical section.\n", id);

    sem_post(&rw_mutex);

    printf("Writer %d has left the critical section.\n", id);
    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];
    int ids[5];

    sem_init(&rw_mutex, 0, 1);  
    sem_init(&mutex, 0, 1);     

    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
    }

    int choice, id;
    while (1) {
        printf("\n1. Reader enters\n2. Writer enters\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Reader ID (1-5): ");
                scanf("%d", &id);
                if (id >= 1 && id <= 5) {
                    pthread_create(&readers[id - 1], NULL, reader, &ids[id - 1]);
                    pthread_join(readers[id - 1], NULL);
                } else {
                    printf("Invalid Reader ID.\n");
                }
                break;

            case 2:
                printf("Enter Writer ID (1-5): ");
                scanf("%d", &id);
                if (id >= 1 && id <= 5) {
                    pthread_create(&writers[id - 1], NULL, writer, &ids[id - 1]);
                    pthread_join(writers[id - 1], NULL);
                } else {
                    printf("Invalid Writer ID.\n");
                }
                break;

            case 3:
                printf("Exiting program.\n");
                sem_destroy(&rw_mutex);
                sem_destroy(&mutex);
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
