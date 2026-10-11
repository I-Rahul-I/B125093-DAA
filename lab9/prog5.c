// Question 5:
//  [Candy Distribution Problem (Bi-directional Slope Greedy)] n children stand in a
// line, each assigned a rating. Each child must get at least one candy. Children with a 
// higher rating than their immediate neighbours must get more candies than their 
// neighbours. Find the minimum total number of candies needed. By choosing the proper
// input representation, write a program in C to validate your algorithm and derive the 
// complexity  analysis of your algorithm.

#include <stdio.h>
#include <stdlib.h>
int main() {
    int n;
    printf("Enter number of children: ");
    scanf("%d", &n);
    int *rating = (int *)malloc(n * sizeof(int));
    int *candy = (int *)malloc(n * sizeof(int));
    printf("Enter %d ratings:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &rating[i]);
    }
    /* Every child gets at least one candy */
    for (int i = 0; i < n; i++) {
        candy[i] = 1;
    }
    /* Left-to-right pass */
    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1]) {
            candy[i] = candy[i - 1] + 1;
        }
    }
    /* Right-to-left pass */
    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1]) {
            if (candy[i] < candy[i + 1] + 1) {
                candy[i] = candy[i + 1] + 1;
            }
        }
    }
    long long totalCandies = 0;
    for (int i = 0; i < n; i++) totalCandies += candy[i];
    printf("\nRatings: ");
    for (int i = 0; i < n; i++) printf("%d ", rating[i]);
    printf("\nCandy distribution: ");
    for (int i = 0; i < n; i++) printf("%d ", candy[i]);
    printf("\nMinimum total candies: %lld\n", totalCandies);
    free(rating);
    free(candy);
    return 0;
}
// Complexity Analysis: Time Complexity: O(n) for two passes through the ratings
// Space Complexity: O(n) for the candy array