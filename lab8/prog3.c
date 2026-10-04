// [Longest Common Subsequence (LCS)] Given two sequences X = ↑x1,x2,...,xm↓
// and Y = ↑y1,y2,...,yn↓, compute the length of their longest common subsequence and
// reconstruct the actual subsequence string. By choosing the proper input representation,
// write a program in C to validate your algorithm and derive the complexity analysis of
// algorithm


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}
int main() {
    char X[200];
    char Y[200];
    printf("Enter first sequence X: ");
    scanf("%199s", X);
    printf("Enter second sequence Y: ");
    scanf("%199s", Y);
    int m = strlen(X);
    int n = strlen(Y);
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }
    /* Initialize first row and first column */
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }
    /* Fill the DP table */
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int lcsLength = dp[m][n];
    /* Create a string to store the LCS */
    char *lcs = (char *)malloc((lcsLength + 1) * sizeof(char));
    lcs[lcsLength] = '\0';
    /*
        Trace backward through dp[][].
        Fill lcs from right to left because backtracking starts at the end.
    */
    int i = m;
    int j = n;
    int index = lcsLength - 1;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    printf("\nFirst sequence:  %s\n", X);
    printf("Second sequence: %s\n", Y);
    printf("Length of LCS: %d\n", lcsLength);
    printf("One LCS string: %s\n", lcs);
    free(lcs);
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    return 0;
}