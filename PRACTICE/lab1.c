#include <stdio.h>
#include <omp.h>

void merge(int a[], int l, int m, int r)
{
    int i = l, j = m + 1, k = 0, b[100];

    while (i <= m && j <= r)
        b[k++] = (a[i] < a[j]) ? a[i++] : a[j++];

    while (i <= m)
        b[k++] = a[i++];

    while (j <= r)
        b[k++] = a[j++];

    for (i = l, k = 0; i <= r; i++)
        a[i] = b[k++];
}

void sort(int a[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        sort(a, l, m);
        sort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main()
{
    int a[100], b[100], n, i;
    double s, e, t1, t2;

    printf("Enter N: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    // Sequential merge sort
    s = omp_get_wtime();
    sort(a, 0, n - 1);
    e = omp_get_wtime();
    t1 = e - s;

    // Parallel merge sort using sections
    s = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        sort(b, 0, n / 2 - 1);

        #pragma omp section
        sort(b, n / 2, n - 1);
    }

    merge(b, 0, (n - 1) / 2, n - 1);

    e = omp_get_wtime();
    t2 = e - s;

    printf("\nSequential Sorted Array: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\nParallel Sorted Array: ");
    for (i = 0; i < n; i++)
        printf("%d ", b[i]);

    printf("\nSequential Time: %f", t1);
    printf("\nParallel Time: %f", t2);
    printf("\nTime Difference: %f seconds", t1 - t2);

    return 0;
}