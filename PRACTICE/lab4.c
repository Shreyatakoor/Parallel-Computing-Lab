#include <stdio.h>
#include <omp.h>

int isPrime(int n)
{
    int i;
    if (n < 2)
        return 0;

    for (i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int n, i;
    double start, end;

    printf("Enter N: ");
    scanf("%d", &n);

    // Serial execution
    start = omp_get_wtime();

    for (i = 1; i <= n; i++)
    {
        if (isPrime(i))
            printf("%d ", i);
    }

    end = omp_get_wtime();
    printf("\nSerial Time: %f seconds\n", end - start);

    // Parallel execution
    start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 1; i <= n; i++)
    {
        if (isPrime(i))
            printf("%d ", i);
    }

    end = omp_get_wtime();
    printf("\nParallel Time: %f seconds\n", end - start);

    return 0;
}