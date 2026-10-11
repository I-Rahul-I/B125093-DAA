// Question 1:
//  [Fractional Knapsack with Deterioration Rate] You have n items with base values
// vi, weights wi, and decay rates λi > 0. If an item is consumed at time t, its effective
// value density decays to (vi/wi)−λi ·t. Knapsack capacity is W. Determine the optimal 
// scheduling order and fractional choices to maximise total value. By choosing the proper 
// input representation, write a program in C to validate your algorithm and derive the 
// complexity analysis of your algorithm


#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int id;
    double value;
    double weight;
    double lambda;
    double density;
    double decayFactor;   /* weight * lambda */
} Item;

/* Sort by decreasing w * lambda */
int compareItems(const void *a, const void *b) {
    Item *x = (Item *)a;
    Item *y = (Item *)b;
    if (x->decayFactor > y->decayFactor) return -1;
    if (x->decayFactor < y->decayFactor) return 1;
    return 0;
}

int main() {
    int n;
    double W;
    printf("Enter number of items and knapsack capacity: ");
    scanf("%d %lf", &n, &W);
    Item *items = (Item *)malloc(n * sizeof(Item));
    printf("Enter value, weight, and decay rate for each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf",&items[i].value,&items[i].weight,&items[i].lambda);
        items[i].id = i + 1;
        items[i].density = items[i].value / items[i].weight;
        items[i].decayFactor = items[i].weight * items[i].lambda;
    }

    qsort(items, n, sizeof(Item), compareItems);
    double remainingCapacity = W;
    double currentTime = 0.0;
    // Each item takes one unit of time to consume.
    double totalValue = 0.0;

    printf("\nOptimal scheduling order and fractional choices:\n");
    for (int i = 0; i < n && remainingCapacity > 0; i++) {
        double effectiveDensity = items[i].density - items[i].lambda * currentTime;
        if (effectiveDensity <= 0) {
            printf("Item %d: skip, effective density = %.4lf\n",items[i].id, effectiveDensity);
            continue;
        }
        double itemValue =items[i].weight * effectiveDensity;
        if (items[i].weight <= remainingCapacity) {
            totalValue += itemValue;
            remainingCapacity -= items[i].weight;
            printf("Item %d: take 1.000000 at time %.0lf, value gained = %.4lf\n",items[i].id,currentTime,itemValue);
            currentTime += 1.0;
        } else {
            double fraction =remainingCapacity / items[i].weight;
            double gainedValue =fraction * itemValue;
            totalValue += gainedValue;
            printf("Item %d: take %.6lf at time %.0lf, value gained = %.4lf\n",items[i].id,fraction,currentTime,gainedValue);
            remainingCapacity = 0;
            currentTime += 1.0;
        }
    }
    printf("\nMaximum total value: %.6lf\n", totalValue);
    free(items);
    return 0;
}

// Complexity Analysis:
// Time Complexity: O(n log n) for sorting + O(n) for the main loop = O(n log n)
// Space Complexity: O(n) for storing items