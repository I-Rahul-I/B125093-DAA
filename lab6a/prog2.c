// QUESTION 2:
// Implement the 0/1 Knapsack problem using Dynamic Programming. Given n items with their weights and profits 
// and a knapsack of capacity W, determine the maximum profit that can be obtained. 
// Analyze the time and space complexity of your algorithm.

// CODE---
#include <stdio.h>
int main() {
    int n, W;
    scanf("%d", &n);
    int weight[100], profit[100];
    for (int i = 0; i < n; i++)
        scanf("%d", &weight[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &profit[i]);
        
    scanf("%d", &W);

    int dp[100][100] = {0};

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {

         if (weight[i - 1] <= w) {
                int include = profit[i - 1] +
                  dp[i - 1][w - weight[i - 1]];
                int exclude = dp[i - 1][w];
                if (include > exclude)
                    dp[i][w] = include;
                else
                    dp[i][w] = exclude;
            }
         else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    printf("%d", dp[n][W]);
    return 0;
}