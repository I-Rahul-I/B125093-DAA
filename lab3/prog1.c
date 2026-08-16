// QUESTION 1:
// Binary vs Ternary Search: In binary search, an n element list is divided into nearly two
// equal halves, while in ternary search, it is divided into nearly three equal intervals.
// Then the search will be in one of the intervals. Design and implement a C program to 
// search for an element x in a sorted list of size n using binary and ternary search. 
// Justify and validate that binary search is better than ternary search via your 
// implementation.


// CODE:---
#include <stdio.h>
#include <stdlib.h>

int binarySearch_steps = 0;
int ternarySearch_steps = 0;

int binarySearch(const int arr[], int left, int right, int x){
    binarySearch_steps+=2;
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == x)
        return mid;
    if (x < arr[mid])
        return binarySearch(arr, left, mid - 1, x);
    return binarySearch(arr, mid + 1, right, x);
}
int ternarySearch(const int arr[], int left, int right, int x){
    ternarySearch_steps+=4;
    if (left > right) return -1;
    int third = (right - left) / 3;
    int mid1 = left + third;
    int mid2 = right - third;
    if (arr[mid1] == x)
        return mid1;
    if (arr[mid2] == x)
        return mid2;
    if (x < arr[mid1])
        return ternarySearch(arr, left, mid1 - 1, x);
    if (x > arr[mid2])
        return ternarySearch(arr, mid2 + 1, right, x);
    return ternarySearch(arr, mid1 + 1, mid2 - 1, x);
}
int main(void){
    int n;
    int search_element;
    printf("Enter the size of the sorted array: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Array size must be positive.\n");
        return 1;
    }
    int *array = (int*)malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("Enter %d elements in sorted order:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
    printf("Enter the element to search: ");
    scanf("%d", &search_element);
    int binary_result = binarySearch(array,0,n - 1,search_element);
    int ternary_result = ternarySearch(array,0,n - 1,search_element);
    printf("\n");

    if (binary_result != -1)
        printf("Binary search found the element at index %d.\n",binary_result);
    else
        printf("Binary search did not find the element.\n");
    printf("Binary search steps: %d\n", binarySearch_steps);
    printf("\n");

    if (ternary_result != -1)
        printf("Ternary search found the element at index %d.\n",ternary_result);
    else
        printf("Ternary search did not find the element.\n");
    printf("Ternary search steps: %d\n", ternarySearch_steps);
    printf("\n");
    
    if (binarySearch_steps < ternarySearch_steps) {
        printf("Binary search is better for this input.\n");
    } else if (ternarySearch_steps > binarySearch_steps) {
        printf("Ternary search is better for this input.\n");
    } else {
        printf("Both searches took the same number of steps.\n");
    }

    printf("\nIn general, binary search is preferred because its time "
           "complexity is O(log2 n), while ternary search is O(log3 n), "
           "and binary search performs fewer comparisons per step.\n");

    free(array);
    return 0;
}