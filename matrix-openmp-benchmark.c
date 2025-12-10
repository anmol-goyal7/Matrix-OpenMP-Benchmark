#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000  

void fillArray(int **arr, int filler) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            arr[r][c] = filler;
        }
    }
}

void multiplyNormal(int **a, int **b, long long **out) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            long long sum = 0;
            for (int k = 0; k < N; k++) {
                sum += (long long)a[r][k] * b[k][c];
            }
            out[r][c] = sum;
        }
    }
}

void multiplyParallel(int **a, int **b, long long **out) {
    #pragma omp parallel for
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            long long sum = 0;
            for (int k = 0; k < N; k++) {
                sum += (long long)a[r][k] * b[k][c];
            }
            out[r][c] = sum;
        }
    }
}

int main() {
    int val1, val2, option;

    int **A, **B;
    long long **C;

    double t1 = 0, t2 = 0;

    A = malloc(N * sizeof(int *));
    B = malloc(N * sizeof(int *));
    C = malloc(N * sizeof(long long *));

    for (int i = 0; i < N; i++) {
        A[i] = malloc(N * sizeof(int));
        B[i] = malloc(N * sizeof(int));
        C[i] = malloc(N * sizeof(long long));
    }

    printf("=== Matrix Multiplication Benchmark ===\n\n");

    printf("Enter value for Matrix A: \n");
    printf("The number that you'll choose will be there in the entire matrix of 1000 elemets");
    scanf("%d", &val1);

    printf("Enter value for Matrix B: ");    
    printf("The number that you'll choose will be there in the entire matrix of 1000 elemets")
    scanf("%d", &val2);

    printf("\nPreparing matrices...\n");

    fillArray(A, val1);
    fillArray(B, val2);

    printf("\nChoose method:\n");
    printf("1. Normal multiplication\n");
    printf("2. OpenMP parallel multiplication\n");
    printf("3. Run and compare both\n");
    printf("Enter option: ");
    scanf("%d", &option);

    printf("\n");

    if (option == 1 || option == 3) {
        printf("Running WITHOUT OpenMP...\n");
        clock_t s = clock();
        multiplyNormal(A, B, C);
        clock_t e = clock();
        t1 = (double)(e - s) / CLOCKS_PER_SEC;

        printf("Finished (No OpenMP)\n");
        printf("Time: %.6f seconds\n\n", t1);
    }

    if (option == 2 || option == 3) {
        printf("Running WITH OpenMP (%d threads)...\n", omp_get_max_threads());
        double s = omp_get_wtime();
        multiplyParallel(A, B, C);
        double e = omp_get_wtime();
        t2 = e - s;

        printf("Finished (With OpenMP)\n");
        printf("Time: %.6f seconds\n\n", t2);
    }

    if (option == 3) {
        printf("========== Comparison ==========\n");
        printf("Normal:    %.6f sec\n", t1);
        printf("OpenMP:    %.6f sec\n", t2);
        printf("Speedup:   %.2fx faster\n", t1 / t2);
        printf("Saved:     %.6f sec (%.1f%%)\n",
               t1 - t2,
               ((t1 - t2) / t1) * 100);
        printf("================================\n\n");
    }

    printf("Sample elements:\n");
    printf("C[0][0] = %lld\n", C[0][0]);
    printf("C[0][999] = %lld\n", C[0][N-1]);
    printf("C[999][0] = %lld\n", C[N-1][0]);
    printf("C[999][999] = %lld\n", C[N-1][N-1]);

    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}

