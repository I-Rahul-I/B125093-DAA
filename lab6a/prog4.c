// QUESTION 4
// Write a program to implement Matrix Chain Multiplication using Dynamic Programming.
//  Given the dimensions of N-1 matrices in an array arr[], determine the minimum number of 
//  scalar multiplications required to multiply the complete matrix chain.


// CODE---
#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);

    int arr[100];
    int dp[100][100] = {0};

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    for (int len = 2; len < n; len++) {
        for (int i = 1; i < n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = 999999;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j]
                         + arr[i - 1] * arr[k] * arr[j];

                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }
    printf("%d", dp[1][n - 1]);
    return 0;
}