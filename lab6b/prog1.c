// Question 1: 
// D array operations and their complexities: Given an array with n unsorted integer elements, what is the worst-case complexity of the following problems in terms of n: (i) Finding the maximum element. (ii) Finding the first and second largest elements. (iii) Finding the mean. (iv) Finding the median. (v) Finding the standard deviation. (vi) Finding the mode. (vii) Removing all duplicates. (viii) Reversing the elements of the array. (ix) Partitioning the array with respect to a given random pivot element so that all elements less than the pivot appear after all the elements greater than or equal to the pivot. By choosing the proper input representation, write a program in C to validate your procedures and derive the corresponding complexity analysis.
#include<stdio.h>
#include<math.h>
//Function to print array
void printArray(int a[],int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");
}
//Function to sort array using Bubble Sort
void sort(int a[],int n)
{
    int i,j,temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}
int main()
{
    int a[100],b[100];
    int n,i,j;
    //Input number of elements
    printf("Enter number of elements: ");
    scanf("%d",&n);
    //Input array elements
    printf("Enter array elements:\n");
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    //1. Finding maximum element
    int max=a[0];
    for(i=1;i<n;i++)
    {
        if(a[i]>max)
            max=a[i];
    }
    printf("\nMaximum = %d\n",max);
    //2. Finding first and second largest elements
    int first=a[0],second=a[1];
    if(second>first)
    {
        int temp=first;
        first=second;
        second=temp;
    }
    for(i=2;i<n;i++)
    {
        if(a[i]>first)
        {
            second=first;
            first=a[i];
        }
        else if(a[i]>second && a[i]!=first)
            second=a[i];
    }
    printf("First Largest = %d\n",first);
    printf("Second Largest = %d\n",second);
    //3. Finding mean
    float sum=0,mean;
    for(i=0;i<n;i++)
        sum+=a[i];
    mean=sum/n;
    printf("Mean = %.2f\n",mean);
    //4. Finding median
    for(i=0;i<n;i++)
        b[i]=a[i];
    sort(b,n);
    float median;
    if(n%2==0)
        median=(b[n/2-1]+b[n/2])/2.0;
    else
        median=b[n/2];
    printf("Median = %.2f\n",median);
    //5. Finding standard deviation
    float variance=0,sd;

    for(i=0;i<n;i++)
        variance+=(a[i]-mean)*(a[i]-mean);

    variance=variance/n;
    sd=sqrt(variance);

    printf("Standard Deviation = %.2f\n",sd);

    //6. Finding mode
    int mode=a[0],maxCount=0;
    for(i=0;i<n;i++)
    {
        int count=0;

        for(j=0;j<n;j++)
        {
            if(a[i]==a[j])
                count++;
        }

        if(count>maxCount)
        {
            maxCount=count;
            mode=a[i];
        }
    }
    printf("Mode = %d\n",mode);
    //7. Removing duplicates
    int unique[100],size=0;
    for(i=0;i<n;i++)
    {
        int found=0;

        for(j=0;j<size;j++)
        {
            if(a[i]==unique[j])
            {
                found=1;
                break;
            }
        }

        if(!found)
        {
            unique[size]=a[i];
            size++;
        }
    }
    printf("Array after removing duplicates:\n");
    printArray(unique,size);
    //8. Reversing array
    for(i=0;i<n;i++)
        b[i]=a[i];
    for(i=0;i<n/2;i++)
    {
        int temp=b[i];
        b[i]=b[n-i-1];
        b[n-i-1]=temp;
    }
    printf("Reversed Array:\n");
    printArray(b,n);
    //9. Partitioning array using pivot
    int pivot;
    printf("Enter pivot element: ");
    scanf("%d",&pivot);
    int partition[100];
    int k=0;
    //Store elements greater than or equal to pivot first
    for(i=0;i<n;i++)
    {
        if(a[i]>=pivot)
            partition[k++]=a[i];
    }
    //Store elements less than pivot after them
    for(i=0;i<n;i++)
    {
        if(a[i]<pivot)
            partition[k++]=a[i];
    }
    printf("Partitioned Array:\n");
    printArray(partition,n);
    return 0;
}