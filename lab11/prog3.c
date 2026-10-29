// Question 3 :
//  [Bidirectional BFS for Shortest Transformation Sequence in a Word Graph] You
// are given:
// ◦ A dictionary D containing N unique words, where every word has the exact same
// length L.
// ◦ A starting word A and a target word B, both of length L.
// A valid mutation step consists of changing exactly one character of a word such that
// the resulting word exists in dictionary D. A transformation sequence from A to B is
// an ordered sequence of words:
// W0,W1,W2,...,Wk
// such that:
// 1. W0 =A and Wk =B.
// 2. Every intermediate word Wi ∈ D for all 1 ≤ i ≤ k. (Note: whether A must initially
// be in D is typically specified by the input constraints, but B must always be in D.)
// 3. For every adjacent pair (Wi−1,Wi), the two words differ by exactly one character
// (i.e.,their Hamming distance is 1).
// Objective: Compute the minimum number of mutations k required to transform A into B.
// If A cannot be transformed into B through valid intermediate words in D, return −1
// (or report that no valid path exists). Keep in mind to consider the following 
// constraints for this problem during implementation:
// ◦ N ≤ 105 (number of dictionary words)
// ◦ L≤10 (length of each word)
// ◦ All words consist solely of lowercase English letters (’a’ to ’z’).
// By choosing the proper input representation, write a program in C to validate your
// algorithm and derive the complexity analysis of your algorithm


// CODE---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 100005
#define MAXL 11
#define ALPHABET 26
char words[MAXN][MAXL];
int wordCount = 0;
/* Simple open-addressing hash set for dictionary lookup. */
typedef struct {
    int *slot;
    int capacity;
} HashSet;
unsigned long hashWord(const char *s) {
    unsigned long h = 1469598103934665603UL;
    while (*s) {
        h ^= (unsigned char)(*s++);
        h *= 1099511628211UL;
    }
    return h;
}
void initSet(HashSet *set, int capacity) {
    set->capacity = capacity;
    set->slot = malloc(sizeof(int) * capacity);
    for (int i = 0; i < capacity; i++)
        set->slot[i] = -1;
}
/* Returns index if present, otherwise -1. */
int findWord(HashSet *set, const char *s) {
    unsigned long h = hashWord(s) % set->capacity;
    while (set->slot[h] != -1) {
        if (strcmp(words[set->slot[h]], s) == 0)
            return set->slot[h];
        h = (h + 1) % set->capacity;
    }
    return -1;
}
int insertWord(HashSet *set, const char *s) {
    unsigned long h = hashWord(s) % set->capacity;
    while (set->slot[h] != -1) {
        if (strcmp(words[set->slot[h]], s) == 0)
            return set->slot[h];
        h = (h + 1) % set->capacity;
    }
    strcpy(words[wordCount], s);
    set->slot[h] = wordCount;
    return wordCount++;
}
int hammingDistance1(const char *a, const char *b) {
    int diff = 0;
    for (int i = 0; a[i]; i++)
        if (a[i] != b[i] && ++diff > 1)
            return 0;
    return diff == 1;
}
int bidirectionalBFS(HashSet *dict, const char *A, const char *B, int L) {
    if (findWord(dict, B) == -1)
        return -1;
    if (strcmp(A, B) == 0)
        return 0;
    int frontA[MAXN], frontB[MAXN];
    int visitedA[MAXN], visitedB[MAXN];
    int nextA[MAXN], nextB[MAXN];
    memset(visitedA, 0, sizeof(visitedA));
    memset(visitedB, 0, sizeof(visitedB));
    int sizeA = 0, sizeB = 0;
    int indexA = findWord(dict, A);
    int indexB = findWord(dict, B);
    /* A may be outside D; still treat it as the starting vertex. */
    if (indexA == -1) {
        strcpy(words[wordCount], A);
        indexA = wordCount++;
    }
    frontA[sizeA++] = indexA;
    frontB[sizeB++] = indexB;
    visitedA[indexA] = 1;
    visitedB[indexB] = 1;
    int mutations = 0;
    char candidate[MAXL];
    while (sizeA > 0 && sizeB > 0) {
        /* Expand the smaller frontier. */
        int *front, *next, *visited, *otherVisited;
        int size, nextSize = 0;
        char (*storedWords)[MAXL] = words;
        if (sizeA <= sizeB) {
            front = frontA;
            next = nextA;
            visited = visitedA;
            otherVisited = visitedB;
            size = sizeA;
        } else {
            front = frontB;
            next = nextB;
            visited = visitedB;
            otherVisited = visitedA;
            size = sizeB;
        }
        mutations++;
        for (int i = 0; i < size; i++) {
            strcpy(candidate, storedWords[front[i]]);
            for (int pos = 0; pos < L; pos++) {
                char original = candidate[pos];
                for (int c = 0; c < ALPHABET; c++) {
                    if (candidate[pos] == 'a' + c)
                        continue;
                    candidate[pos] = 'a' + c;
                    int id = findWord(dict, candidate);
                    if (id == -1)
                        continue;
                    if (otherVisited[id])
                        return mutations;
                    if (!visited[id]) {
                        visited[id] = 1;
                        next[nextSize++] = id;
                    }
                }
                candidate[pos] = original;
            }
        }
        if (sizeA <= sizeB) {
            sizeA = nextSize;
            memcpy(frontA, nextA, nextSize * sizeof(int));
        } else {
            sizeB = nextSize;
            memcpy(frontB, nextB, nextSize * sizeof(int));
        }
    }
    return -1;
}
int main(void) {
    int N, L;
    char A[MAXL], B[MAXL];
    printf("Enter dictionary size N and word length L:\n");
    scanf("%d %d", &N, &L);
    HashSet dict;
    initSet(&dict, 4 * N + 10);
    printf("Enter %d dictionary words:\n", N);
    for (int i = 0; i < N; i++) {
        char w[MAXL];
        scanf("%s", w);
        insertWord(&dict, w);
    }
    printf("Enter starting word A and target word B:\n");
    scanf("%s %s", A, B);
    int answer = bidirectionalBFS(&dict, A, B, L);
    if (answer == -1)
        printf("No valid transformation sequence exists.\n");
    else
        printf("Minimum number of mutations: %d\n", answer);
    free(dict.slot);
    return 0;
}
//Complexity Analysis
//Time complexity O(V+E)
//Space complexity O(V+E)