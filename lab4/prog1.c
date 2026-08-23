/*
Question 1:
Application of sorting-I: Assume that we are given n pairs of items as input, where the
first item is a number and the second item is one of three colours (red, blue, or yellow).
Further assume that the items are sorted by number. Give an O(n) algorithm to sort
the items by colour (all reds before all blues before all yellows) such that the numbers 
for identical colours stay sorted. By choosing the proper input representation, write a 
program in C to validate your algorithm.

ALGORITHM---
Read 𝑛
and the n items (number, colour) into an array arr, assumed sorted by number.
First pass: count how many items are red, blue, and yellow.
Allocate three arrays:
redarr of size redcount
bluearr of size bluecount
yellowarr of size yellowcount
Second pass: scan arr again and:
If item is red, copy it into redarr at the next red index
If blue, copy into bluearr
If yellow, copy into yellowarr
Maintain separate counters for each colour while filling.
Copy back into arr in order:
First all elements of redarr
Then all elements of bluearr
Then all elements of yellowarr
Print the resulting arr.
Total time: O(n), extra space: 𝑂(𝑛)


PSEUDOCODE--- SortItemsByColour(arr[1..n]):
    Input:  arr = array of n items
            each item = (number, colour)
            colour ∈ {"red", "blue", "yellow"}
            arr is sorted by number
    Output: arr reordered so that:
            all reds, then blues, then yellows,
            with numbers within each colour still sorted
    1. redcount ← 0
       bluecount ← 0
       yellowcount ← 0
    2. For i = 1 to n:
           If arr[i].colour = "red":
               redcount ← redcount + 1
           Else if arr[i].colour = "blue":
               bluecount ← bluecount + 1
           Else if arr[i].colour = "yellow":
               yellowcount ← yellowcount + 1
    3. Allocate:
           redarr[1..redcount]
           bluearr[1..bluecount]
           yellowarr[1..yellowcount]
    4. r ← 0
       b ← 0
       y ← 0
       For i = 1 to n:
           If arr[i].colour = "red":
               r ← r + 1
               redarr[r] ← arr[i]
           Else if arr[i].colour = "blue":
               b ← b + 1
               bluearr[b] ← arr[i]
           Else if arr[i].colour = "yellow":
               y ← y + 1
               yellowarr[y] ← arr[i]
    5. k ← 0
       For i = 1 to redcount:
           k ← k + 1
           arr[k] ← redarr[i]
       For i = 1 to bluecount:
           k ← k + 1
           arr[k] ← bluearr[i]
       For i = 1 to yellowcount:
           k ← k + 1
           arr[k] ← yellowarr[i]
    6. Return arr
*/

// CODE---
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
    int num;
    char colour[7];
} items;
int main(){
    int length;
    printf("Enter the number of items: ");
    scanf("%d",&length);
    items arr[length];
    printf("enter items in sorted order of number\n");
    for(int i=0;i<length;i++){
        printf("Enter the item %d: ",i+1);
        scanf("%d",&arr[i].num);
        printf("Enter the colour of item %d: ",i+1);
        scanf("%s",arr[i].colour);
    }

    int redcount = 0, bluecount = 0, yellowcount = 0;
    //counting colours
    for(int i=0;i<length;i++){
        if(strcmp(arr[i].colour,"red")==0){
            redcount++;
        }
        else if(strcmp(arr[i].colour,"blue")==0){
            bluecount++;
        }
        else if(strcmp(arr[i].colour,"yellow")==0){
            yellowcount++;
        }
    }
    items* redarr = (items*)malloc(redcount * sizeof(items));
    items* bluearr = (items*)malloc(bluecount * sizeof(items));
    items* yellowarr = (items*)malloc(yellowcount * sizeof(items));
    redcount = 0, bluecount = 0, yellowcount = 0;
    for(int i=0;i<length;i++){
        if(strcmp(arr[i].colour,"red")==0){
            redarr[redcount].num = arr[i].num;
            strcpy(redarr[redcount].colour,arr[i].colour);
            redcount++;
        }
        else if(strcmp(arr[i].colour,"blue")==0){
            bluearr[bluecount].num = arr[i].num;
            strcpy(bluearr[bluecount].colour,arr[i].colour);
            bluecount++;
        }
        else if(strcmp(arr[i].colour,"yellow")==0){
            yellowarr[yellowcount].num = arr[i].num;
            strcpy(yellowarr[yellowcount].colour,arr[i].colour);
            yellowcount++;
        }
    }
    for(int a=0;a<redcount;a++){
        arr[a] = redarr[a];
    }
    for(int b=0;b<bluecount;b++){
        arr[redcount+b] = bluearr[b];
    }
    for(int c=0;c<yellowcount;c++){
        arr[redcount+bluecount+c] = yellowarr[c];
    }
    free(redarr);
    free(bluearr);
    free(yellowarr);
    printf("Sorted items by colour:\n");
    for(int i=0;i<length;i++){  
        printf("Item %d: Number = %d, Colour = %s\n",i+1,arr[i].num,arr[i].colour);
    }
    return 0;
}