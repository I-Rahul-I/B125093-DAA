// Question 3:
//  [Minimum Initial Fuel (Reverse Greedy)] A vehicle needs to reach the target D
// starting with fuel F. Along the way are stations (di,fi) (distance from origin and 
// refuel amount). What is the minimum number of refuelling stops required to reach the 
// target? By choosing the proper input representation, write a program in C to validate
// your algorithm and derive the complexity analysis of your algorithm

#include <stdio.h>
#include <stdlib.h>
#define MILEAGE 10   /* 1 litre = 10 km */
typedef struct {
    int distance;
    int fuel;
} Station;
/* Max-heap implementation */
void swap(int *a, int *b) {
    int temp = *a; *a = *b;
    *b = temp;
}
void heapifyUp(int heap[], int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] >= heap[index]) break;
        swap(&heap[parent], &heap[index]);
        index = parent;
    }
}
void heapifyDown(int heap[], int size, int index) {
    while (1) {
        int largest = index; int left = 2 * index + 1; int right = 2 * index + 2;
        if (left < size && heap[left] > heap[largest]) largest = left;
        if (right < size && heap[right] > heap[largest]) largest = right;
        if (largest == index) break;
        swap(&heap[index], &heap[largest]);
        index = largest;
    }
}
void insertHeap(int heap[], int *size, int value) {
    heap[*size] = value;
    heapifyUp(heap, *size);
    (*size)++;
}
int extractMax(int heap[], int *size) {
    int maxValue = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapifyDown(heap, *size, 0);
    return maxValue;
}
/* Sort stations by increasing distance */
int compareStations(const void *a, const void *b) {
    Station *x = (Station *)a;
    Station *y = (Station *)b;
    return x->distance - y->distance;
}
int minimumRefuellingStops(Station stations[], int n, int D, int F) {
    /* Add target as a station with fuel 0.
        This lets us treat reaching D exactly like reaching another station.*/
    Station *points = (Station *)malloc((n + 1) * sizeof(Station));
    for (int i = 0; i < n; i++) points[i] = stations[i];
    points[n].distance = D;
    points[n].fuel = 0;
    qsort(points, n + 1, sizeof(Station), compareStations);
    int *maxHeap = (int *)malloc((n + 1) * sizeof(int));
    int heapSize = 0; int fuelLeft = F; int stops = 0;
    for (int i = 0; i <= n; i++) {
/*Fuel required to travel from previous point to current point, in litres.*/
        int distanceGap;
        if (i == 0) distanceGap = points[i].distance;
        else distanceGap = points[i].distance - points[i - 1].distance;
        fuelLeft -= distanceGap / MILEAGE;
/*While we cannot reach the current point,refuel using the largest fuel station already passed.*/
        while (fuelLeft < 0) {
            if (heapSize == 0) {
                free(points); free(maxHeap);
                return -1;
            }
            fuelLeft += extractMax(maxHeap, &heapSize);
            stops++;
        }
        /* Current station becomes available for future refuelling */
        insertHeap(maxHeap, &heapSize, points[i].fuel);
    }
    free(points);
    free(maxHeap);
    return stops;
}
int main() {
    int D, F, n;
    printf("Enter target distance D in km: ");
    scanf("%d", &D);
    printf("Enter initial fuel F in litres: ");
    scanf("%d", &F);
    printf("Enter number of stations: ");
    scanf("%d", &n);
    Station *stations = (Station *)malloc(n * sizeof(Station));
    printf("Enter distance and fuel for each station:\n");
    for (int i = 0; i < n; i++) scanf("%d %d", &stations[i].distance, &stations[i].fuel);
    int answer = minimumRefuellingStops(stations, n, D, F);
    if (answer == -1) printf("Not possible to reach the target.\n");
    else printf("Minimum number of refuelling stops: %d\n", answer);
    free(stations);
    return 0;
}