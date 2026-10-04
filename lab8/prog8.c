// [Optimal Binary Search Trees (OBST)] Given a set of n distinct sorted keys K =
// ↑k1,k2,...,kn↓ with search probabilities p1,p2,...,pn, and n+1 dummy keys d0,d1,...,dn
// representing searches not in K with probabilities q0,q1,...,qn,findtheminimumexpected
// search cost of a binary search tree. By choosing the proper input representation, write
// a program in C to validate your procedures and derive the complexity analysis of your
// algorithm.


#include <stdio.h>
#include <stdlib.h>
#include <float.h>
/*
    Print one optimal BST recursively.
    root[i][j] contains the index r of the root key for interval [i, j].
    parentName:
    - "ROOT" for the full tree root
    - otherwise a key name such as "k2"
*/
void printOptimalBST(int **root, int keys[], int i, int j,
                     const char *parentName, const char *relation) {
    if (i > j) {
        printf("%s is the %s child of %s\n",
               (i == j + 1) ? "dummy key" : "dummy key",
               relation, parentName);
        return;
    }
    int r = root[i][j];
    printf("k%d (%d) is the %s child of %s\n",r, keys[r], relation, parentName);
    char currentName[30];
    sprintf(currentName, "k%d (%d)", r, keys[r]);
    printOptimalBST(root, keys, i, r - 1, currentName, "left");
    printOptimalBST(root, keys, r + 1, j, currentName, "right");
}
/* Print the tree in parenthesized preorder form */
void printTreeExpression(int **root, int keys[], int i, int j) {
    if (i > j) {
        printf("d%d", j);
        return;
    }
    int r = root[i][j];
    printf("(");
    printf("%d ", keys[r]);
    printTreeExpression(root, keys, i, r - 1);
    printf(" ");
    printTreeExpression(root, keys, r + 1, j);
    printf(")");
}
int main() {
    int n;
    printf("Enter number of sorted keys: ");
    scanf("%d", &n);
    /*
        Use 1-based indexing:
        keys[1..n]
        p[1..n]
        q[0..n]
    */
    int *keys = (int *)malloc((n + 1) * sizeof(int));
    double *p = (double *)malloc((n + 1) * sizeof(double));
    double *q = (double *)malloc((n + 1) * sizeof(double));
    printf("Enter %d sorted keys:\n", n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &keys[i]);
    }
    printf("Enter probabilities p1 to p%d:\n", n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
    }
    printf("Enter probabilities q0 to q%d:\n", n);
    for (int i = 0; i <= n; i++) {
        scanf("%lf", &q[i]);
    }
    /*
        Allocate (n+2) x (n+1) tables.
        Extra space supports e[n+1][n].
    */
    double **e = (double **)malloc((n + 2) * sizeof(double *));
    double **w = (double **)malloc((n + 2) * sizeof(double *));
    int **root = (int **)malloc((n + 2) * sizeof(int *));
    for (int i = 0; i <= n + 1; i++) {
        e[i] = (double *)malloc((n + 1) * sizeof(double));
        w[i] = (double *)malloc((n + 1) * sizeof(double));
        root[i] = (int *)malloc((n + 1) * sizeof(int));
    }
    /* Base cases: empty subtrees */
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }
    /*
        length = number of real keys in the subtree.
        Build solutions from short intervals to longer intervals.
    */
    for (int length = 1; length <= n; length++) {
        for (int i = 1; i <= n - length + 1; i++) {
            int j = i + length - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double cost = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }
    double totalProbability = 0.0;
    for (int i = 1; i <= n; i++) {
        totalProbability += p[i];
    }
    for (int i = 0; i <= n; i++) {
        totalProbability += q[i];
    }
    printf("\nTotal probability: %.2lf\n", totalProbability);
    printf("Minimum expected search cost: %.4lf\n", e[1][n]);
    printf("\nOptimal BST in parenthesized form:\n");
    printTreeExpression(root, keys, 1, n);
    printf("\n");
    printf("\nOptimal BST structure:\n");
    int r = root[1][n];
    printf("k%d (%d) is the ROOT\n", r, keys[r]);
    char rootName[30];
    sprintf(rootName, "k%d (%d)", r, keys[r]);
    printOptimalBST(root, keys, 1, r - 1, rootName, "left");
    printOptimalBST(root, keys, r + 1, n, rootName, "right");
    for (int i = 0; i <= n + 1; i++) {
        free(e[i]);
        free(w[i]);
        free(root[i]);
    }
    free(e);
    free(w);
    free(root);
    free(keys);
    free(p);
    free(q);
    return 0;
}