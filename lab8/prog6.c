// [Edit Distance with Traceback Information] Given two strings A of length m and B
// of length n, compute the minimum number of operations (insertions, deletions, or substi
// tutions) required to transform A into B, and print the traceback result. By choosing 
// the proper input representation, write a program in C to validate your algorithm and 
// derive the complexity analysis of your algorithm


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int min3(int a, int b, int c) {
    int minimum = a;
    if (b < minimum) {
        minimum = b;
    }
    if (c < minimum) {
        minimum = c;
    }
    return minimum;
}
void printDPTable(int **dp, char A[], char B[], int m, int n) {
    printf("\nDP Table:\n\n");
    printf("      ");
    for (int j = 0; j <= n; j++) {
        if (j == 0) {
            printf("  - ");
        } else {
            printf("  %c ", B[j - 1]);
        }
    }
    printf("\n");
    for (int i = 0; i <= m; i++) {
        if (i == 0) {
            printf("  - ");
        } else {
            printf("  %c ", A[i - 1]);
        }
        for (int j = 0; j <= n; j++) {
            printf("%3d ", dp[i][j]);
        }
        printf("\n");
    }
}
void printTraceback(int **dp, char A[], char B[], int m, int n) {
    int maxSteps = m + n;
    char **steps = (char **)malloc(maxSteps * sizeof(char *));
    for (int i = 0; i < maxSteps; i++) {
        steps[i] = (char *)malloc(100 * sizeof(char));
    }
    int count = 0;
    int i = m;
    int j = n;
    /*
        Start from dp[m][n] and move toward dp[0][0].
        Up       : deletion from A
        Left     : insertion into A
        Diagonal : match or substitution
    */
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1]) {
            sprintf(steps[count], "Match '%c' (no operation)", A[i - 1]);
            i--;
            j--;
        } else if (i > 0 && j > 0 &&
                   dp[i][j] == dp[i - 1][j - 1] + 1) {
            sprintf(steps[count], "Substitute '%c' with '%c'",
                    A[i - 1], B[j - 1]);
            i--;
            j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            sprintf(steps[count], "Delete '%c'", A[i - 1]);
            i--;
        } else {
            sprintf(steps[count], "Insert '%c'", B[j - 1]);
            j--;
        }
        count++;
    }
    printf("\nTraceback / one optimal transformation:\n");
    /*
        Traceback was collected backward, so print it backward.
        Matches are included to show alignment but do not add to edit count.
    */
    for (int k = count - 1; k >= 0; k--) {
        printf("%s\n", steps[k]);
    }
    for (int k = 0; k < maxSteps; k++) {
        free(steps[k]);
    }
    free(steps);
}
int main() {
    char A[200];
    char B[200];
    printf("Enter string A: ");
    scanf("%199s", A);
    printf("Enter string B: ");
    scanf("%199s", B);
    int m = strlen(A);
    int n = strlen(B);
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }
    /* Base cases */
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    /* Fill the DP table */
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                int deletion = dp[i - 1][j] + 1;
                int insertion = dp[i][j - 1] + 1;
                int substitution = dp[i - 1][j - 1] + 1;

                dp[i][j] = min3(deletion, insertion, substitution);
            }
        }
    }
    printf("\nString A: %s\n", A);
    printf("String B: %s\n", B);
    printf("Minimum number of operations: %d\n", dp[m][n]);
    printDPTable(dp, A, B, m, n);
    printTraceback(dp, A, B, m, n);
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    return 0;
}