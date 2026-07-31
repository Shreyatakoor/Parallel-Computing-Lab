#include <stdio.h>
#include <omp.h>

int main(){
    int n = 2;
    int data[8] = {10, 20, 30, 40, 50, 60, 70, 80};

    #pragma omp parallel for
    for(int i = 0; i < n; i++){
        int id = omp_get_thread_num();
        printf("Thread %d processed index %d: value=%d\n", id, i, data[i]);
    }

    return 0;
}