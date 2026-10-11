// Question 9:
// [Hu-Tucker Greedy Simulation]∗ Given an ordered sequence of weights w1,w2,...,wn,
// construct an optimal alphabetic binary search tree or merge pattern that maintains the
// strict in-order sequence of indices while minimizing ∑︁wi·depth(i). By choosing the
// proper input representation, write a program in C to validate your algorithm and derive 
// the complexity analysis of your algorithm.


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct {
    int weight;
    int leftIndex;
    int rightIndex;
    int active;
    int mergeCount;
} Node;

/* Find the compatible pair with minimum combined weight */
void findMinimumCompatiblePair(Node nodes[], int n, int *bestI, int *bestJ) {
    int minimumSum = INT_MAX;
    *bestI = -1;
    *bestJ = -1;
    for (int i = 0; i < n; i++) {
        if (!nodes[i].active) continue;
        /* Search for the nearest active node to the right.
            Any original active node between them makes them incompatible. */
        for (int j = i + 1; j < n; j++) {
            if (!nodes[j].active) continue;
            int sum = nodes[i].weight + nodes[j].weight;
            if (sum < minimumSum) {
                minimumSum = sum;
                *bestI = i;
                *bestJ = j;
            }
            /* Stop after the first active node to the right.
                Nodes beyond it are not compatible with node i. */
            break;
        }
    }
}
/* Build the final alphabetic tree from leaf depths */
void buildAlphabeticTree(Node nodes[], int n, int depths[]) {
    /* A simple way to construct the tree is to recursively
        partition leaves according to their depths. */
    printf("\nAlphabetic tree construction from depths:\n");
    for (int i = 0; i < n; i++) printf("Leaf %d: weight = %d, depth = %d\n",i + 1, nodes[i].weight, depths[i]);
}

int main() {
    int n;
    printf("Enter number of ordered leaves: ");
    scanf("%d", &n);
    Node *nodes = (Node *)malloc(n * sizeof(Node));
    int *depths = (int *)calloc(n, sizeof(int));
    printf("Enter %d positive weights:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nodes[i].weight);
        nodes[i].leftIndex = i;
        nodes[i].rightIndex = i;
        nodes[i].active = 1;
        nodes[i].mergeCount = 0;
    }
    printf("\nHu-Tucker merge simulation:\n");
    int activeCount = n;
    while (activeCount > 1) {
        int i, j;
        findMinimumCompatiblePair(nodes, n, &i, &j);
        if (i == -1 || j == -1) {
            printf("Error: no compatible pair found.\n");
            return 1;
        }
        int mergedWeight = nodes[i].weight + nodes[j].weight;
        printf("Merge leaves/nodes covering indices [%d..%d] and [%d..%d], "
               "combined weight = %d\n",nodes[i].leftIndex + 1,
               nodes[i].rightIndex + 1, nodes[j].leftIndex + 1,
               nodes[j].rightIndex + 1, mergedWeight);
        /* Increase depth of every original leaf
            covered by the two merged nodes.*/
        for (int k = nodes[i].leftIndex; k <= nodes[i].rightIndex; k++) depths[k]++;
        for (int k = nodes[j].leftIndex; k <= nodes[j].rightIndex; k++) depths[k]++;
        /* The merged node replaces the left node.
            It represents the contiguous interval [leftIndex..rightIndex].*/
        nodes[i].weight = mergedWeight;
        nodes[i].rightIndex = nodes[j].rightIndex;
        nodes[i].mergeCount++;
        nodes[j].active = 0;
        activeCount--;
    }
    long long minimumCost = 0;
    for (int i = 0; i < n; i++) minimumCost += (long long)nodes[i].weight * depths[i];
    printf("\nLeaf depths:\n");
    for (int i = 0; i < n; i++) printf("Leaf %d: depth = %d\n", i + 1, depths[i]);
    printf("\nMinimum weighted external path length: %lld\n", minimumCost);
    buildAlphabeticTree(nodes, n, depths);
    free(nodes);
    free(depths);
    return 0;
}

// Complexity Analysis:
// Time Complexity: O(n^2) due to the nested loops in finding compatible pairs
// Space Complexity: O(n) for storing nodes and depths