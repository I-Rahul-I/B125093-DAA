// [Maximum Sum Increasing Subsequence] Given an array of n positive integers A =
// [a0,a1,...,an→1], find the maximum possible sum of a strictly increasing subsequence. By
// choosing the proper input representation, write a program in C to validate your
// algorithm and derive the complexity analysis of your algorithm.


#include <stdio.h>
#include <stdlib.h>
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *A = (int *)malloc(n * sizeof(int));
    int *dp = (int *)malloc(n * sizeof(int));
    int *parent = (int *)malloc(n * sizeof(int));
    int *result = (int *)malloc(n * sizeof(int));
    printf("Enter %d positive integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    /*
        dp[i] = maximum sum of an increasing subsequence
                that ends at A[i]

        parent[i] = index of the previous element selected
                    before A[i] in that subsequence
    */
    for (int i = 0; i < n; i++) {
        dp[i] = A[i];
        parent[i] = -1;
    }
    int maxSum = A[0];
    int lastIndex = 0;
    /* Find maximum sum increasing subsequence */
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i] && dp[j] + A[i] > dp[i]) {
                dp[i] = dp[j] + A[i];
                parent[i] = j;
            }
        }
        if (dp[i] > maxSum) {
            maxSum = dp[i];
            lastIndex = i;
        }
    }
    /*
        Reconstruct the subsequence.
        parent[] moves from the last element toward the first,
        so initially the result is stored in reverse order.
    */
    int count = 0;
    while (lastIndex != -1) {
        result[count] = A[lastIndex];
        count++;
        lastIndex = parent[lastIndex];
    }
    printf("\nArray: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\nMaximum sum of increasing subsequence: %d\n", maxSum);
    printf("One maximum-sum increasing subsequence: ");
    for (int i = count - 1; i >= 0; i--) {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(A);
    free(dp);
    free(parent);
    free(result);
    return 0;
}