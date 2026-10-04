// [Longest Increasing Subsequence] Given an integer array A =[a0,a1,...,an→1], find
// the length of the longest subsequence such that all elements of the subsequence are
// strictly increasing. By choosing the proper input representation, write a program in
// C to validate your algorithm and derive the complexity analysis of your algorithm.


#include <stdio.h>
#include <stdlib.h>
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *A = (int *)malloc(n * sizeof(int));
    int *dp = (int *)malloc(n * sizeof(int));
    int *parent = (int *)malloc(n * sizeof(int));
    int *lis = (int *)malloc(n * sizeof(int));
    printf("Enter %d array elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    /*
        dp[i] = length of LIS ending at A[i]
        parent[i] = previous index used before A[i] in that LIS
    */
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        parent[i] = -1;
    }
    int maxLength = 1;
    int lastIndex = 0;
    /* Fill the DP array */
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > maxLength) {
            maxLength = dp[i];
            lastIndex = i;
        }
    }
    /*
        Reconstruct LIS by moving backward through parent[].
        The sequence is first obtained in reverse order.
    */
    int index = maxLength - 1;
    while (lastIndex != -1) {
        lis[index] = A[lastIndex];
        index--;
        lastIndex = parent[lastIndex];
    }
    printf("\nArray: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\nLength of LIS: %d\n", maxLength);
    printf("One Longest Increasing Subsequence: ");
    for (int i = 0; i < maxLength; i++) {
        printf("%d ", lis[i]);
    }
    printf("\n");
    free(A);
    free(dp);
    free(parent);
    free(lis);
    return 0;
}