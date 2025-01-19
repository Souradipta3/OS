#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int input;
    long long result;
} FactorialData;

typedef struct {
    int input;
    int result;
} ReverseData;

void *calculateFactorial(void *arg) {
    FactorialData *data = (FactorialData *)arg;
    int num = data->input;
    data->result = 1;
    for (int i = 1; i <= num; i++) {
        data->result *= i;
    }
    pthread_exit(NULL);
}

void *calculateReverse(void *arg) {
    ReverseData *data = (ReverseData *)arg;
    int num = data->input;
    data->result = 0;
    while (num > 0) {
        data->result = data->result * 10 + num % 10;
        num /= 10;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    FactorialData factData;
    ReverseData revData;

    printf("Enter a number to calculate factorial: ");
    scanf("%d", &factData.input);
    printf("Enter a number to find reverse: ");
    scanf("%d", &revData.input);

    if (pthread_create(&thread1, NULL, calculateFactorial, &factData) != 0) {
        perror("Error creating thread for factorial");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread2, NULL, calculateReverse, &revData) != 0) {
        perror("Error creating thread for reverse");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nFactorial of %d is: %lld\n", factData.input, factData.result);
    printf("Reverse of %d is: %d\n", revData.input, revData.result);

    return 0;
}