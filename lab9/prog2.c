// Question 2:
// [Huffman Coding] Given symbol frequencies, construct a prefix-free binary code of mini
// mum expectedlength, and output the canonical Huffman codebook (where codes are ordered
// lexicographically by length). By choosing the proper input representation, write a 
// program in C to validate your algorithm and derive the complexity analysis of your
// algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SYMBOLS 128
#define MAX_CODE_LENGTH 100
typedef struct Node {
    char symbol; int frequency;
    struct Node *left; struct Node *right;
} Node;
/* ---------------- Min-heap of Huffman nodes ---------------- */
typedef struct {
    Node **array; int size;
    int capacity;
} MinHeap;
Node *createNode(char symbol, int frequency) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->symbol = symbol; node->frequency = frequency;
    node->left = NULL; node->right = NULL;
    return node;}
MinHeap *createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->array = (Node **)malloc(capacity * sizeof(Node *));
    heap->size = 0; heap->capacity = capacity;
    return heap;}
void swapNodes(Node **a, Node **b) {
    Node *temp = *a;
    *a = *b;
    *b = temp;}
void minHeapify(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < heap->size &&
        heap->array[left]->frequency < heap->array[smallest]->frequency) {
        smallest = left;
    }
    if (right < heap->size &&
        heap->array[right]->frequency < heap->array[smallest]->frequency) {
        smallest = right;
    }
    if (smallest != index) {
        swapNodes(&heap->array[index], &heap->array[smallest]);
        minHeapify(heap, smallest);
    }
}
Node *extractMin(MinHeap *heap) {
    Node *minNode = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1]; heap->size--;
    minHeapify(heap, 0);
    return minNode;}
void insertMinHeap(MinHeap *heap, Node *node) {
    heap->array[heap->size] = node;
    int index = heap->size;  heap->size++;
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->array[parent]->frequency <= heap->array[index]->frequency) break;
        swapNodes(&heap->array[parent], &heap->array[index]);
        index = parent;
    }
}
/* ---------------- Huffman tree construction ---------------- */
Node *buildHuffmanTree(char symbols[], int frequencies[], int n) {
    MinHeap *heap = createMinHeap(n);
    for (int i = 0; i < n; i++) 
        insertMinHeap(heap, createNode(symbols[i], frequencies[i]));
    while (heap->size > 1) {
        Node *left = extractMin(heap);
        Node *right = extractMin(heap);
        Node *parent = createNode('\0', left->frequency + right->frequency);
        parent->left = left; parent->right = right;
        insertMinHeap(heap, parent);
    }
    Node *root = extractMin(heap);
    free(heap->array); free(heap);
    return root;}
/* ---------------- Find Huffman code lengths ---------------- */
void findCodeLengths(Node *root, int depth, int codeLength[]) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        codeLength[(unsigned char)root->symbol] = depth;
        return;
    }
    findCodeLengths(root->left, depth + 1, codeLength);
    findCodeLengths(root->right, depth + 1, codeLength);
}
/* ---------------- Canonical Huffman codebook ---------------- */
typedef struct {
    char symbol;
    int codeLength;
} CodeEntry;
int compareCodeEntries(const void *a, const void *b) {
    CodeEntry *x = (CodeEntry *)a;
    CodeEntry *y = (CodeEntry *)b;
    if (x->codeLength != y->codeLength) return x->codeLength - y->codeLength;
    return (unsigned char)x->symbol - (unsigned char)y->symbol;
}
void printCanonicalCodebook(char symbols[], int frequencies[], int n) {
    Node *root = buildHuffmanTree(symbols, frequencies, n);
    int codeLength[MAX_SYMBOLS] = {0};
    findCodeLengths(root, 0, codeLength);
    CodeEntry entries[MAX_SYMBOLS];
    int count = 0;
    for (int i = 0; i < n; i++) {
        entries[count].symbol = symbols[i];
        entries[count].codeLength = codeLength[(unsigned char)symbols[i]];
        count++;
    }
    qsort(entries, count, sizeof(CodeEntry), compareCodeEntries);
    unsigned long long code = 0;
    int previousLength = entries[0].codeLength;
    printf("\nCanonical Huffman Codebook:\n");
    for (int i = 0; i < count; i++) {
        int currentLength = entries[i].codeLength;
        if (i == 0) code = 0;
        else {
            code = code + 1;
            if (currentLength > previousLength) code = code << (currentLength - previousLength);
        }
        printf("%c : ", entries[i].symbol);
        for (int bit = currentLength - 1; bit >= 0; bit--) {
            printf("%d", (code >> bit) & 1);
        }
        printf("\n");
        previousLength = currentLength;
    }
    /* Expected length calculation */
    long long totalFrequency = 0;
    double expectedLength = 0.0;
    for (int i = 0; i < n; i++)  totalFrequency += frequencies[i];
    for (int i = 0; i < n; i++) 
        expectedLength +=((double)frequencies[i] / totalFrequency) * codeLength[(unsigned char)symbols[i]];
    printf("\nMinimum expected code length: %.4lf bits/symbol\n",expectedLength);
}
int main() {
    int n;
    printf("Enter number of symbols: ");
    scanf("%d", &n);
    char *symbols = (char *)malloc(n * sizeof(char));
    int *frequencies = (int *)malloc(n * sizeof(int));
    printf("Enter symbol and frequency for each symbol:\n");
    for (int i = 0; i < n; i++) {
        scanf(" %c %d", &symbols[i], &frequencies[i]);
    }
    printCanonicalCodebook(symbols, frequencies, n);
    free(symbols); free(frequencies);
// Complexity Analysis:
// Time Complexity: O(n log n) due to sorting
// Space Complexity: O(n) for storing the codebook entries
    return 0;
}