// Question 3
// Convolution operation on vectors of size n: The convolution of two vectors A and B is a new 
// vector C such that m−1 ∑︂ C[k] = j=0 A[j]B[k − j] Assuming the lengths of A and B are of length
//  m and n, respectively, and the indexing of the vectors starts from 0, find an O(nlogn) divide
// and conquer algorithm for this operation. Consider, n ≥ m for your implementation and analysis. 
// By choosing the proper input representation, write a program in C to validate your algorithm.


// CODE---
#include<stdio.h>
#include<math.h>
#include<complex.h>
#define PI 3.14159265358979323846
//Recursive FFT function
void fft(double complex a[],int n,int invert)
{
    if(n==1)
        return;
    int i;
    double complex even[n/2],odd[n/2];
    for(i=0;i<n/2;i++)
    {
        even[i]=a[2*i];
        odd[i]=a[2*i+1];
    }
    fft(even,n/2,invert);
    fft(odd,n/2,invert);
    double angle=2*PI/n*(invert?-1:1);
    double complex w=1;
    double complex wn=cos(angle)+I*sin(angle);
    for(i=0;i<n/2;i++)
    {
        double complex u=even[i];
        double complex v=w*odd[i];
        a[i]=u+v;
        a[i+n/2]=u-v;
        w*=wn;
    }
    if(invert)
    {
        for(i=0;i<n;i++)
            a[i]/=2;
    }
}
//Find next power of 2
int nextPowerOfTwo(int x)
{
    int p=1;
    while(p<x)
        p*=2;
    return p;
}
int main()
{
    int m,n,i,size;
    double complex a[1024],b[1024];
    printf("Enter size of first vector: ");
    scanf("%d",&m);
    printf("Enter size of second vector: ");
    scanf("%d",&n);
    size=nextPowerOfTwo(m+n-1);
    for(i=0;i<size;i++)
    {
        a[i]=0;
        b[i]=0;
    }
    printf("Enter first vector:\n");
    for(i=0;i<m;i++)
    {
        double x;
        scanf("%lf",&x);
        a[i]=x;
    }
    printf("Enter second vector:\n");
    for(i=0;i<n;i++)
    {
        double x;
        scanf("%lf",&x);
        b[i]=x;
    }
    //Apply FFT
    fft(a,size,0);
    fft(b,size,0);
    //Multiply corresponding values
    for(i=0;i<size;i++)
        a[i]*=b[i];
    //Apply inverse FFT
    fft(a,size,1);
    printf("Convolution Result:\n");
    for(i=0;i<m+n-1;i++)
        printf("%.0f ",creal(a[i]));
    printf("\n");
    return 0;
}