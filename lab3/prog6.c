// Question 6:
// Use of loop invariants in sorting: Generally, loop invariants are used to prove an
// algorithm’s correctness. To validate the proof, one must show three things about a loop
// invariant: initialisation, maintenance, and termination. Consider sorting on n numbers
// stored in an array A[1···n] by first finding the smallest element of A[1···n] and exchanging
// it with the element in A[1]. Then, find the smallest element of A[2···n], and exchange it
// with A[2]. Then, find the smallest element of A[3···n], and exchange it with A[3]. Continue
// in this manner for the first (n − 1) elements of A. Write a pseudocode for this algorithm.
// What loop invariant does this algorithm maintain? Why does it need to run for only the
// first (n −1) elements, rather than for all n elements? Give the worst-case running time of
// the above sorting algorithm in Θ-notation. Is the best-case running time any better?
// Finally, implement your algorithm in C to validate your claim.


// CODE:---
#include <stdio.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void selection_sort(int array[], int n){
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[min_index])
                min_index = j;
        }
        swap(&array[i], &array[min_index]);
    }
}
void print_array(const int array[], int n){
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);

    printf("\n");
}
int main(void){
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Array size must be positive.\n");
        return 1;
    }
    int array[n];
    printf("Enter the array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);

    selection_sort(array, n);
    printf("Sorted array:\n");
    print_array(array, n);
    return 0;
}

//Clearly selection sort has a time complexity of Θ(n^2) in both best case and worst case scenarios.