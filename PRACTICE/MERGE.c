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
    int n,i;
    int *a,*b;
    double s,t1,t2;

    printf("Enter N: ");
    scanf("%d",&n);

    if(n<=0) return 0;

    a=malloc(n*sizeof(int));
    b=malloc(n*sizeof(int));

    if(a==NULL || b==NULL)
    {
        printf("Memory allocation failed");
        free(a);
        free(b);
        return 1;
    }

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

    merge(b,0,(n-1)/2,n-1);
    t2=omp_get_wtime()-s;

    printf("\nFirst 20 Sequential Elements:\n");
    for(i=0;i<n && i<20;i++)
        printf("%d ",a[i]);

    printf("\nFirst 20 Parallel Elements:\n");
    for(i=0;i<n && i<20;i++)
        printf("%d ",b[i]);

    printf("\n\nSequential Time: %f",t1);
    printf("\nParallel Time: %f",t2);
    printf("\nTime Difference: %f seconds\n",t1-t2);

    free(a);
    free(b);

    return 0;
}