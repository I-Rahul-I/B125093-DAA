#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50
#define TRIALS 1000

void copy_array(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void bubble_early(int a[], int n, long long *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparisons)++;
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void bubble_full(int a[], int n, long long *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparisons)++;
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main() {
    int original[N], a1[N], a2[N];
    FILE *data = fopen("bubble_data.dat", "w");
    if (data == NULL) {
        perror("Unable to create data file");
        return 1;
    }

    srand((unsigned)time(NULL));

    for (int t = 1; t <= TRIALS; t++) {
        for (int i = 0; i < N; i++) {
            original[i] = rand() % 1000;
        }

        copy_array(a1, original, N);
        copy_array(a2, original, N);

        long long comp_early, comp_full;

        bubble_early(a1, N, &comp_early);
        bubble_full(a2, N, &comp_full);

        fprintf(data, "%d %lld %lld\n", t, comp_early, comp_full);
    }

    fclose(data);

    printf("Array size: %d\n", N);
    printf("Number of random trials: %d\n", TRIALS);

    FILE *gp = popen("gnuplot -persist", "w");
    if (gp == NULL) {
        perror("gnuplot not found");
        return 1;
    }

    fprintf(gp, "set title 'Bubble Sort Comparisons: Early Stop vs Full Pass'\n");
    fprintf(gp, "set xlabel 'Random Trial'\n");
    fprintf(gp, "set ylabel 'Number of Comparisons'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set style line 1 lc rgb 'blue' lt 1 lw 2\n");
    fprintf(gp, "set style line 2 lc rgb 'red' lt 1 lw 2\n");
    fprintf(gp, "plot 'bubble_data.dat' using 1:2 with lines ls 1 title 'Early Termination', \\\n");
    fprintf(gp, "     'bubble_data.dat' using 1:3 with lines ls 2 title 'Always n-1 Passes'\n");

    pclose(gp);
    return 0;
}