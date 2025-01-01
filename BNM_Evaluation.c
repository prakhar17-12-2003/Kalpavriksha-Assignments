#include <stdio.h>
long computeExpression(long B, long N, long M) 
{
    long result=1;          
    while (N>0) 
    {
        if (N%2==1) 
        {
            result=(result*B)%M;
        }
        N=N/2;
        B=(B*B)%M;
    }
   return result;
}

int main() 
{
    long B,N,M;
    printf("Enter the base B: ");
    scanf("%ld", &B);

    printf("Enter the exponent N: ");
    scanf("%ld", &N);

    printf("Enter the modulus M: ");
    scanf("%ld", &M);

    if (M<=1) 
    {
        printf("Error:M should be greater than 1\n");
        return 1;
    }
    if (N<0) {
        printf("Error:N must be positive integer\n");
        return 1;
    }
    long result = computeExpression(B,N,M);
    printf("Result: %ld\n",result);

    return 0;
}