// QUESTION 1:
// Write a program to find the nth Fibonacci number using Dynamic Programming.


// CODE---
#include <stdio.h>

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Invalid input");
        return 0;
    }
    if (n == 0) {
        printf("0");
        return 0;
    }
    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    printf("The %dth Fibonacci number is: %d", n, dp[n]);
    return 0;
}
