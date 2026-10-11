// Question 4:
// [Minimum Cost to Connect Sticks] You have sticks of lengths L1,L2,...,Ln. Con
// necting two sticks of lengths x and y costs x+y, resulting in a single stick of length 
// x+y. Find the minimum total cost to connect all sticks into one. By choosing the proper 
// input representation, write a program in C to validate your algorithm and derive the 
// complexity analysis of your algorithm.


#include <stdio.h>
#include <stdlib.h>
/* ---------------- Min-heap functions ---------------- */
void minHeapify(int heap[], int heapSize, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < heapSize && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < heapSize && heap[right] < heap[smallest]) {
        smallest = right;
    }
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
        if (heap[parent] <= heap[index]) {
            break;
        }
        int temp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = temp;
        index = parent;
    }
}
/* ---------------- Main algorithm ---------------- */
long long minimumCostToConnectSticks(int sticks[], int n) {
    if (n <= 1) {
        return 0;
    }
    int *heap = (int *)malloc(n * sizeof(int));
    int heapSize = n;
    for (int i = 0; i < n; i++) {
        heap[i] = sticks[i];
    }
    buildMinHeap(heap, heapSize);
    long long totalCost = 0;
    while (heapSize > 1) {
        int first = extractMin(heap, &heapSize);
        int second = extractMin(heap, &heapSize);
        int combinedLength = first + second;
        totalCost += combinedLength;
        insertMinHeap(heap, &heapSize, combinedLength);
    }
    free(heap);
    return totalCost;
}
int main() {
    int n;
    printf("Enter number of sticks: ");
    scanf("%d", &n);
    int *sticks = (int *)malloc(n * sizeof(int));
    printf("Enter %d stick lengths:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &sticks[i]);
    }
    long long answer = minimumCostToConnectSticks(sticks, n);
    printf("\nMinimum total cost to connect all sticks: %lld\n", answer);
    free(sticks);
    return 0;
}

// Complexity Analysis:
// Time Complexity: O(n log n) due to heap operations
// Space Complexity: O(n) for the heap array