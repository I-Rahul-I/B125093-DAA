// Question 4 :
//  [Security switches] There is a row of n security switches protecting a military installation
// entrance. The switches can be manipulated as follows:
// (i) The rightmost switch may be turned on or off at will.
// (ii) Any other switch may be turned on or off only if the switch to its immediate right is
// on and all the other switches to its right, if any, are off.
// (iii) Only one switch may be toggled at a time.
// Devise an algorithm to turn off all the switches, which are initially all on, in the minimum
// number of moves. (Toggling one switch is considered one move.)

// Algorithm SecuritySwitches(start, n)
// Input:
//     start = starting position of the group of switches
//     n     = number of switches in the group
// Output:
//     All n switches are turned OFF using the minimum number of moves
// 1. If n = 1:
//        Toggle the only switch.
//        Return.
// 2. If n = 2:
//        Toggle the first switch.
//        Toggle the second switch.
//        Return.
// 3. Otherwise:
//        // Step 1:
//        // First solve the last n-2 switches.
//        // This prepares the switches so that the first
//        // switch can legally be toggled.
//        Call SecuritySwitches(start + 2, n - 2)
//        // Step 2:
//        // Toggle the first switch.
//        Toggle switch at position start.
//        // Step 3:
//        // Reverse the moves made in Step 1.
//        // This turns those n-2 switches back ON,
//        // putting the remaining switches into the required state.
//        Call ReverseSecuritySwitches(start + 2, n - 2)
//        // Step 4:
//        // Finally solve the remaining n-1 switches.
//        Call SecuritySwitches(start + 1, n - 1)
// End Algorithm

// CODE---
#include <stdio.h>
int switches[20];
int moves = 0;
void undo(int start, int n, int total);
void toggle(int pos, int n){
    /* Toggle the switch */
    switches[pos] = !switches[pos];
    /* One toggle = one move */
    moves++;
    /* Display the move */
    printf("Move %d: Toggle switch %d -> ",moves, pos + 1);
    /* Display current switch configuration */
    for (int i = 0; i < n; i++){
        printf("%d", switches[i]);
    }
    printf("\n");
}
void solve(int start, int n, int total){
    if (n == 1){
        toggle(start, total);
        return;
    }
    if (n == 2){
        toggle(start, total);
        toggle(start + 1, total);
        return;
    }
    solve(start + 2, n - 2, total);
    toggle(start, total);
    undo(start + 2, n - 2, total);
    solve(start + 1, n - 1, total);
}

void undo(int start, int n, int total){
    if (n == 1){
        toggle(start, total);
        return;
    }
    if (n == 2){
        toggle(start + 1, total);
        toggle(start, total);
        return;
    }
    /* Reverse STEP 4 of solve() */
    undo(start + 1, n - 1, total);
    /* Reverse STEP 3 of solve() */
    solve(start + 2, n - 2, total);
    /* Reverse STEP 2 of solve() */
    toggle(start, total);
    /* Reverse STEP 1 of solve() */
    undo(start + 2, n - 2, total);
}
int main(){
    int n;
    /* Read number of switches */
    printf("Enter number of switches: ");
    scanf("%d", &n);
    /* Validate input */
    if (n <= 0 || n > 20){
        printf("Invalid input.\n");
        return 1;
    }
    for (int i = 0; i < n; i++){
        switches[i] = 1;
    }
    /* Display initial state */
    printf("\nInitial state: ");
    for (int i = 0; i < n; i++){
        printf("%d", switches[i]);
    }
    printf("\n\n");
    solve(0, n, n);
    /* Display final state */
    printf("\nFinal state: ");
    for (int i = 0; i < n; i++){
        printf("%d", switches[i]);
    }
    printf("\n");
    /* Display total number of moves */
    printf("Total moves = %d\n", moves);
    return 0;
}