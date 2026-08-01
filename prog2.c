#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int trials = 1000;
    int fair_heads = 0, fair_tails = 0;
    int biased_heads = 0, biased_tails = 0;
    double theta = 0.2;   // biased coin: P(H) = 0.5 + theta = 0.7

    FILE *data = fopen("coin_compare.dat", "w");
    if (data == NULL) {
        perror("Unable to create data file");
        return 1;
    }

    srand(time(NULL));

    for (int i = 1; i <= trials; i++) {
        int fair_flip = rand() % 2;   // 0 = HEAD, 1 = TAIL
        if (fair_flip == 0) {
            fair_heads++;
        } else {
            fair_tails++;
        }

        double r = (double)rand() / RAND_MAX;
        int biased_flip = (r < (0.5 + theta)) ? 0 : 1;   // 0 = HEAD, 1 = TAIL
        if (biased_flip == 0) {
            biased_heads++;
        } else {
            biased_tails++;
        }

        double fair_prob = (double)fair_heads / i;
        double biased_prob = (double)biased_heads / i;

        fprintf(data, "%d %.5f %.5f\n", i, fair_prob, biased_prob);
    }

    fclose(data);

    printf("Total tosses: %d\n", trials);
    printf("\nFair coin:\n");
    printf("Heads: %d\n", fair_heads);
    printf("Tails: %d\n", fair_tails);
    printf("Probability of HEAD: %.5f\n", (double)fair_heads / trials);
    printf("Probability of TAIL: %.5f\n", (double)fair_tails / trials);

    printf("\nBiased coin:\n");
    printf("Heads: %d\n", biased_heads);
    printf("Tails: %d\n", biased_tails);
    printf("Probability of HEAD: %.5f\n", (double)biased_heads / trials);
    printf("Probability of TAIL: %.5f\n", (double)biased_tails / trials);

    FILE *gp = popen("gnuplot -persist", "w");
    if (gp == NULL) {
        perror("gnuplot not found");
        return 1;
    }

    fprintf(gp, "set title 'Fair Coin vs Biased Coin'\n");
    fprintf(gp, "set xlabel 'Number of Trials'\n");
    fprintf(gp, "set ylabel 'Running Probability of Head'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set yrange [0:1]\n");
    fprintf(gp, "plot 'coin_compare.dat' using 1:2 with lines title 'Fair Coin', \\\n");
    fprintf(gp, "     'coin_compare.dat' using 1:3 with lines title 'Biased Coin'\n");

    pclose(gp);
    return 0;
}