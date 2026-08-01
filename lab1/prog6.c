#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int hasDuplicate(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int n;
    printf("Enter number of random elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand((unsigned)time(NULL));

    printf("Generated numbers:\n");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
        printf("%d ", arr[i]);
    }
    printf("\n");

    if (hasDuplicate(arr, n)) {
        printf("Duplicates found.\n");
    } else {
        printf("No duplicates found.\n");
    }

    free(arr);
    return 0;
}