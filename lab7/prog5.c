// Question 5 :
//  [Hitting a moving target] A computer game has a shooter and a moving target. The
// shooter can hit any of n > 1 hiding spots located along a straight line in which the target
// can hide. The shooter can never see the target; all he knows is that the target moves to
// an adjacent hiding spot between every two consecutive shots. Design an algorithm that
// guarantees hitting the target or prove that no such algorithm exists.
// If any such algorithm exists, by choosing the proper input representation, write a program
// in C to validate your algorithm and derive the complexity analysis of your algorithm.

// ALGORITHM: HIT_MOVING_TARGET(n)
// INPUT:
//     n = number of hiding spots, where n > 1
// OUTPUT:
//     A sequence of shooting positions that guarantees hitting the target
// BEGIN
//     IF n = 2 THEN
//         Shoot at position 1
//         Shoot at position 1 again
//         RETURN
//     END IF
//     // Move from left to right.
//     // Shoot at every position from 2 to n-1.
//     FOR position = 2 TO n-1 DO
//         Shoot at position
//     END FOR
//     // Move back from right to left.
//     // Shoot at every position from n-1 to 2.
//     FOR position = n-1 DOWNTO 2 DO
//         Shoot at position
//     END FOR
// END

// CODE---
#include <stdio.h>
#include <stdlib.h>
int main(){
    int n;
    printf("Enter number of hiding spots: ");
    scanf("%d", &n);
    // n must be greater than 1
    if (n <= 1){
        printf("Invalid input. n must be greater than 1.\n");
        return 0;
    }
    /*
        possible[i] = 1 means that the target
        could currently be at position i.
        possible[i] = 0 means that the target
        cannot currently be at position i. */
    int *possible = (int *)calloc(n + 1, sizeof(int));
    int *next = (int *)calloc(n + 1, sizeof(int));
    if (possible == NULL || next == NULL){
        printf("Memory allocation failed.\n");
        free(possible);
        free(next);
        return 0;
    }
    /* Initially, the target can be hiding at ANY of the n positions. */
    for (int i = 1; i <= n; i++){
        possible[i] = 1;
    }
    int totalShots;
    if (n == 2){
        totalShots = 2;
    } 
    else{
        totalShots = 2 * n - 4;
    }
    for (int shot = 1; shot <= totalShots; shot++){
        int shootPosition;
        /* Special case n = 2: Shoot at position 1 twice. */
        if (n == 2){
            shootPosition = 1;
        }
        /* First sweep: 2, 3, 4, ..., n-1 */
        else if (shot <= n - 2){
            shootPosition = shot + 1;
        }
        /* Second sweep: n-1, n-2, ..., 2 */
        else{
            shootPosition = n - 1 - (shot - (n - 2));
        }
        printf("Shot %d -> Position %d\n",shot, shootPosition);
        /*SHOOT. If the target was at shootPosition,
            it would be hit. Therefore, that possibility is removed.*/
        possible[shootPosition] = 0;
        /*Check whether any possible target position still remains.
            If none remains, then every possible target movement has been hit.*/
        int remaining = 0;
        for(int i = 1; i <= n; i++){
            if (possible[i] == 1){
                remaining = 1;
                break;
            }
        }
        if (remaining == 0){
            printf("\nTarget is guaranteed to be hit!\n");
            free(possible);
            free(next);
            return 0;
        }
        /*    TARGET MOVES
            The target must move to an adjacent position
            after every shot.
            Clear the next-state array first. */
        for (int i = 1; i <= n; i++){
            next[i] = 0;
        }
        for (int i = 1; i <= n; i++){
            if (possible[i] == 1){
                // Move one position to the left
                if (i - 1 >= 1){
                    next[i - 1] = 1;
                }
                // Move one position to the right
                if (i + 1 <= n){
                    next[i + 1] = 1;
                }
            }
        }
        for (int i = 1; i <= n; i++){
            possible[i] = next[i];
        }
    }
    free(possible);
    free(next);
    return 0;
}