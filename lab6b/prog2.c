// Question 2:
// 2D square matrix operations and their complexities: Given square matrices with n rows and n columns, what is the worst-case computational complexity of the following matrix algorithms in terms of n: (i) Matrix Addition. (ii) Matrix Multiplication. (iii) Finding if the given matrix is a zero matrix. (iv) Finding if the given matrix is a symmetric matrix. (v) Computing the determinant of the given matrix. (vi) Transposing the matrix in situ (in place). (vii) Finding the eigenvalue and eigenvector of the matrix. By choosing the proper input representation, write a program in C to validate your procedures and derive the corresponding complexity analysis.



// CODE---
#include<stdio.h>
#include<math.h>
#define MAX 20
void printMatrix(float a[MAX][MAX],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%.2f ",a[i][j]);
        printf("\n");
    }
}
//Finding determinant using Gaussian elimination
float determinant(float a[MAX][MAX],int n)
{
    float temp[MAX][MAX],det=1,ratio;
    int i,j,k;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            temp[i][j]=a[i][j];

    for(i=0;i<n;i++)
    {
        if(temp[i][i]==0)
        {
            for(k=i+1;k<n;k++)
            {
                if(temp[k][i]!=0)
                {
                    for(j=0;j<n;j++)
                    {
                        float t=temp[i][j];
                        temp[i][j]=temp[k][j];
                        temp[k][j]=t;
                    }
                    det=-det;
                    break;
                }
            }
        }

        if(temp[i][i]==0)
            return 0;

        for(k=i+1;k<n;k++)
        {
            ratio=temp[k][i]/temp[i][i];
            for(j=i;j<n;j++)
                temp[k][j]-=ratio*temp[i][j];
        }
    }

    for(i=0;i<n;i++)
        det*=temp[i][i];

    return det;
}
//Finding dominant eigenvalue and eigenvector
void eigen(float a[MAX][MAX],int n)
{
    float x[MAX],y[MAX],eigenvalue=0,newEigenvalue;
    int i,j,iteration;

    for(i=0;i<n;i++)
        x[i]=1;

    for(iteration=0;iteration<20;iteration++)
    {
        for(i=0;i<n;i++)
        {
            y[i]=0;
            for(j=0;j<n;j++)
                y[i]+=a[i][j]*x[j];
        }

        newEigenvalue=fabs(y[0]);

        for(i=1;i<n;i++)
        {
            if(fabs(y[i])>newEigenvalue)
                newEigenvalue=fabs(y[i]);
        }

        for(i=0;i<n;i++)
            x[i]=y[i]/newEigenvalue;

        eigenvalue=newEigenvalue;
    }

    printf("Dominant Eigenvalue = %.4f\n",eigenvalue);
    printf("Corresponding Eigenvector:\n");

    for(i=0;i<n;i++)
        printf("%.4f ",x[i]);

    printf("\n");
}
int main()
{
    float a[MAX][MAX],b[MAX][MAX],result[MAX][MAX];
    int n,i,j,k;

    printf("Enter size of square matrix: ");
    scanf("%d",&n);

    printf("Enter first matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%f",&a[i][j]);

    printf("Enter second matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%f",&b[i][j]);

    //1.Matrix Addition
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            result[i][j]=a[i][j]+b[i][j];

    printf("\nMatrix Addition:\n");
    printMatrix(result,n);

    //2.Matrix Multiplication
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            result[i][j]=0;
            for(k=0;k<n;k++)
                result[i][j]+=a[i][k]*b[k][j];
        }
    }
    printf("\nMatrix Multiplication:\n");
    printMatrix(result,n);
    //3.Checking zero matrix
    int isZero=1;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(a[i][j]!=0)
                isZero=0;
        }
    }

    if(isZero)
        printf("\nMatrix is a Zero Matrix\n");
    else
        printf("\nMatrix is not a Zero Matrix\n");
    //4.Checking symmetric matrix
    int symmetric=1;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(a[i][j]!=a[j][i])
                symmetric=0;
        }
    }
    if(symmetric)
        printf("Matrix is Symmetric\n");
    else
        printf("Matrix is not Symmetric\n");
    //5.Finding determinant
    printf("Determinant = %.2f\n",determinant(a,n));
    //6.Transpose matrix in place
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            float temp=a[i][j];
            a[i][j]=a[j][i];
            a[j][i]=temp;
        }
    }
    printf("\nTranspose of Matrix:\n");
    printMatrix(a,n);
    //7.Finding eigenvalue and eigenvector
    eigen(a,n);
    return 0;
}