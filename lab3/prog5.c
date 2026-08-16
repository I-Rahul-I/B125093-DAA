// QUESTION 5:
// Multiply special-pattern square matrices using D&C approach: Two n×n matrices
// are provided to you, where n = 2^k for some natural number k. Each matrix has the recursive
// structure described as: when divided into four equal-sized blocks, two diagonal blocks are
// identical, and two off-diagonal blocks are identical, i.e. the structure of the matrices would
// be:
// M= 
// M1 M2
// M2 M1
// Each block has a recursive structure that goes down to single integer elements. Give a
// divide-and-conquer approach-based O(n2) algorithm for multiplying two such matrices and
// validate the complexity of your algorithm


// CODE:---
#include <stdio.h>
#include <stdlib.h>
void add(int n,int A[n][n],int B[n][n],int C[n][n]){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    }
}

void special_multiply(int n,int A[n][n],int B[n][n],int C[n][n]){
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;

    int A1[half][half];
    int A2[half][half];
    int B1[half][half];
    int B2[half][half];

    int P1[half][half];
    int P2[half][half];
    int P3[half][half];
    int P4[half][half];

    int X[half][half];
    int Y[half][half];

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + half];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + half];
        }
    }

    special_multiply(half, A1, B1, P1);
    special_multiply(half, A2, B2, P2);

    special_multiply(half, A1, B2, P3);
    special_multiply(half, A2, B1, P4);

    add(half, P1, P2, X);
    add(half, P3, P4, Y);
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = X[i][j];
            C[i][j + half] = Y[i][j];
            C[i + half][j] = Y[i][j];
            C[i + half][j + half] = X[i][j];
        }
    }
}
int main(void){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    if (n < 1 || (n & (n - 1)) != 0) {
        printf("n must be a positive power of two.\n");
        return 1;
    }
    int A[n][n];
    int B[n][n];
    int C[n][n];
    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    }
    printf("Enter matrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);
    }
    special_multiply(n, A, B, C);
    printf("Product matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);

        printf("\n");
    }
    return 0;
}