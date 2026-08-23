/*
Question 4:
Application of sorting-IV: A camera at the door tracks the entry time ai and exit
time bi (assume bi > ai) for each of n the persons pi attending a party. Give an
O(n·logn) algorithm that analyses this data to determine the time when the most
people were simultaneously present at the party. Assume that all entry and exit
times are distinct (no ties). By choosing the proper input representation, write
a program in C to validate your algorithm.


Algorithm:
1. For each person i, create two events:
   - (a_i, ENTRY)  → one more person enters
   - (b_i, EXIT)   → one person leaves
2. Sort all 2n events by time in ascending order.
   - All times are distinct, so no tie-breaking is needed.
3. Sweep through the sorted events, maintaining:
   - cur = current number of people at the party
   - max_people = maximum value of cur seen so far
   - max_time = time at which max_people was first achieved
4. For each event in sorted order:
   - If ENTRY: cur++; if cur > max_people, update max_people and max_time
   - If EXIT: cur--
5. At the end, max_time is a time when the most people were present,
   and max_people is that maximum count.

Complexity:
- Total time: O(n log n)
- Extra space: O(n) for the events array

Pseudocode:
Algorithm MaxOverlapTime(A[1..n], B[1..n]):
    1. Create array Events[1..2n]
    2. For i = 1 to n:
           Events[2i-1] ← (time = A[i], type = ENTRY)
           Events[2i]   ← (time = B[i], type = EXIT)
    3. Sort Events by time ascending
    4. cur ← 0
       max_people ← 0
       max_time ← -1
    5. For k = 1 to 2n:
           If Events[k].type = ENTRY:
               cur ← cur + 1
               If cur > max_people:
                   max_people ← cur
                   max_time ← Events[k].time
           Else:  // EXIT
               cur ← cur - 1
    6. Return (max_time, max_people)
*/

//CODE---
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int time;
    int type;
} Event;
int cmp_event(const void *x, const void *y) {
    const Event *a = x;
    const Event *b = y;
    return a->time - b->time;
}
int main(void) {
    int n;
    printf("Enter number of people: ");
    scanf("%d",&n);
    Event *ev = malloc(2 * n * sizeof(Event));
    for (int i = 0; i < n; i++) {
        int a, b;
        printf("Person %d entry and exit time: ", i + 1);
        if (scanf("%d %d", &a, &b) != 2 || b <= a) {
            printf("Invalid times (need b > a)\n");
            free(ev);
            return 1;
        }
        ev[2 * i].time = a;
        ev[2 * i].type = 1;
        ev[2 * i + 1].time = b;
        ev[2 * i + 1].type = -1;
    }
    qsort(ev, 2 * n, sizeof(Event), cmp_event);
    int cur = 0, max_people = 0, max_time = -1;
    for (int i = 0; i < 2 * n; i++) {
        if (ev[i].type == 1) {
            cur++;
            if (cur > max_people) {
                max_people = cur;
                max_time = ev[i].time;
            }
        } else {
            cur--;
        }
    }
    printf("Maximum people simultaneously present: %d\n", max_people);
    printf("Time of maximum overlap: %d\n", max_time);
    free(ev);
    return 0;
}