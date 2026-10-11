// Question 8:
// [Minimum Number of Meeting Rooms] Given an array of meeting time intervals con
// sisting of start and end times [︁[s1,e1],[s2,e2],... ]︁, find the minimum number of 
// conference rooms required. By choosing the proper input representation, write a program
// in C to validate your procedures and derive the complexity analysis of your algorithm.


#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int start;
    int end;
} Meeting;

/* ---------------- Min-heap functions ---------------- */
void minHeapify(int heap[], int heapSize, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < heapSize && heap[left] < heap[smallest]) smallest = left;
    if (right < heapSize && heap[right] < heap[smallest]) smallest = right;
    if (smallest != index) {
        int temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        minHeapify(heap, heapSize, smallest);
    }
}

void buildMinHeap(int heap[], int heapSize) {
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
        minHeapify(heap, heapSize, i);
    }
}

int extractMin(int heap[], int *heapSize) {
    int minValue = heap[0];
    heap[0] = heap[*heapSize - 1];
    (*heapSize)--;
    minHeapify(heap, *heapSize, 0);
    return minValue;
}

void insertMinHeap(int heap[], int *heapSize, int value) {
    heap[*heapSize] = value;
    int index = *heapSize;
    (*heapSize)++;
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] <= heap[index]) break;
        int temp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = temp;
        index = parent;
    }
}

/* ---------------- Sort meetings by start time ---------------- */
int compareMeetings(const void *a, const void *b) {
    Meeting *x = (Meeting *)a;
    Meeting *y = (Meeting *)b;
    return x->start - y->start;
}

/* ---------------- Main algorithm ---------------- */
int minimumMeetingRooms(Meeting meetings[], int n) {
    if (n == 0) return 0;
    qsort(meetings, n, sizeof(Meeting), compareMeetings);
    int *endTimes = (int *)malloc(n * sizeof(int));
    int heapSize = 0;
    for (int i = 0; i < n; i++) {
        /* If the earliest-ending meeting has already ended,reuse that room.*/
        if (heapSize > 0 && endTimes[0] <= meetings[i].start) extractMin(endTimes, &heapSize);
        /*Allocate or continue using a room for this meeting.*/
        insertMinHeap(endTimes, &heapSize, meetings[i].end);
    }
    int answer = heapSize;
    free(endTimes);
    return answer;
}

int main() {
    int n;
    printf("Enter number of meetings: ");
    scanf("%d", &n);
    Meeting *meetings = (Meeting *)malloc(n * sizeof(Meeting));
    printf("Enter start and end time of each meeting:\n");
    for (int i = 0; i < n; i++) scanf("%d %d", &meetings[i].start, &meetings[i].end);
    int rooms = minimumMeetingRooms(meetings, n);
    printf("\nMinimum number of meeting rooms required: %d\n", rooms);
    free(meetings);
    return 0;
}

// Complexity Analysis:
// Time Complexity: O(n log n) for sorting and heap operations
// Space Complexity: O(n) for the endTimes heap