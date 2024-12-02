#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Function to compute the dot product of two integer arrays
int dot_product(const int* x, const int* y, int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result += x[i] * y[i];
    }
    return result;
}

// Function to compute the sum of absolute differences between two integer arrays
int sum_abs_diff(const int* x, const int* y, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += abs(x[i] - y[i]);
    }
    return sum;
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

    n = i; // Adjust n to the number of elements actually read

    // Find max value in the right array for frequency mapping
    int max_val = 0;
    for (int i = 0; i < n; i++) {
        if (right[i] > max_val) max_val = right[i];
    }

    // Create and populate frequency map
    int* freq_map = (int*)calloc(max_val + 1, sizeof(int));
    if (!freq_map) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        freq_map[right[i]]++;
    }

    // Create frequency-mapped array for left
    int* freqs = (int*)malloc(n * sizeof(int));
    if (!freqs) {
        perror("Memory allocation failed");
        free(freq_map);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++) {
        freqs[i] = freq_map[left[i]];
    }

    // Compute part2: Dot product of left and frequency-mapped array
    int part2 = dot_product(left, freqs, n);

    // Sort both arrays for part1
    qsort(left, n, sizeof(int), cmpfunc);
    qsort(right, n, sizeof(int), cmpfunc);

    // Compute part1: Sum of sorted absolute differences
    int part1 = sum_abs_diff(left, right, n);

    // Output results
    printf("Sum of sorted absolute differences (part1): %d\n", part1);
    printf("Dot product of frequency-mapped left array (part2): %d\n", part2);

    // Free allocated memory
    free(freq_map);
    free(freqs);

    return 0;
}