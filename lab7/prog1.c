// Question 1 :
// [Invert the coin-triangle] Consider an equilateral triangle formed by closely packed pen
// nies or other identical coins like the one shown in Figure 1. (The centers of the coins are
// assumed to be at the points of the equilateral triangular lattice.) Design an algorithm to
// flip the triangle upside down in the minimum number of moves if on each move you can
// slide one coin at a time to its new position. Give a compact formula for the number of
// minimum moves.

// ALGORITHM: FLIP AN EQUILATERAL COIN TRIANGLE
// Input: n, the number of coins in the last row.
// Output: Minimum number of moves required to flip the triangle upside down.
// 1. Arrange the coins in an equilateral triangular formation with n coins in the bottom row.
// 2. The number of coins in each row is: 1, 2, 3, ..., n
// 3. Calculate the total number of coins by adding the coins in all rows:
//    Total Coins = 1 + 2 + 3 + ... + n
//    Using the sum of the first n natural numbers:
//    Total Coins = n(n + 1) / 2
// 4. Consider the triangular lattice positions occupied by the coins.
// 5. Identify the positions required to form the same triangle upside down.
// 6. Keep the coins that already occupy a required position fixed.
// 7. For every remaining required position, slide one coin at a time from its current position to the empty position, following the triangular lattice.
// 8. Continue until the original triangle is completely transformed into the inverted triangle.
// 9. Calculate the total number of coins and minimum moves for n = 1 to 6:
//    n = 1  ->  Total Coins = 1 + 0 = 1    ->  Minimum Moves = 0
//    n = 2  ->  Total Coins = 1 + 2 = 3    ->  Minimum Moves = 1
//    n = 3  ->  Total Coins = 1 + 2 + 3 = 6    ->  Minimum Moves = 2
//    n = 4  ->  Total Coins = 1 + 2 + 3 + 4 = 10   ->  Minimum Moves = 3
//    n = 5  ->  Total Coins = 1 + 2 + 3 + 4 + 5 = 15   ->  Minimum Moves = 5
//    n = 6  ->  Total Coins = 1 + 2 + 3 + 4 + 5 + 6 = 21   ->  Minimum Moves = 7
// 10. From these values, the minimum number of moves follows the formula:
//     Minimum Moves = floor(n(n + 1) / 6)


// CODE---
#include <stdio.h>
int main() {
    int n;
    printf("Enter the number of balls in the last row (side length n): ");
    scanf("%d", &n);
    printf("\n--- Original Upright Pattern ---\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {
            printf(" ");
        }
        for (int k = 1; k <= i; k++) {
            printf("* ");
        }
        printf("\n");
    }
    // Apply the minimum moves mathematical inversion formula
    int min_moves = (n * (n + 1)) / 6;
    printf("\n----------------------------------------\n");
    printf("Minimum number of moves to invert: %d\n", min_moves);
    printf("----------------------------------------\n");
    printf("\n--- Inverted Target Pattern ---\n");
    for (int i = n; i >= 1; i--) {
        // Print leading spaces that increase as rows shrink
        for (int j = 1; j <= n - i; j++) {
            printf(" ");
        }
        // Print asterisks separated by spaces
        for (int k = 1; k <= i; k++) {
            printf("* ");
        }
        printf("\n");
    }
    return 0;
}