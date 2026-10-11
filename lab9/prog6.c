// Question 6:
// [Reorganise String with K-Distance Apart] Given a string S and an integer K, rear
// range S such that the same characters are at least distance K apart. If impossible, 
// return an empty string. By choosing the proper input representation, write a program 
// in C to validate your algorithm and derive the complexity analysis of your algorithm.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET 128
typedef struct {
    char character;
    int frequency;
} HeapNode;
/* ---------------- Max-heap ---------------- */
void maxHeapify(HeapNode heap[], int heapSize, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < heapSize && heap[left].frequency > heap[largest].frequency) {
        largest = left;
    }
    if (right < heapSize && heap[right].frequency > heap[largest].frequency) {
        largest = right;
    }
    if (largest != index) {
        HeapNode temp = heap[index];
        heap[index] = heap[largest];
        heap[largest] = temp;
        maxHeapify(heap, heapSize, largest);
    }
}

void buildMaxHeap(HeapNode heap[], int heapSize) {
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, heapSize, i);
    }
}

HeapNode extractMax(HeapNode heap[], int *heapSize) {
    HeapNode maxNode = heap[0];
    heap[0] = heap[*heapSize - 1];
    (*heapSize)--;
    maxHeapify(heap, *heapSize, 0);
    return maxNode;
}

void insertMaxHeap(HeapNode heap[], int *heapSize, HeapNode node) {
    heap[*heapSize] = node;
    int index = *heapSize;
    (*heapSize)++;
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent].frequency >= heap[index].frequency) {
            break;
        }
        HeapNode temp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = temp;
        index = parent;
    }
}

/* ---------------- Main algorithm ---------------- */
char *rearrangeString(char S[], int K) {
    int length = strlen(S);
    char *result = (char *)malloc((length + 1) * sizeof(char));
    result[length] = '\0';
    if (K <= 1) {
        strcpy(result, S);
        return result;
    }
    int frequency[ALPHABET] = {0};
    for (int i = 0; i < length; i++) {
        frequency[(unsigned char)S[i]]++;
    }
    HeapNode *heap = (HeapNode *)malloc(ALPHABET * sizeof(HeapNode));
    int heapSize = 0;
    for (int i = 0; i < ALPHABET; i++) {
        if (frequency[i] > 0) {
            heap[heapSize].character = (char)i;
            heap[heapSize].frequency = frequency[i];
            heapSize++;
        }
    }
    buildMaxHeap(heap, heapSize);
    /* Cooling queue stores characters waiting for K positions */
    HeapNode *waitingQueue = (HeapNode *)malloc(K * sizeof(HeapNode));
    int waitingSize = 0;
    int resultIndex = 0;
    while (heapSize > 0 || waitingSize > 0) {
        /*If no character is currently available but some are cooling,
            a valid arrangement is impossible.*/
        if (heapSize == 0) {
            free(result);
            result = (char *)malloc(sizeof(char));
            result[0] = '\0';
            free(heap);
            free(waitingQueue);
            return result;
        }
        HeapNode current = extractMax(heap, &heapSize);
        result[resultIndex] = current.character;
        resultIndex++;
        current.frequency--;
        /* Put the used character into cooling queue */
        waitingQueue[waitingSize] = current;
        waitingSize++;
        /*Once K characters have been placed after using a character,
            it becomes available again.*/
        if (waitingSize == K) {
            HeapNode released = waitingQueue[0];
            for (int i = 1; i < waitingSize; i++) {
                waitingQueue[i - 1] = waitingQueue[i];
            }
            waitingSize--;
            if (released.frequency > 0) {
                insertMaxHeap(heap, &heapSize, released);
            }
        }
    }
    free(heap);
    free(waitingQueue);
    return result;
}

int main() {
    char S[1000];
    int K;
    printf("Enter string S: ");
    scanf("%999s", S);
    printf("Enter K: ");
    scanf("%d", &K);
    char *answer = rearrangeString(S, K);
    if (answer[0] == '\0') {
        printf("\nRearranged string: \"\"\n");
        printf("No valid arrangement exists.\n");
    } else {
        printf("\nRearranged string: %s\n", answer);
    }
    free(answer);
    return 0;
}

// Complexity Analysis:
// Time Complexity: O(n log m) where n is the length of the string and m is the number of unique characters
// Space Complexity: O(m + K) for the heap and waiting queue