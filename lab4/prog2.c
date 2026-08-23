/*
Question 2:
Application of sorting-II: Given two sets S1 and S2 (each of size n), and a number x,
describe an O(n · logn) algorithm for finding whether there exists a pair of elements,
one from S1 and one from S2, that add up to x. By choosing the proper input
representation, write a program in C to validate your algorithm.

Algorithm:
1. Sort one of the sets (say S2) in ascending order. This takes O(n log n).
2. For each element a in S1:
   - Compute target = x - a
   - Binary search for target in the sorted S2 (O(log n))
   - If found, we have a pair (a, target) with a ∈ S1, target ∈ S2, and a + target = x
3. If no such pair is found after checking all elements of S1, report failure.

Complexity:
- Total time: O(n log n)
- Extra space: O(1) beyond input arrays

Pseudocode:
Algorithm ExistsPairSum(S1[1..n], S2[1..n], x):
    Input:  S1, S2 = two sets of n integers each
            x = target sum
    Output: A pair (a, b) with a ∈ S1, b ∈ S2, a + b = x, or report none exists
    1. Sort S2 in ascending order
    2. For i = 1 to n:
           a ← S1[i]
           target ← x - a
           If BinarySearch(S2, target) = true:
               Return (a, target)
    3. Return "No pair found"
Function BinarySearch(A[1..n], target):
    Input:  A = sorted array of n integers
            target = value to search for
    Output: true if target ∈ A, else false
    1. left ← 1
       right ← n
    2. While left ≤ right:
           mid ← left + (right - left) / 2
           If A[mid] = target:
               Return true
           Else if A[mid] < target:
               left ← mid + 1
           Else:
               right ← mid - 1

    3. Return false
*/
// CODE---
#include<stdio.h>
#include<stdlib.h>
int compare(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}
int binarysearch(int* arr, int length, int target){
    int left = 0;
    int right = length - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(arr[mid] == target){
            return 1; // milgaya
        }
        else if(arr[mid] < target){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return 0; //nhi mila
}
int main(){
    int length1;
    printf("Enter the number of items in set 1: ");
    scanf("%d", &length1);
    int* set1 = (int*)malloc(length1 * sizeof(int));
    printf("Enter the items in set 1: \n");
    for(int i = 0; i < length1; i++){
        scanf("%d", &set1[i]);
    }
    int length2;
    printf("Enter the number of items in set 2: ");
    scanf("%d", &length2);
    int* set2 = (int*)malloc(length2 * sizeof(int));
    printf("Enter the items in set 2: \n");
    for(int i = 0; i < length2; i++){
        scanf("%d", &set2[i]);
    }
    int x;
    printf("Enter the item to search for: ");
    scanf("%d", &x);
    qsort(set2, length2, sizeof(int),compare);
    for(int i=0;i<length1;i++){
        int found = binarysearch(set2, length2,x-set1[i]);
        if(found){
            printf("Pair found: (%d, %d)\n", set1[i], x-set1[i]);
            free(set1);
            free(set2);
            return 0;
        }
    }
    printf("No pair found.\n");
    return 0;
}