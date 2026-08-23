/*
Question 6:
Application of sorting-VI: You are given a set S of n intervals on a line, with the
ith interval described by its left and right endpoints (li,ri). Give an O(n · logn)
algorithm to identify a point p on the line that is in the largest number of intervals.
As an example, for S ={(10,40),(20,60),(50,90),(15,70)} no point exists in all four
intervals, but p = 50 is an example of a point in three intervals. You can assume an
endpoint counts as being in its interval. By choosing a suitable input and output
representation, write a program in C to validate your algorithm.

Algorithm:
1. For each interval [l_i, r_i], create two events:
   - (l_i, ENTRY) → one more interval starts covering points
   - (r_i, EXIT)  → one interval stops covering points after r_i
2. Sort all 2n events by:
   - Primary key: time ascending
   - Secondary key: ENTRY before EXIT when times are equal
     (so that endpoints are counted as inside their intervals)
3. Sweep through the sorted events, maintaining:
   - cur = current number of intervals covering the current point
   - max_count = maximum value of cur seen so far
   - best_point = time at which max_count was first achieved
4. For each event in sorted order:
   - If ENTRY: cur++; if cur > max_count, update max_count and best_point
   - If EXIT: cur--
5. At the end, best_point is a point covered by the maximum number of intervals,
   and max_count is that maximum.

Complexity:
- Total time: O(n log n)
- Extra space: O(n) for the events array

Pseudocode:
Algorithm MaxCoveredPoint(S[1..n]):
    1. Create array Events[1..2n]
    2. For i = 1 to n:
           Events[2i-1] = (time = l_i, type = ENTRY)
           Events[2i]   = (time = r_i, type = EXIT)
    3. Sort Events by:
           - time ascending
           - if times equal, ENTRY before EXIT
    4. cur ← 0
       max_count ← 0
       best_point ← -1
    5. For each event e in Events:
           If e.type = ENTRY:
               cur ← cur + 1
               If cur > max_count:
                   max_count ← cur
                   best_point ← e.time
           Else:
               cur ← cur - 1

    6. Return (best_point, max_count)
*/

//CODE---
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int time;
    int type;
} Event;
int cmp_event(const void *a, const void *b) {
    const Event *ea = a;
    const Event *eb = b;
    if (ea->time != eb->time)
        return ea->time - eb->time;
    return eb->type - ea->type;
}
int main(void) {
    int n;
    printf("Enter number of intervals: ");
    scanf("%d", &n);
    Event *ev = malloc(2 * n * sizeof(Event));
    for (int i = 0; i < n; i++) {
        int l, r;
        printf("Interval %d left and right: ", i + 1);
        scanf("%d %d", &l, &r);
        ev[2 * i].time = l;
        ev[2 * i].type = 1;
        ev[2 * i + 1].time = r;
        ev[2 * i + 1].type = -1;
    }
    qsort(ev, 2 * n, sizeof(Event), cmp_event);
    int cur = 0, max_count = 0, best_point = -1;
    for (int i = 0; i < 2 * n; i++) {
        if (ev[i].type == 1) {
            cur++;
            if (cur > max_count) {
                max_count = cur;
                best_point = ev[i].time;
            }
        } else {
            cur--;
        }
    }
    printf("Point with maximum coverage: %d\n", best_point);
    printf("Number of intervals covering it: %d\n", max_count);
    free(ev);
    return 0;
}