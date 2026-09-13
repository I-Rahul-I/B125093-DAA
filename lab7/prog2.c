// Question 2:
// [Super egg testing experiment] A firm has invented a super-strong egg. For publicity
// purposes, it wants to determine the highest floor in a 100-storey building from which such an
// egg can fall without breaking. The firm has given a tester two identical eggs to experiment
// with. Of course, the same egg can be dropped multiple times unless it breaks. What is the
// minimum number of droppings that is guaranteed to determine the highest safe floor in all
// cases? Design a dynamic programming generalized solution for E eggs and F floors.


#include <stdio.h>
#include <limits.h>
// Helper function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}
// Function to calculate the minimum drops using Dynamic Programming
int eggDrop(int e, int f) {
    // dp[i][j] represents the minimum drops needed for i eggs and j floors
    int dp[e + 1][f + 1];
    int i, j, k, res;
    // Base cases: 1 drop for 1 floor, 0 drops for 0 floors
    for (i = 1; i <= e; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }
    // Base case: If we only have 1 egg, we need j drops for j floors
    for (j = 1; j <= f; j++) {
        dp[1][j] = j;
    }
    // Fill the rest of the DP table bottom-up
    for (i = 2; i <= e; i++) {
        for (j = 2; j <= f; j++) {
            dp[i][j] = INT_MAX;
            // Test dropping from all floors from 1 to j
            for (k = 1; k <= j; k++) {
                res = 1 + max(dp[i - 1][k - 1], dp[i][j - k]);
                if (res < dp[i][j]) {
                    dp[i][j] = res;
                }
            }
        }
    }
    // Return the result for E eggs and F floors
    return dp[e][f];
}
int main() {
    int eggs = 5;
    int floors = 90;
    printf("Minimum number of droppings required with %d eggs and %d floors is: %d\n",eggs, floors, eggDrop(eggs, floors));          
    return 0;
}