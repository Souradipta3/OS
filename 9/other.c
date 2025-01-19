#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, full, empty;
int x = 0; 

void producer() {
    sem_wait(&empty); 
    sem_wait(&mutex); 

    x++; 
    printf("Producer produces the item %d\n", x);

    sem_post(&mutex); 
    sem_post(&full);  
}

void consumer() {
    sem_wait(&full); 
    sem_wait(&mutex); 

    printf("Consumer consumes the item %d\n", x);
    x--; 

    sem_post(&mutex); 
    sem_post(&empty); 
}

int main() {
    int c;

    sem_init(&mutex, 0, 1);  
    sem_init(&full, 0, 0);  
    sem_init(&empty, 0, 3);  

    printf("1.Producer\n2.Consumer\n3.Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &c);
        switch (c) {
            case 1:
                if (sem_trywait(&empty) == 0) {
                    sem_post(&empty); 
                    producer();
                } else {
                    printf("Buffer is full\n");
                }
                break;

            case 2:
                if (sem_trywait(&full) == 0) {
                    sem_post(&full); 
                    consumer();
                } else {
                    printf("Buffer is empty\n");
                }
                break;

            case 3:
                sem_destroy(&mutex);
                sem_destroy(&full);
                sem_destroy(&empty);
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
