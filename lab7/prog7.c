// Question 7:
// [Matrix Chain Multiplication (MCM) problem] Consider the matrix chain multipli
// cation problem. Write a program in C to implement the dynamic programming solution of
// the MCM problem in order to find the minimum number of scalar multiplications involved
// and the corresponding ordering to obtain the final result.

// CODE---
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Print optimal parenthesization using letters a, b, c, ...
void print_optimal_parens(int **s, int i, int j) {
    if (i == j) {
        // Print matrix name as a, b, c, ...
        printf("%c", 'a' + (i - 1));
    } else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}

void matrix_chain_order(int p[], int n) {
    // Allocate m[n+1][n+1] and s[n+1][n+1]
    int **m = (int **)malloc((n + 1) * sizeof(int *));
    int **s = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 1; i <= n; ++i) {
        m[i] = (int *)malloc((n + 1) * sizeof(int));
        s[i] = (int *)malloc((n + 1) * sizeof(int));
    }
    // Initialize diagonal
    for (int i = 1; i <= n; ++i) {
        m[i][i] = 0;
    }
    // l = chain length
    for (int l = 2; l <= n; ++l) {
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; ++k) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    printf("Minimum number of scalar multiplications: %d\n", m[1][n]);
    printf("Optimal multiplication order: ");
    print_optimal_parens(s, 1, n);
    printf("\n");
    // Free memory
    for (int i = 1; i <= n; ++i) {
        free(m[i]);
        free(s[i]);
    }
    free(m);
    free(s);
}
int main() {
    // Matrices: 
    // a: 30x35
    // b: 35x15
    // c: 15x5
    // d: 5x10
    // e: 10x20
    int p[] = {30, 35, 15, 5, 10, 20};
    int n = sizeof(p) / sizeof(p[0]) - 1; // number of matrices
    printf("Matrix Chain Multiplication (DP) Solution\n");
    printf("Matrices and dimensions:\n");
    for (int i = 0; i < n; ++i) {
        printf("  %c: %d x %d\n", 'a' + i, p[i], p[i + 1]);
    }
    printf("\n");
    matrix_chain_order(p, n);
    return 0;
}