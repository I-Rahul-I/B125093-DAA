// [MinimumCoinChange]Given an integer array of coin denominations C = {c1,c2,...,cn}
// representing coins of di!erent values, and an integer target amount V ,findtheminimum
// number of coins needed to make up that amount. You may assume an infinite supply of
// each coin denomination. If that amount of money cannot be made up by any combination
// of the coins, return -1. By choosing the proper input representation, write a program in
// C to validate your algorithm and derive the complexity analysis of your algorithm.


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int minimumCoins(int coins[], int n, int V, int chosenCoin[]) {
    int *dp = (int *)malloc((V + 1) * sizeof(int));
    for (int i = 0; i <= V; i++) {
        dp[i] = INT_MAX;
        chosenCoin[i] = -1;
    }
    dp[0] = 0;
    for (int amount = 1; amount <= V; amount++) {
        for (int j = 0; j < n; j++) {
            int coin = coins[j];
            if (coin <= amount && dp[amount - coin] != INT_MAX) {
                int currentCost = dp[amount - coin] + 1;
                if (currentCost < dp[amount]) {
                    dp[amount] = currentCost;
                    chosenCoin[amount] = coin;
                }
            }
        }
    }
    int result;
    if (dp[V] == INT_MAX) {
        result = -1;
    } else {
        result = dp[V];
    }
    free(dp);
    return result;
}
void printCombination(int chosenCoin[], int V) {
    printf("One optimal combination: ");
    while (V > 0) {
        printf("%d ", chosenCoin[V]);
        V = V - chosenCoin[V];
    }
    printf("\n");
}
int main() {
    int n, V;
    printf("Enter number of coin denominations: ");
    scanf("%d", &n);
    int *coins = (int *)malloc(n * sizeof(int));
    printf("Enter %d coin denominations:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }
    printf("Enter target amount: ");
    scanf("%d", &V);
    int *chosenCoin = (int *)malloc((V + 1) * sizeof(int));
    int result = minimumCoins(coins, n, V, chosenCoin);
    if (result == -1) {
        printf("Minimum number of coins: -1\n");
        printf("Target amount cannot be formed.\n");
    } else {
        printf("Minimum number of coins: %d\n", result);
        printCombination(chosenCoin, V);
    }
    free(coins);
    free(chosenCoin);
    return 0;
}