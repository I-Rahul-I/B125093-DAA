/*
Question 5:
Application of sorting-V: Given a list I of n intervals, specified as (xi,yi) pairs,
return a list where the overlapping intervals are merged. For I = {(1,3),(2,6),(8,10),(7,18)}
the output should be {(1,6),(7,18)}. Your algorithm should run in worst-case
O(n·logn) time complexity. By choosing a suitable input and output representation,
write a program in C to validate your algorithm.

Algorithm:
1. Sort all intervals by their start time x_i in ascending order.
2. Sweep through the sorted intervals, maintaining a list of merged intervals:
   - For each interval [start, end]:
       - If the merged list is empty OR start > last_merged.end (no overlap):
             append [start, end] to the merged list
       - Else (overlap exists):
             update last_merged.end = max(last_merged.end, end)
3. Return the merged list.

Complexity:
- Total time: O(n log n)
- Extra space: O(n) for the merged list

Pseudocode:
Algorithm MergeIntervals(I[1..n]):
    Input:  I = list of n intervals (x_i, y_i)
    Output: merged list of non-overlapping intervals
    1. Sort I by x_i ascending
    2. Create empty list merged
    3. For each (start, end) in I:
           If merged is empty OR start > merged[last].end:
               Append (start, end) to merged
           Else:
               merged[last].end = max(merged[last].end, end)

    4. Return merged
*/

// CODE---
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int start;
    int end;
} Interval;
int cmp_interval(const void *a, const void *b) {
    const Interval *ia = a;
    const Interval *ib = b;
    return ia->start - ib->start;
}
int main(void) {
    int n;
    printf("Enter number of intervals: ");
    scanf("%d", &n);
    Interval *arr = malloc(n * sizeof(Interval));
    for (int i = 0; i < n; i++) {
        printf("Interval %d start and end: ", i + 1);
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }
    qsort(arr, n, sizeof(Interval), cmp_interval);
    Interval *merged = malloc(n * sizeof(Interval));
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (m == 0 || arr[i].start > merged[m - 1].end) {
            merged[m++] = arr[i];
        } else {
            if (arr[i].end > merged[m - 1].end) {
                merged[m - 1].end = arr[i].end;
            }
        }
    }
    printf("Merged intervals:\n");
    for (int i = 0; i < m; i++) {
        printf("(%d,%d)\n", merged[i].start, merged[i].end);
    }
    free(arr);
    free(merged);
    return 0;
}