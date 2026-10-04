// [Rod Cutting with Reconstruction] Given a rod of length n inches and an array of
// prices P =[p1,p2,...,pn], where pi denotes the market price of a rod piece of length i
// inches, determine:
// (i) The maximum revenue obtainable by cutting up the rod and selling the pieces.
// (ii) The exact lengths of the pieces that constitute the optimal decomposition 
// (reconstruction). Cuts are integral and can be made in any combination (including 
// leaving the rod uncut),and the sum of the piece lengths must equal n. By choosing the
// proper input representation, write a program in C to validate your algorithm and derive
// the complexity analysis of your algorithm.


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main() {
    int n;
    printf("Enter rod length: ");
    scanf("%d", &n);
    int *price = (int *)malloc((n + 1) * sizeof(int));
    int *revenue = (int *)malloc((n + 1) * sizeof(int));
    int *firstCut = (int *)malloc((n + 1) * sizeof(int));
    printf("Enter prices for pieces of length 1 to %d:\n", n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);}
    //revenue[L] = maximum revenue obtainable from a rod of length L
    //firstCut[L] = first piece length in an optimal decomposition of L
    revenue[0] = 0;
    firstCut[0] = 0;
    for (int length = 1; length <= n; length++) {
        revenue[length] = INT_MIN;
        for (int pieceLength = 1; pieceLength <= length; pieceLength++) {
            int currentRevenue = price[pieceLength]
                               + revenue[length - pieceLength];
            if (currentRevenue > revenue[length]) {
                revenue[length] = currentRevenue;
                firstCut[length] = pieceLength;
            }
        }
    }
    printf("\nMaximum revenue: %d\n", revenue[n]);
    printf("Optimal piece lengths: ");
    int remainingLength = n;
    while (remainingLength > 0) {
        printf("%d ", firstCut[remainingLength]);
        remainingLength = remainingLength - firstCut[remainingLength];}
    printf("\n");
    free(price);
    free(revenue);
    free(firstCut);
    return 0;
}