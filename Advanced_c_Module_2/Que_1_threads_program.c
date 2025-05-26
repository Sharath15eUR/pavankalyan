#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>


bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i*i <= num; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}


void* sumPrimes(void* arg) {
    int N = *(int*)arg;
    int count = 0, num = 2, sum = 0;

    while (count < N) {
        if (isPrime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    printf("Sum of first %d prime numbers: %d\n", N, sum);
    return NULL;
}


void* thread1(void* arg) {
    time_t start = time(NULL);
    while (time(NULL) - start <= 100) {
        printf("Thread 1 running\n");
        sleep(2);
    }
    return NULL;
}


void* thread2(void* arg) {
    time_t start = time(NULL);
    while (time(NULL) - start <= 100) {
        printf("Thread 2 running\n");
        sleep(3);
    }
    return NULL;
}

int main() {
    int N;
    printf("Enter value of N: ");
    scanf("%d", &N);

    pthread_t tA, tB, tC;

    pthread_create(&tA, NULL, sumPrimes, &N);
    pthread_create(&tB, NULL, thread1, NULL);
    pthread_create(&tC, NULL, thread2, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);

    return 0;
}
