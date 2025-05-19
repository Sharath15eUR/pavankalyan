#include <stdio.h>

void rightShift(int *start, int *end) {
    int temp = *end;
    for (int *p = end; p > start; p--) {
        *p = *(p - 1);
    }
    *start = temp;
}


void rearrangeEvenOdd(int *arr, int size) {
    int *current = arr;

    for (int *i = arr; i < arr + size; i++) {
        if (*i % 2 == 0) {
            rightShift(current, i);
            current++; 
        }
    }
}

int main() {
    int arr[] = {5, 2, 8, 3, 1, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int *p = arr; p < arr + size; p++) {
        printf("%d ", *p);
    }

    rearrangeEvenOdd(arr, size);

    printf("\nRearranged array (even before odd): ");
    for (int *p = arr; p < arr + size; p++) {
        printf("%d ", *p);
    }

    return 0;
}
