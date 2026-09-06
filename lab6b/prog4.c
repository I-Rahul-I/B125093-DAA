// QUESTION 4
// Sorting via reversal procedure
//
// Given a permutation of 1...n, the only operation allowed is:
// reverse(p, i, j)
//
// Part 1:
// Show that any permutation can be sorted using O(n) reversals.
//
// Part 2:
// If the cost of reverse(p,i,j) is |j-i|+1,
// design an algorithm with total cost O(n log^2 n).
//
// This program implements both algorithms.

#include <stdio.h>

#define MAX 100

int total_cost = 0;
int total_reversals = 0;

// ================================================================
// Reverse elements from index i to j
// ================================================================
void reverse_range(int a[], int i, int j)
{
    if (i >= j)
        return;

    // Cost of this reversal
    total_cost += (j - i + 1);
    total_reversals++;

    while (i < j)
    {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;

        i++;
        j--;
    }
}

// ================================================================
// Reset counters
// ================================================================
void reset_counters()
{
    total_cost = 0;
    total_reversals = 0;
}

// ================================================================
// Print array
// ================================================================
void print_array(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

// ================================================================
// PART 1
//
// O(n) REVERSALS
//
// At position i, find element i+1 in the remaining portion.
// Reverse the range from i to its current position.
//
// After the reversal, i+1 is placed at position i.
//
// At most one reversal is performed for every position,
// so there are at most n-1 reversals.
// ================================================================
void sort_by_linear_reversals(int a[], int n)
{
    reset_counters();

    for (int i = 0; i < n - 1; i++)
    {
        int target = i + 1;
        int target_index = i;

        // Find target element
        for (int j = i; j < n; j++)
        {
            if (a[j] == target)
            {
                target_index = j;
                break;
            }
        }

        // Put target into position i
        if (target_index != i)
        {
            reverse_range(a, i, target_index);
        }
    }

    printf("\n========================================\n");
    printf("PART 1: O(n) REVERSALS ALGORITHM\n");
    printf("========================================\n");

    printf("Sorted array: ");
    print_array(a, n);

    printf("Number of reversals = %d\n", total_reversals);
    printf("Maximum possible reversals = %d\n", n - 1);
    printf("Total reversal cost = %d\n", total_cost);
}

// ================================================================
// PART 2
//
// STABLE PARTITION USING ONLY REVERSALS
//
// We partition a[l...r] according to:
//
//        a[i] <= value
//
// The recursive partition produces:
//
//        TRUE FALSE | TRUE FALSE
//
// We need:
//
//        TRUE TRUE | FALSE FALSE
//
// To do this, rotate the middle two blocks using 3 reversals:
//
//        A B C D
//
// where B = FALSE block on left
//       C = TRUE block on right
//
// becomes:
//
//        A C B D
//
// using:
//
//        reverse(B)
//        reverse(C)
//        reverse(B+C)
//
// The function returns the NUMBER of TRUE elements.
// ================================================================
int stable_partition(int a[], int l, int r, int value)
{
    // Base case: one element
    if (l == r)
    {
        if (a[l] <= value)
            return 1;
        else
            return 0;
    }

    int mid = (l + r) / 2;

    // Partition left half
    int left_true = stable_partition(a, l, mid, value);

    // Partition right half
    int right_true = stable_partition(a, mid + 1, r, value);

    // Boundaries of the middle blocks
    //
    // Left half:
    // [ TRUE ... ][ FALSE ... ]
    //
    // Right half:
    // [ TRUE ... ][ FALSE ... ]
    //
    // We need to rotate:
    //
    // [FALSE(left)][TRUE(right)]
    //
    // into:
    //
    // [TRUE(right)][FALSE(left)]

    int first_false_left = l + left_true;
    int first_false_right = mid + 1 + right_true;

    // Reverse FALSE block of left half
    reverse_range(a, first_false_left, mid);

    // Reverse TRUE block of right half
    reverse_range(a, mid + 1, first_false_right - 1);

    // Reverse the combined block
    reverse_range(a, first_false_left, first_false_right - 1);

    // Total number of TRUE elements
    return left_true + right_true;
}

// ================================================================
// PART 2 SORT
//
// Values in a[l...r] are assumed to be exactly:
//
//        low, low+1, ..., high
//
// Partition around the middle value:
//
//        value = (low + high) / 2
//
// Left side gets values <= value.
// Right side gets values > value.
//
// Then recursively sort both sides.
// ================================================================
void sort_by_bounded_cost(int a[],
                          int l,
                          int r,
                          int low,
                          int high)
{
    // Nothing to sort
    if (l >= r || low >= high)
        return;

    // Divide value range into two approximately equal parts
    int value = (low + high) / 2;

    // Stable partition based on value
    int number_left = stable_partition(a, l, r, value);

    // Position where right part starts
    int split = l + number_left;

    // Sort values low ... value
    sort_by_bounded_cost(a,
                         l,
                         split - 1,
                         low,
                         value);

    // Sort values value+1 ... high
    sort_by_bounded_cost(a,
                         split,
                         r,
                         value + 1,
                         high);
}

// ================================================================
// Run Part 2
// ================================================================
void run_bounded_cost_algorithm(int a[], int n)
{
    reset_counters();

    sort_by_bounded_cost(a, 0, n - 1, 1, n);

    printf("\n========================================\n");
    printf("PART 2: O(n log^2 n) COST ALGORITHM\n");
    printf("========================================\n");

    printf("Sorted array: ");
    print_array(a, n);

    printf("Number of reversals = %d\n", total_reversals);
    printf("Total reversal cost = %d\n", total_cost);
}

// ================================================================
// Check whether array is sorted
// ================================================================
int is_sorted(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != i + 1)
            return 0;
    }

    return 1;
}

// ================================================================
// MAIN
// ================================================================
int main()
{
    int n;
    int original[MAX];
    int test_array[MAX];

    printf("Enter number of elements: ");

    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX)
    {
        printf("Invalid input size.\n");
        return 1;
    }

    printf("Enter permutation of 1 to %d:\n", n);

    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &original[i]) != 1)
        {
            printf("Invalid input.\n");
            return 1;
        }
    }

    // ============================================================
    // Test Part 1
    // ============================================================

    for (int i = 0; i < n; i++)
        test_array[i] = original[i];

    sort_by_linear_reversals(test_array, n);

    if (is_sorted(test_array, n))
        printf("Correctness check: PASSED\n");
    else
        printf("Correctness check: FAILED\n");

    // ============================================================
    // Test Part 2
    // ============================================================

    for (int i = 0; i < n; i++)
        test_array[i] = original[i];

    run_bounded_cost_algorithm(test_array, n);

    if (is_sorted(test_array, n))
        printf("Correctness check: PASSED\n");
    else
        printf("Correctness check: FAILED\n");

    return 0;
}
