// QUESTION 1
// Dictionary Operations: Consider a dictionary (D) abstract data type that permits access
// to data items by content (key). The following are the primary operations that the dictionary
// supports.
// • Search(D,k)- Given a search key k, return a pointer to the elements in the dictionary
// D whose key value is k, if one exists.
// • Insert(D,x)- Given a data item x, add it to the Dictionary D.
// • Delete(D,x)- Given a pointer x to a data item in the dictionary D, remove it from
// D.
// • Max(D) or Min(D)- Retrieve the item with the largest (or smallest) key from D.
// These two operations help the dictionary to serve as a priority queue.
// • Predecessor(D,x) or Successor(D,x) Retrieve the item from D whose key is imme
// diately before (or after) the item x in sorted order.
// What are the asymptotic worst-case running times for all the seven primary operations
// (search, insert, delete, maximum, minimum, predecessor, and successor) when the said
// data structure is implemented using:
// • An unsorted array.
// • Asorted array.
// • Asingly linked unsorted list.
// • Asingly linked sorted list.
// • Adoubly linked unsorted list.
// • Adoubly linked sorted list.
// Write a C program to validate your claim by plotting the order of growth of these functions.



// //CODE:---
#include <stdio.h>
#include <stdlib.h>
#define STRUCTURES 6
#define OPERATIONS 7
#define DATA_POINTS 12
enum {UNSORTED_ARRAY,SORTED_ARRAY,SINGLY_UNSORTED,SINGLY_SORTED,DOUBLY_UNSORTED,DOUBLY_SORTED};
enum {SEARCH,INSERT,DELETE,MAXIMUM,MINIMUM,PREDECESSOR,SUCCESSOR};
const char *structureNames[STRUCTURES] = {"Unsorted array","Sorted array","Singly linked unsorted list",
    "Singly linked sorted list","Doubly linked unsorted list","Doubly linked sorted list"};
const char *operationNames[OPERATIONS] = {"Search","Insert","Delete","Maximum","Minimum","Predecessor","Successor"};

const char *fileNames[OPERATIONS] = {"search.csv","insert.csv","delete.csv","maximum.csv",
    "minimum.csv","predecessor.csv","successor.csv"};

long long logarithmicSteps(int n) {
    long long steps = 0;
    while (n > 1) {
        n = (n + 1) / 2;
        steps++;
    }
    return steps + 1;
}

long long operationSteps(int structure, int operation, int n) {
    switch (structure) {
        case UNSORTED_ARRAY:
            switch (operation) {
                case SEARCH:
                    return n;
                case INSERT:
                    return 1;
                case DELETE:
                    return n;
                case MAXIMUM:
                    return n;
                case MINIMUM:
                    return n;
                case PREDECESSOR:
                    return 2LL * n;
                case SUCCESSOR:
                    return 2LL * n;
            }
            break;

        case SORTED_ARRAY:
            switch (operation) {
                case SEARCH:
                    return logarithmicSteps(n);
                case INSERT:
                    return n;
                case DELETE:
                    return n;
                case MAXIMUM:
                    return 1;
                case MINIMUM:
                    return 1;
                case PREDECESSOR:
                    return 1;
                case SUCCESSOR:
                    return 1;
            }
            break;
        case SINGLY_UNSORTED:
            switch (operation) {
                case SEARCH:
                    return n;
                case INSERT:
                    return 1;
                case DELETE:
                    return n;
                case MAXIMUM:
                    return n;
                case MINIMUM:
                    return n;
                case PREDECESSOR:
                    return 2LL * n;
                case SUCCESSOR:
                    return 2LL * n;
            }
            break;
        case SINGLY_SORTED:
            switch (operation) {
                case SEARCH:
                    return n;
                case INSERT:
                    return n;
                case DELETE:
                    return n;
                case MAXIMUM:
                    return n;
                case MINIMUM:
                    return 1;
                case PREDECESSOR:
                    return n;
                case SUCCESSOR:
                    return 1;
            }
            break;
        case DOUBLY_UNSORTED:
            switch (operation) {
                case SEARCH:
                    return n;
                case INSERT:
                    return 1;
                case DELETE:
                    return 1;
                case MAXIMUM:
                    return n;
                case MINIMUM:
                    return n;
                case PREDECESSOR:
                    return 2LL * n;
                case SUCCESSOR:
                    return 2LL * n;
            }
            break;
        case DOUBLY_SORTED:
            switch (operation) {
                case SEARCH:
                    return n;
                case INSERT:
                    return n;
                case DELETE:
                    return 1;
                case MAXIMUM:
                    return 1;
                case MINIMUM:
                    return 1;
                case PREDECESSOR:
                    return 1;
                case SUCCESSOR:
                    return 1;
            }
            break;
    }
    return 0;
}
void createCsvFiles(void) {
    FILE *files[OPERATIONS];
    for (int operation = 0; operation < OPERATIONS; operation++) {
        files[operation] = fopen(fileNames[operation], "w");
        fprintf(files[operation], "n");
        for (int structure = 0; structure < STRUCTURES; structure++) {
            fprintf(files[operation], ",s%d", structure + 1);
        }
        fprintf(files[operation], "\n");
    }
    for (int point = 0; point < DATA_POINTS; point++) {
        int n = 1 << (point + 3);
        for (int operation = 0; operation < OPERATIONS; operation++) {
            fprintf(files[operation], "%d", n);
            for (int structure = 0; structure < STRUCTURES; structure++) {
                long long steps = operationSteps(structure, operation, n);
                fprintf(files[operation], ",%lld", steps);
            }
            fprintf(files[operation], "\n");
        }
    }
    for (int operation = 0; operation < OPERATIONS; operation++) {
        fclose(files[operation]);
    }
}

void createGnuplotScript(void) {
    FILE *file = fopen("plot.gp", "w");
    fprintf(file, "set terminal png size 1400,900\n");
    fprintf(file, "set output 'dictionary_growth.png'\n");
    fprintf(file, "set datafile separator ','\n");
    fprintf(file, "set logscale xy\n");
    fprintf(file, "set grid\n");
    fprintf(file, "set key outside\n");
    fprintf(file, "set multiplot layout 4,2 title 'Dictionary Operation Growth'\n");
    for (int operation = 0; operation < OPERATIONS; operation++) {
        fprintf(file, "set title '%s'\n", operationNames[operation]);
        fprintf(file, "set xlabel 'Number of elements (n)'\n");
        fprintf(file, "set ylabel 'Operation count'\n");
        fprintf(file, "plot '%s' using 1:2 with linespoints title '%s', ",
                fileNames[operation], structureNames[0]);
        fprintf(file, "'%s' using 1:3 with linespoints title '%s', ",
                fileNames[operation], structureNames[1]);
        fprintf(file, "'%s' using 1:4 with linespoints title '%s', ",
                fileNames[operation], structureNames[2]);
        fprintf(file, "'%s' using 1:5 with linespoints title '%s', ",
                fileNames[operation], structureNames[3]);
        fprintf(file, "'%s' using 1:6 with linespoints title '%s', ",
                fileNames[operation], structureNames[4]);
        fprintf(file, "'%s' using 1:7 with linespoints title '%s'\n",
                fileNames[operation], structureNames[5]);
    }
    fprintf(file, "unset multiplot\n");
    fclose(file);
}
int main(void) {
    createCsvFiles();
    createGnuplotScript();
    printf("CSV files created.\n");
    printf("Gnuplot script created.\n");
    printf("Plot generated as dictionary_growth.png.\n");
    return 0;
}