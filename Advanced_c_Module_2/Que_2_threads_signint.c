#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

volatile sig_atomic_t keepRunning = 1;

BOOL WINAPI handle_ctrl_c(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        printf("\nSIGINT (Ctrl+C) received. Ignoring termination...\n");
        return TRUE; 
    }
    return FALSE;
}

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return false;
    return true;
}

void printExecutionTime(const char* threadName, DWORD start, DWORD end) {
    printf("%s execution time: %.2f seconds\n", threadName, (end - start) / 1000.0);
}


DWORD WINAPI sumPrimes(LPVOID param) {
    DWORD start = GetTickCount();
    int N = *(int*)param;
    int count = 0, num = 2, sum = 0;

    while (count < N) {
        if (isPrime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    DWORD end = GetTickCount();
    printf("Sum of first %d prime numbers: %d\n", N, sum);
    printExecutionTime("Thread A", start, end);
    return 0;
}


DWORD WINAPI thread1(LPVOID param) {
    DWORD start = GetTickCount();
    DWORD begin = GetTickCount();
    while (GetTickCount() - begin <= 100000 && keepRunning) {
        printf("Thread 1 running\n");
        Sleep(2000);
    }
    DWORD end = GetTickCount();
    printExecutionTime("Thread B", start, end);
    return 0;
}


DWORD WINAPI thread2(LPVOID param) {
    DWORD start = GetTickCount();
    DWORD begin = GetTickCount();
    while (GetTickCount() - begin <= 100000 && keepRunning) {
        printf("Thread 2 running\n");
        Sleep(3000);
    }
    DWORD end = GetTickCount();
    printExecutionTime("Thread C", start, end);
    return 0;
}

int main() {
    
    SetConsoleCtrlHandler(handle_ctrl_c, TRUE);

    int N;
    printf("Enter value of N: ");
    scanf("%d", &N);

    HANDLE hThreadA, hThreadB, hThreadC;
    DWORD threadID;

    hThreadA = CreateThread(NULL, 0, sumPrimes, &N, 0, &threadID);
    hThreadB = CreateThread(NULL, 0, thread1, NULL, 0, &threadID);
    hThreadC = CreateThread(NULL, 0, thread2, NULL, 0, &threadID);

    WaitForSingleObject(hThreadA, INFINITE);
    WaitForSingleObject(hThreadB, INFINITE);
    WaitForSingleObject(hThreadC, INFINITE);

    CloseHandle(hThreadA);
    CloseHandle(hThreadB);
    CloseHandle(hThreadC);

    printf("All threads completed.\n");
    return 0;
}
