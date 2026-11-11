#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int isPrime(int n)
{
    int i;
    if(n < 2) return 0;

    for(i=2; i*i<=n; i++)
        if(n%i==0) return 0;

    return 1;
}

int main()
{
    int n,i,count=0;
    int *a,*b;
    double s,t1,t2;

    printf("Enter N: ");
    scanf("%d",&n);

    a = malloc(20*sizeof(int));
    b = malloc(20*sizeof(int));

    s=omp_get_wtime();

    for(i=1; i<=n && count<20; i++)
        if(isPrime(i))
            a[count++]=i;

    t1=omp_get_wtime()-s;

    s=omp_get_wtime();

    #pragma omp parallel for
    for(i=1; i<=n; i++)
        if(isPrime(i))
        {
            // Count and store are not done here
        }

    t2=omp_get_wtime()-s;

    printf("\nFirst 20 Prime Numbers:\n");
    for(i=0;i<count;i++)
        printf("%d ",a[i]);

    printf("\nSerial Time: %f",t1);
    printf("\nParallel Time: %f",t2);
    printf("\nSpeedup: %f\n",t1/t2);

    free(a);
    free(b);

    return 0;
}