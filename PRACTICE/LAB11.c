#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int a[], int l, int m, int r)
{
    int *b = malloc((r-l+1)*sizeof(int));
    int i=l, j=m+1, k=0;

    while(i<=m && j<=r)
        b[k++] = (a[i]<a[j]) ? a[i++] : a[j++];

    while(i<=m) b[k++]=a[i++];
    while(j<=r) b[k++]=a[j++];

    for(i=l,k=0; i<=r; i++)
        a[i]=b[k++];

    free(b);
}

void sort(int a[], int l, int r)
{
    if(l<r)
    {
        int m=(l+r)/2;
        sort(a,l,m);
        sort(a,m+1,r);
        merge(a,l,m,r);
    }
}

int main()
{
    int n=100000, i;
    int *a=malloc(n*sizeof(int));
    int *b=malloc(n*sizeof(int));
    double s,t1,t2;

    for(i=0;i<n;i++)
        a[i]=b[i]=rand()%100000;

    s=omp_get_wtime();
    sort(a,0,n-1);
    t1=omp_get_wtime()-s;

    s=omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        sort(b,0,n/2-1);

        #pragma omp section
        sort(b,n/2,n-1);
    }

    merge(b,0,n/2-1,n-1);
    t2=omp_get_wtime()-s;

    printf("Sequential Time: %f\n",t1);
    printf("Parallel Time: %f\n",t2);
    printf("Time Difference: %f\n",t1-t2);

    free(a);
    free(b);

    return 0;
}