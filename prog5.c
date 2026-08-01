#include <stdio.h>

int transitionPoint(int arr[], int n) {
    int low = 0, high = n - 1;
    int ans = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == 1) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements (only 0s followed by 1s):\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i+1);
        scanf("%d", &arr[i]);
    }

    int pos = transitionPoint(arr, n);

    if (pos == -1) {
        printf("No transition point found. Array contains only 0s.\n");
    } else {
        printf("Transition point found at index: %d\n", pos);
    }

    return 0;
}