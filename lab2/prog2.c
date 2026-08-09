// QUESTION 2:
// Merge sort vs. modified merge sort: Consider the following modification to merge
// sort: divide the input array into thirds (rather than halves), recursively sort each third,
// and finally combine the results using a three-way merge subroutine. What is the worst-case
// running time of this modified merge sort?
// Write a C program to validate your claim by plotting the order of growth for both the
// merge sort (discussed in the class) and the modified merge sort described above.



// CODE:---
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
long long merge_sort_steps = 0;
long long merge_sort_3way_steps = 0;
int *generate_random_array(int size){
    int *array = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = rand();
    }
    return array;
}

void merge(int array[], int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
        merge_sort_steps++;
    }
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
        merge_sort_steps++;
    }
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
        merge_sort_steps++;
    }
    free(L);
    free(R);
}

void merge_sort(int array[], int left, int right){
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(array, left, mid);
        merge_sort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void merge_3way(int array[],int left,int mid1,int mid2,int right){
    int n1 = mid1 - left + 1;
    int n2 = mid2 - mid1;
    int n3 = right - mid2;
    int *L = malloc(n1 * sizeof(int));
    int *M = malloc(n2 * sizeof(int));
    int *R = malloc(n3 * sizeof(int));
    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
    }
    for (int i = 0; i < n2; i++) {
        M[i] = array[mid1 + 1 + i];
    }
    for (int i = 0; i < n3; i++) {
        R[i] = array[mid2 + 1 + i];
    }
    int i = 0;
    int j = 0;
    int k = 0;
    int position = left;
    while (i < n1 && j < n2 && k < n3) {
        if (L[i] <= M[j] && L[i] <= R[k]) {
            array[position++] = L[i++];
        } else if (M[j] <= L[i] && M[j] <= R[k]) {
            array[position++] = M[j++];
        } else {
            array[position++] = R[k++];
        }
        merge_sort_3way_steps++;
    }
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            array[position++] = L[i++];
        } else {
            array[position++] = M[j++];
        }
        merge_sort_3way_steps++;
    }
    while (j < n2 && k < n3) {
        if (M[j] <= R[k]) {
            array[position++] = M[j++];
        } else {
            array[position++] = R[k++];
        }
        merge_sort_3way_steps++;
    }
    while (i < n1 && k < n3) {
        if (L[i] <= R[k]) {
            array[position++] = L[i++];
        } else {
            array[position++] = R[k++];
        }
        merge_sort_3way_steps++;
    }
    while (i < n1) {
        array[position++] = L[i++];
        merge_sort_3way_steps++;
    }
    while (j < n2) {
        array[position++] = M[j++];
        merge_sort_3way_steps++;
    }
    while (k < n3) {
        array[position++] = R[k++];
        merge_sort_3way_steps++;
    }
    free(L);
    free(M);
    free(R);
}

void merge_sort_3way(int array[], int left, int right){
    int length = right - left + 1;
    if (length <= 1) {
        return;
    }
    if (length == 2) {
        if (array[left] > array[right]) {
            int temp = array[left];
            array[left] = array[right];
            array[right] = temp;
        }
        merge_sort_3way_steps++;
        return;
    }
    int first_part_size = length / 3;
    int second_part_size = length / 3;
    int mid1 = left + first_part_size - 1;
    int mid2 = mid1 + second_part_size;
    merge_sort_3way(array, left, mid1);
    merge_sort_3way(array, mid1 + 1, mid2);
    merge_sort_3way(array, mid2 + 1, right);
    merge_3way(array, left, mid1, mid2, right);
}

void create_plot(void){
    FILE *gnuplot = popen("gnuplot -persist", "w");
    if (gnuplot == NULL) {
        perror("GNUplot could not be started");
        return;
    }
    fprintf(gnuplot, "set title 'Two-Way Merge Sort vs Three-Way Merge Sort'\n");
    fprintf(gnuplot, "set xlabel 'Array Size'\n");
    fprintf(gnuplot, "set ylabel 'Number of Steps'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "set key outside\n");
    fprintf(
        gnuplot,
        "plot 'merge_compare.dat' using 1:2 "
        "with linespoints lw 2 title 'Two-Way Merge Sort', "
        "'merge_compare.dat' using 1:3 "
        "with linespoints lw 2 title 'Three-Way Merge Sort'\n"
    );
    fflush(gnuplot);
    pclose(gnuplot);
}

int main(void){
    int number_of_trials;
    printf("Enter the number of trials: ");
    scanf("%d", &number_of_trials);
    FILE *data_file = fopen("merge_compare.dat", "w");
    if (data_file == NULL) {
        perror("Unable to create merge_compare.dat");
        return EXIT_FAILURE;
    }
    srand((unsigned int) time(NULL));
    fprintf(
        data_file,
        "# ArraySize TwoWayMergeSortSteps ThreeWayMergeSortSteps\n"
    );
    for (int size = 1; size <= number_of_trials; size++) {
        int *original_array = generate_random_array(size);
        int *array_for_merge_sort = malloc(size * sizeof(int));
        int *array_for_3way_sort = malloc(size * sizeof(int));
        memcpy(
            array_for_merge_sort,
            original_array,
            size * sizeof(int)
        );
        memcpy(
            array_for_3way_sort,
            original_array,
            size * sizeof(int)
        );
        merge_sort_steps = 0;
        merge_sort_3way_steps = 0;
        merge_sort(array_for_merge_sort, 0, size - 1);
        merge_sort_3way(array_for_3way_sort, 0, size - 1);
        fprintf(data_file,"%d %lld %lld\n",size,merge_sort_steps,merge_sort_3way_steps);
        free(original_array);
        free(array_for_merge_sort);
        free(array_for_3way_sort);
    }
    fclose(data_file);
    printf("\nData saved to merge_compare.dat\n");
    printf("Starting GNUplot...\n");
    create_plot();
    return EXIT_SUCCESS;
}