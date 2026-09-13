// Question 6:
// [The best time to be alive] An editor of The History of the World Science wants to find
// out the time when the largest number of prominent scientists were alive. The prominent
// scientists are, by definition, the people mentioned in the book with the dates of their birth
// and death. (No living scientists are included in the book.) Devise an algorithm for this task
// if it has the book’s index as its input. The entries in the index are sorted alphabetically
// and give the persons’ birth and death years. If a person A died the same year person B
// was born, assume that the former event happened before the latter one.

// Input representation: Array of 2n events
// Algorithm:
//     1. Create birth and death events.
//     2. Sort events by year.
//     3. For equal years, process death before birth.
//     4. Sweep through the sorted events.
//     5. Maintain the current number of living scientists.
//     6. Store the maximum count and corresponding year.
// Time Complexity  = O(n log n)
// Space Complexity = O(n)

// CODE---
#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int year;
    int type;       // +1 = birth, -1 = death
} Event;
/* Compare two events */
int compareEvents(const void *a, const void *b){
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    if (e1->year != e2->year) return e1->year - e2->year;
return e1->type - e2->type;
}
int main(){
    int n;
    printf("Enter number of scientists: ");
    scanf("%d", &n);
    Event *events = (Event *)malloc(2 * n * sizeof(Event));
    /* Read birth and death years */
    for (int i = 0; i < n; i++){
        int birth, death;
        printf("Enter birth and death year of scientist %d: ",i + 1);
        scanf("%d %d", &birth, &death);
        events[2 * i].year = birth;
        events[2 * i].type = 1;
        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }
    /* Sort all events */
    qsort(events, 2 * n, sizeof(Event), compareEvents);
    int current = 0;
    int maximum = 0;
    int bestYear = 0;
    /* Sweep through all events */
    for (int i = 0; i < 2 * n; i++){
        current += events[i].type;
        if (current > maximum){
            maximum = current;
            bestYear = events[i].year;
        }
    }
    printf("\nMaximum number of scientists alive = %d\n",maximum);
    printf("A year with the maximum number alive = %d\n",bestYear);
    free(events);
    return 0;
}
