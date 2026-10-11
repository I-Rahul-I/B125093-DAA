// Question 7:
//  [Minimise Deviation in Array (Two-Way Greedy with Max-Heap)] Given an ar
// ray of positive integers, you can perform two operations: multiply any odd element by
// 2, or divide any even element by 2. The deviation is (max(A) − min(A)). Minimise the
// deviation after any number of operations. By choosing the proper input representation,
// write a program in C to validate your procedures and derive the complexity analysis of
// your algorithm.


#include <stdio.h>
#include <stdlib.h>
/* ---------------- Max-heap functions ---------------- */
void maxHeapify(int heap[], int heapSize, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < heapSize && heap[left] > heap[largest]) largest = left;
    if (right < heapSize && heap[right] > heap[largest]) largest = right;
    if (largest != index) {
        int temp = heap[index];
        heap[index] = heap[largest];
        heap[largest] = temp;
        maxHeapify(heap, heapSize, largest);
    }
}
void buildMaxHeap(int heap[], int heapSize) {
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, heapSize, i);
    }
}
int extractMax(int heap[], int *heapSize) {
    int maxValue = heap[0];
    heap[0] = heap[*heapSize - 1];
    (*heapSize)--;
    maxHeapify(heap, *heapSize, 0);
    return maxValue;
}
void insertMaxHeap(int heap[], int *heapSize, int value) {
    heap[*heapSize] = value;
    int index = *heapSize;
    (*heapSize)++;
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] >= heap[index]) break;
        int temp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = temp;
        index = parent;
    }
}

/* ---------------- Main algorithm ---------------- */
int minimizeDeviation(int nums[], int n) {
    int *heap = (int *)malloc(n * sizeof(int));
    int heapSize = 0;
    int minimumValue = 1000000000;
    /* Normalize: If a number is odd, multiply it by 2.
        Now every number is even and can only be divided by 2. */
    for (int i = 0; i < n; i++) {
        int value = nums[i];
        if (value % 2 == 1) value = value * 2;
        heap[heapSize] = value;
        heapSize++;
        if (value < minimumValue) minimumValue = value;
    }
    buildMaxHeap(heap, heapSize);
    int minimumDeviation = 1000000000;
    /* Repeatedly reduce the current maximum while it is even.*/
    while (heap[0] % 2 == 0) {
        int currentMax = heap[0];
        int currentDeviation = currentMax - minimumValue;
        if (currentDeviation < minimumDeviation) {
            minimumDeviation = currentDeviation;
        }
        int halvedValue = currentMax / 2;
        if (halvedValue < minimumValue) {
            minimumValue = halvedValue;
        }
        extractMax(heap, &heapSize);
        insertMaxHeap(heap, &heapSize, halvedValue);
    }
    /* Final check after the maximum becomes odd.*/
    int finalDeviation = heap[0] - minimumValue;
    if (finalDeviation < minimumDeviation) minimumDeviation = finalDeviation;
    free(heap);
    return minimumDeviation;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *nums = (int *)malloc(n * sizeof(int));
    printf("Enter %d positive integers:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &nums[i]);
    int answer = minimizeDeviation(nums, n);
    printf("\nMinimum deviation: %d\n", answer);
    free(nums);
    return 0;
}

// Complexity Analysis:
// Time Complexity: O(n log n) due to heap operations
// Space Complexity: O(n) for the heap array