#include <stdio.h>
#include <pthread.h>

int factorial_result = 1, reverse_result = 0;
int number; 

void *calculate_factorial(void *arg) {
    int n = *((int *)arg);
    factorial_result = 1;
    for (int i = 1; i <= n; i++) {
        factorial_result *= i;
    }
    pthread_exit(0);
}

void *calculate_reverse(void *arg) {
    int n = *((int *)arg);
    reverse_result = 0;
    while (n > 0) {
        reverse_result = reverse_result * 10 + (n % 10);
        n /= 10;
    }
    pthread_exit(0);
}

int main() {
    pthread_t thread1, thread2;

    printf("Enter a number: ");
    scanf("%d", &number);

    pthread_create(&thread1, NULL, calculate_factorial, &number);
    pthread_create(&thread2, NULL, calculate_reverse, &number);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Factorial of %d is %d\n", number, factorial_result);
    printf("Reverse of %d is %d\n", number, reverse_result);

    return 0;
}
