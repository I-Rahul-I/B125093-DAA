/*
Question 3:
Application of sorting-III: Given a set S of n integers and an integer T,
give an O(n^{k-1} · log n) algorithm to test whether k of the integers in S
add up to T. By choosing the proper input representation, write a program in C
to validate your algorithm.

Algorithm (for general k, conceptual):
1. Sort S in ascending order. This takes O(n log n).
2. Use a recursive procedure kSum(S, k, T):
   - Base case k = 2:
       Use the two-pointer technique on the sorted array to check if any pair sums to T.
       This runs in O(n).
   - Recursive case k > 2:
       For each element a in S (with index i from 0 to n−1):
           - Let T' = T - a
           - Recursively solve (k-1)-Sum on the subarray S[i+1 .. n-1] with target T'
       If any recursive call returns true, then a solution exists.

Complexity:
- In general, this yields O(n^{k-1}) after sorting, which is within O(n^{k-1} · log n).

Pseudocode :
Algorithm KSumExists(S[1..n], k, T):
    Input:  S = array of n integers
            k = number of elements to sum
            T = target sum
    Output: true if some k distinct elements of S sum to T, else false
    1. Sort S in ascending order
    2. Return KSumRecursive(S, 0, n-1, k, T)
Function KSumRecursive(S, left, right, k, T):
    Input:  S = sorted array
            left, right = current subarray bounds [left, right]
            k = number of elements to pick
            T = target sum
    Output: true if some k elements in S[left..right] sum to T
    1. If k == 2:
           Return TwoSumExists(S, left, right, T)
    2. For i from left to right - (k - 1):
           a ← S[i]
           If KSumRecursive(S, i + 1, right, k - 1, T - a) = true:
               Return true
    3. Return false
Function TwoSumExists(S, left, right, T):
    Input:  S = sorted array
            left, right = bounds
            T = target sum
    Output: true if some pair in S[left..right] sums to T
    1. l ← left
       r ← right
    2. While l < r:
           sum ← S[l] + S[r]
           If sum = T:
               Return true
           Else if sum < T:
               l ← l + 1
           Else:
               r ← r - 1
    3. Return false

Pseudocode :
Algorithm KSumSlidingWindow(S[1..n], k, T):
    Input:  S = array of n integers
            k = size of group
            T = target sum
    Output: true if some contiguous block of k elements in sorted S sums to T
    1. Sort S in ascending order
    2. sum ← S[1] + S[2] + ... + S[k]
    3. If sum = T:
           Return true
    4. For i from k+1 to n:
           sum ← sum - S[i-k] + S[i]
           If sum = T:
               Return true
           Else if sum > T:
               Break  // optional optimization for non-negative numbers

    5. Return false
*/

// CODE---
#include<stdio.h>
#include<stdlib.h>
int compare(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}
int main(){
    int length;
    printf("Enter the number of items in set: ");
    scanf("%d",&length);
    int* set = (int*)malloc(length * sizeof(int));
    for(int i=0;i<length;i++){
        printf("Enter item %d: ",i+1);
        scanf("%d",&set[i]);
    }
    qsort(set,length,sizeof(int),compare);
    int t;
    printf("enter value of t : ");
    scanf("%d",&t);
    int k;
    printf("enter value of k : ");
    scanf("%d",&k);
    int sum=0;
    for(int i=0;i<k;i++){
        sum+=set[i];
    }
    if(sum==t){
        free(set);
        printf("there exists a group of %d integers",k);
        return 0;
    }
    for(int i=k;i<length;i++){
        sum-=set[i-k];
        sum+=set[i];
        if(sum==t){
            free(set);
            printf("there exists a group of %d integers",k);
            return 0;
        }
        else if(sum>t){
            break;
        }
    }
    free(set);
    printf("no such group exists\n");
    return 0;
}