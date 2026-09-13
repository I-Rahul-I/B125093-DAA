// Question 3:
//  Reve’s puzzle: There are eight disks of different sizes and four pegs. Initially, all the disks
// are on the first peg in order of size, the largest on the bottom and the smallest on the top.
// The objective is to transfer all the disks to another peg by a sequence of moves. Only one
// disk can be moved at a time, and it is forbidden to place a larger disk on top of a smaller
// one. Devise an algorithm that solves the puzzle in 33 moves. Generalize your algorithm for
// an n-disk problem.

// ALGORITHM:
// Recursive solution
// For n disks:
//     1. Move k disks using 4 pegs.
//     2. Move remaining n-k disks using 3 pegs.
//     3. Move k disks to destination using 4 pegs.
//
// Recurrence:
//     T(n) = min [2*T(k) + 2^(n-k) - 1]
//            for 1 <= k < n

// CODE---
#include <stdio.h>
#include <limits.h>
/* Standard 3-peg Tower of Hanoi */
long long hanoi3(int n){
    if (n == 0) return 0;
    return 2 * hanoi3(n - 1) + 1;
}
/* Recursive 4-peg Reve's Puzzle */
long long reve(int n){
    if (n == 0) return 0;
    if (n == 1) return 1;
    long long minimum = LLONG_MAX;
    /* Try every possible split */
    for (int k = 1; k < n; k++){
        long long moves = 2 * reve(k) + hanoi3(n - k);
        if (moves < minimum)  minimum = moves;
    }
return minimum;
}

int main(){
    int n;
    printf("Enter number of disks: ");
    scanf("%d", &n);
    if (n < 1){
        printf("Invalid number of disks.\n");
        return 1;
    }
    long long result = reve(n);
    printf("\nMinimum number of moves = %lld\n", result);
    return 0;
}
