#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

volatile sig_atomic_t keepRunning = 1;

// Signal handler for Ctrl+C
void handle_sigint(int sig) {
    printf("\nSIGINT (Ctrl+C) received. Ignoring termination...\n");
    keepRunning = 0;
}

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return false;
    return true;
}

void printExecutionTime(const char* threadName, time_t start, time_t end) {
    printf("%s execution time: %.2f seconds\n", threadName, difftime(end, start));
}

void* sumPrimes(void* param) {
    time_t start = time(NULL);
    int N = *(int*)param;
    int count = 0, num = 2, sum = 0;

    while (count < N) {
        if (isPrime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    time_t end = time(NULL);
    printf("Sum of first %d prime numbers: %d\n", N, sum);
    printExecutionTime("Thread A", start, end);
    return NULL;
}

void* thread1(void* param) {
    time_t start = time(NULL);
    time_t begin = time(NULL);
    while (difftime(time(NULL), begin) <= 100 && keepRunning) {
        printf("Thread 1 running\n");
        sleep(2);
    }
    time_t end = time(NULL);
    printExecutionTime("Thread B", start, end);
    return NULL;
}

void* thread2(void* param) {
    time_t start = time(NULL);
    time_t begin = time(NULL);
    while (difftime(time(NULL), begin) <= 100 && keepRunning) {
        printf("Thread 2 running\n");
        sleep(3);
    }
    time_t end = time(NULL);
    printExecutionTime("Thread C", start, end);
    return NULL;
}

int main() {
    signal(SIGINT, handle_sigint);  // Register signal handler

    int N;
    printf("Enter value of N: ");
    scanf("%d", &N);

    pthread_t threadA, threadB, threadC;

    pthread_create(&threadA, NULL, sumPrimes, &N);
    pthread_create(&threadB, NULL, thread1, NULL);
    pthread_create(&threadC, NULL, thread2, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    printf("All threads completed.\n");
    return 0;
}
