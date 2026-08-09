// QUESTION 3:
// Merging k sorted arrays: Suppose you are given k sorted arrays, each with n elements,
// and you want to combine them into a single sorted array of kn elements.
// (a) [Method 1] One approach is to use the merge subroutine repeatedly, merging the first
// two arrays, then merging the result with the third array, then with the fourth array,
// and so on until you merge in the kth and final input array. Write a program to validate
// this idea. Also, find the worst-case running time of this method.
// (b) [Method 2] Consider the algorithm that first divides the k arrays into k
// 2 pairs of arrays
// and uses the merge subroutine to combine each pair, resulting in k
// 2 sorted-length2n
// arrays. The algorithm repeats this step until there is only one length-kn sorted array.
// Write a program to validate this idea. What is the running time of this method as a
// function of n and k?



// CODE:---
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif
long long mergeArrays(const int first[],int firstSize,const int second[],int secondSize,int result[]) {
    int i = 0;
    int j = 0;
    int k = 0;
    long long steps = 0;
    while (i < firstSize && j < secondSize) {
        steps++;
        if (first[i] <= second[j]) {
            result[k] = first[i];
            i++;
        } else {
            result[k] = second[j];
            j++;
        }
        k++;
        steps++;
    }
    while (i < firstSize) {
        result[k] = first[i];
        i++;
        k++;
        steps++;
    }
    while (j < secondSize) {
        result[k] = second[j];
        j++;
        k++;
        steps++;
    }
    return steps;
}
int **createSortedArrays(int numberOfArrays, int arrayLength) {
    int **arrays = malloc(numberOfArrays * sizeof(int *));
    for (int i = 0; i < numberOfArrays; i++) {
        arrays[i] = malloc(arrayLength * sizeof(int));
        for (int j = 0; j < arrayLength; j++) {
            arrays[i][j] = j * numberOfArrays + i;
        }
    }
    return arrays;
}
void freeArrays(int **arrays, int numberOfArrays) {
    for (int i = 0; i < numberOfArrays; i++) {
        free(arrays[i]);
    }
    free(arrays);
}
long long methodOne(int **arrays, int numberOfArrays, int arrayLength) {
    int currentSize = arrayLength;
    int *result = malloc(currentSize * sizeof(int));
    long long steps = 0;
    for (int i = 0; i < arrayLength; i++) {
        result[i] = arrays[0][i];
        steps++;
    }
    for (int i = 1; i < numberOfArrays; i++) {
        int newSize =  currentSize + arrayLength;
        int *merged = malloc(newSize * sizeof(int));
        steps += mergeArrays(
            result,
            currentSize,
            arrays[i],
            arrayLength,
            merged
        );
        free(result);
        result = merged;
        currentSize = newSize;
    }
    free(result);
    return steps;
}
long long methodTwo(int **arrays, int numberOfArrays, int arrayLength) {
    int **currentArrays = malloc(numberOfArrays * sizeof(int *));
    int *currentSizes = malloc(numberOfArrays * sizeof(int));
    long long steps = 0;
    int currentCount = numberOfArrays;
    for (int i = 0; i < numberOfArrays; i++) {
        currentArrays[i] = malloc(arrayLength * sizeof(int));
        currentSizes[i] = arrayLength;
        for (int j = 0; j < arrayLength; j++) {
            currentArrays[i][j] = arrays[i][j];
            steps++;
        }
    }
    while (currentCount > 1) {
        int nextCount = (currentCount + 1) / 2;
        int **nextArrays = malloc(nextCount * sizeof(int *));
        int *nextSizes = malloc(nextCount * sizeof(int));
        int nextIndex = 0;
        for (int i = 0; i < currentCount; i += 2) {
            if (i + 1 < currentCount) {
                int newSize = currentSizes[i] + currentSizes[i + 1];
                nextArrays[nextIndex] = malloc(newSize * sizeof(int));
                nextSizes[nextIndex] = newSize;
                steps += mergeArrays(
                    currentArrays[i],
                    currentSizes[i],
                    currentArrays[i + 1],
                    currentSizes[i + 1],
                    nextArrays[nextIndex]
                );
                free(currentArrays[i]);
                free(currentArrays[i + 1]);
            } else {
                nextArrays[nextIndex] = currentArrays[i];
                nextSizes[nextIndex] = currentSizes[i];
            }
            nextIndex++;
        }
        free(currentArrays);
        free(currentSizes);
        currentArrays = nextArrays;
        currentSizes = nextSizes;
        currentCount = nextCount;
    }
    free(currentArrays[0]);
    free(currentArrays);
    free(currentSizes);
    return steps;
}
void createDataFile(int arrayLength, int maximumArrays) {
    FILE *file = fopen("merge_methods.dat", "w");
    fprintf(file, "# NumberOfArrays Method1Steps Method2Steps\n");
    for (int numberOfArrays = 2;
         numberOfArrays <= maximumArrays;
         numberOfArrays++) {

        int **arrays = createSortedArrays(
            numberOfArrays,
            arrayLength
        );
        long long methodOneSteps = methodOne(
            arrays,
            numberOfArrays,
            arrayLength
        );
        long long methodTwoSteps = methodTwo(
            arrays,
            numberOfArrays,
            arrayLength
        );
        fprintf(
            file,
            "%d %lld %lld\n",
            numberOfArrays,
            methodOneSteps,
            methodTwoSteps
        );
        freeArrays(arrays, numberOfArrays);
    }
    fclose(file);
}
void plotGraph(void) {
    FILE *gnuplot = popen("gnuplot -persist", "w");
    fprintf(gnuplot, "set terminal windows size 1000,700\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "set logscale xy\n");
    fprintf(gnuplot, "set xlabel 'Number of sorted arrays (k)'\n");
    fprintf(gnuplot, "set ylabel 'Measured merge steps'\n");
    fprintf(gnuplot, "set title 'Actual Comparison of Two Merging Methods'\n");
    fprintf(gnuplot, "set key outside\n");
    fprintf(
        gnuplot,
        "plot 'merge_methods.dat' using 1:2 "
        "with linespoints linewidth 2 "
        "title 'Method 1: Sequential merging', "
        "'merge_methods.dat' using 1:3 "
        "with linespoints linewidth 2 "
        "title 'Method 2: Pairwise merging'\n"
    );
    fflush(gnuplot);
    pclose(gnuplot);
}
int main(void) {
    int arrayLength;
    int maximumArrays;
    printf("Enter the length of each sorted array: ");
    scanf("%d", &arrayLength);
    printf("Enter the maximum number of arrays: ");
    scanf("%d", &maximumArrays);
    createDataFile(arrayLength, maximumArrays);
    plotGraph();
    printf("Actual merge results written to merge_methods.dat.\n");
    return 0;
}