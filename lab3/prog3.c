// QUESTION 3:
// Max and Min using D&C Approach: Using the divide and conquer approach, develop
// an algorithm to find the maximum and minimum elements in an array of size n so that the
// number of comparisons will be bounded by 3n/2 . Implement your algorithm in C to validatethe result.


// CODE:---
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int minimum;
    int maximum;
} MinMax;
MinMax find_min_max(const int array[], int low, int high)
{
    MinMax result;
    MinMax left_result;
    MinMax right_result;
    if (low == high) {
        result.minimum = array[low];
        result.maximum = array[low];
        return result;
    }
    if (high == low + 1) {
        if (array[low] < array[high]) {
            result.minimum = array[low];
            result.maximum = array[high];
        } else {
            result.minimum = array[high];
            result.maximum = array[low];
        }
        return result;
    }
    int mid = low + (high - low) / 2;
    left_result = find_min_max(array, low, mid);
    right_result = find_min_max(array, mid + 1, high);
    if (left_result.minimum < right_result.minimum)
        result.minimum = left_result.minimum;
    else
        result.minimum = right_result.minimum;
    if (left_result.maximum > right_result.maximum)
        result.maximum = left_result.maximum;
    else
        result.maximum = right_result.maximum;
    return result;
}
int main(void)
{
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Array size must be positive.\n");
        return 1;
    }
    int *array = malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("Enter the array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
    MinMax result = find_min_max(array, 0, n - 1);
    printf("Minimum element: %d\n", result.minimum);
    printf("Maximum element: %d\n", result.maximum);
    free(array);
    return 0;
}