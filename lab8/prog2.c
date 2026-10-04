// [Coin Change:Total number of ways] Given an array of distinct positive integers rep
// resenting coin denominations C = {c1,c2,...,cn} and a target amount V , find the total
// number of distinct combinations of coins that sum up to V . You may assume an infinite
// supply of each coin denomination. The order of coins does not matter (e.g., 1 + 2 and
// 2 +1 are considered the same combination). By choosing the proper input representation,
// write a program in C to validate your algorithm and derive the complexity analysis of
// algorithm.


#include <stdio.h>
#include <stdlib.h>
long long countCombinations(int coins[], int n, int V) {
    long long *dp = (long long *)calloc(V + 1, sizeof(long long));
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int amount = coins[i]; amount <= V; amount++) {
            dp[amount] = dp[amount] + dp[amount - coins[i]];
        }
    }
    long long result = dp[V];
    free(dp);
    return result;
}
int main() {
    int n, V;
    printf("Enter number of coin denominations: ");
    scanf("%d", &n);
    int *coins = (int *)malloc(n * sizeof(int));
    printf("Enter %d distinct coin denominations:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }
    printf("Enter target amount: ");
    scanf("%d", &V);
    long long ways = countCombinations(coins, n, V);
    printf("\nCoin denominations: { ");
    for (int i = 0; i < n; i++) {
        printf("%d", coins[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf(" }\n");
    printf("Target amount: %d\n", V);
    printf("Total distinct combinations: %lld\n", ways);
    free(coins);
    return 0;
}