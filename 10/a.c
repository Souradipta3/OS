#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t write_lock;
pthread_mutex_t mutex;
int reader_count = 0;

void *reader(void *arg) {
    int id = *((int *)arg);

    pthread_mutex_lock(&mutex);
    reader_count++;
    if (reader_count == 1) {
        sem_wait(&write_lock);
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d is reading.\n", id);
    sleep(1);

    pthread_mutex_lock(&mutex);
    reader_count--;
    if (reader_count == 0) {
        sem_post(&write_lock);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);

    sem_wait(&write_lock);
    printf("Writer %d is writing.\n", id);
    sleep(2);
    sem_post(&write_lock);

    return NULL;
}

int main() {
    int num_readers, num_writers;

    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);

    pthread_t readers[num_readers], writers[num_writers];
    int ids[num_readers > num_writers ? num_readers : num_writers];

    sem_init(&write_lock, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < num_readers; i++) {
        ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    for (int i = 0; i < num_writers; i++) {
        ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&write_lock);
    pthread_mutex_destroy(&mutex);

    return 0;
}
