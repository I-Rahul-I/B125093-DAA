#include <stdio.h>
#include <stdlib.h>

long long hanoi_moves(int n) {
    if (n == 1) {
        return 1;
    }
    return 2 * hanoi_moves(n - 1) + 1;
}

int main() {
    int n_max;
    printf("Enter the maximum number of discs: ");
    scanf("%d", &n_max);
    FILE *data = fopen("hanoi_data.dat", "w");
    if (data == NULL) {
        perror("Unable to create data file");
        return 1;
    }

    for (int n = 1; n <= n_max; n++) {
        long long moves = hanoi_moves(n);
        fprintf(data, "%d %lld\n", n, moves);
        printf("Discs: %d, Moves: %lld\n", n, moves);
    }

    fclose(data);

    FILE *gp = popen("gnuplot -persist", "w");
    if (gp == NULL) {
        perror("gnuplot not found");
        return 1;
    }

    fprintf(gp, "set title 'Tower of Hanoi: Number of Moves vs Discs'\n");
    fprintf(gp, "set xlabel 'Number of Discs'\n");
    fprintf(gp, "set ylabel 'Total Moves'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set logscale y\n");
    fprintf(gp, "plot 'hanoi_data.dat' using 1:2 with linespoints title 'Moves'\n");

    pclose(gp);
    return 0;
}