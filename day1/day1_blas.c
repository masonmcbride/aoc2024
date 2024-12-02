// gcc -o day1_blas day1_blas.c -lmkl_rt -lpthread -lm -ldl
#include <stdio.h>
#include <stdlib.h>
#include <mkl_cblas.h>

int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

double sum_abs_diff(const double* x, const double* y, int n) {
    // Allocate memory for the temporary array
    double* temp_diff = (double*)malloc(n * sizeof(double));
    if (!temp_diff) {
        perror("Memory allocation failed for temp_diff");
        exit(EXIT_FAILURE);
    }

    // Step 1: Copy x into temp_diff
    cblas_dcopy(n, x, 1, temp_diff, 1);

    // Step 2: Compute temp_diff = temp_diff - y
    cblas_daxpy(n, -1.0, y, 1, temp_diff, 1);

    // Step 3: Compute the sum of absolute values
    double result = cblas_dasum(n, temp_diff, 1);

    // Free the temporary array
    free(temp_diff);

    return result;
}

int main() {
    int n = 1000;
    int left[n], right[n];

     // Read input file
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }

    int i = 0;
    while (i < n && fscanf(file, "%d %d", &left[i], &right[i]) == 2) {
        i++;
    }
    fclose(file);

    int max_val = 0;
    for (int i = 0; i < n; i++) {
        if (right[i] > max_val) max_val = right[i];
    }

    int* freq_map = (int*)calloc(max_val+1, sizeof(int));
    if (!freq_map) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++) {
        freq_map[right[i]]++;
    }

    int* freqs = (int*)malloc(n * sizeof(int));
    if (!freqs) {
        perror("Memory allocation failed");
        free(freq_map);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++) {
        freqs[i] = freq_map[left[i]];
    }

    // Convert int arrays to double for CBLAS operations
    double* left_d = (double*)malloc(n * sizeof(double));
    double* freqs_d = (double*)malloc(n * sizeof(double));
    if (!left_d || !freqs_d) {
        perror("Memory allocation failed");
        free(freq_map);
        free(freqs);
        free(left_d);
        free(freqs_d);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        left_d[i] = (double)left[i];
        freqs_d[i] = (double)freqs[i];
    }
    // compute dot product for part 2
    double part2 = cblas_ddot(n, left_d, 1, freqs_d, 1);

    // do sum of sorted absoulte differences for part 1
    qsort(left, n, sizeof(int),cmpfunc);
    qsort(right, n, sizeof(int),cmpfunc);

    double* right_d = freqs_d;
    for (int i = 0; i < n; i++) {
        left_d[i] = (double)left[i];
        right_d[i] = (double)right[i];
    }

    double part1 = sum_abs_diff(left_d, right_d, n);
    // Output the result
    printf("part 1: %.2f\n", part1);
    printf("part 2: %.2f\n", part2);

    // Free allocated memory;
    free(freq_map);
    free(freqs);
    free(left_d);
    free(freqs_d);

    return 0;
}
