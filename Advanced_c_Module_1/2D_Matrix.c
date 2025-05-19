#include <stdio.h>

int searchStaticMatrix(int matrix[][100], int n, int key) {
    int row = 0, col = n - 1;

    while (row < n && col >= 0) {
        if (matrix[row][col] == key)
            return 1;
        else if (matrix[row][col] > key)
            col--;
        else
            row++;
    }

    return 0;
}

int main() {
    int n = 4;
    int matrix[100][100] = {
        {1, 4, 7, 11},
        {2, 5, 8, 12},
        {3, 6, 9, 16},
        {10, 13, 14, 17}
    };

    int key = 6;

    if (searchStaticMatrix(matrix, n, key)) {
        printf("Key %d found in the matrix.\n", key);
    } else {
        printf("Key %d not found in the matrix.\n", key);
    }

    return 0;
}
