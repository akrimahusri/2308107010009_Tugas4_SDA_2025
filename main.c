#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorting_algorithms.h"

#define MAX_LINE 100
#define MAX_KATA 100
#define MAX_DATA 2000000

// Fungsi untuk membaca angka dari file
int read_integers(const char *filename, int *data, int jumlah) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Gagal membuka file");
        return -1;
    }

    int i = 0;
    while (i < jumlah && fscanf(file, "%d", &data[i]) == 1) {
        i++;
    }

    fclose(file);
    return i;
}

// Fungsi untuk membaca kata dari file
int read_strings(const char *filename, char **data, int jumlah) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Gagal membuka file");
        return -1;
    }

    int i = 0;
    char buffer[MAX_LINE];
    while (i < jumlah && fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Hilangkan newline
        data[i] = malloc(strlen(buffer) + 1);
        strcpy(data[i], buffer);
        i++;
    }

    fclose(file);
    return i;
}

// Fungsi untuk mengkloning array integer
void clone_int_array(int *src, int *dest, int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

// Fungsi untuk mengkloning array string
void clone_str_array(char **src, char **dest, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = malloc(strlen(src[i]) + 1);
        strcpy(dest[i], src[i]);
    }
}

// Fungsi untuk membebaskan array string
void free_str_array(char **arr, int n) {
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
}

void test_int_sort(void (*sort_func)(int*, int), const char *sort_name, int *data, int n) {
    int *copy = malloc(sizeof(int) * n);
    clone_int_array(data, copy, n);

    clock_t start = clock();
    sort_func(copy, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    size_t mem_kb = (sizeof(int) * n) / 1024;

    printf("| %-10s | %12d | %13.3f | %11zu |\n", sort_name, n, time_taken, mem_kb);

    free(copy);
}

void test_str_sort(void (*sort_func)(char**, int), const char *sort_name, char **data, int n) {
    char **copy = malloc(sizeof(char*) * n);
    clone_str_array(data, copy, n);

    clock_t start = clock();
    sort_func(copy, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    size_t mem_kb = 0;
    for (int i = 0; i < n; i++) {
        mem_kb += strlen(copy[i]) + 1;
    }
    mem_kb = (mem_kb + sizeof(char*) * n) / 1024;

    printf("| %-10s | %12d | %13.3f | %11zu |\n", sort_name, n, time_taken, mem_kb);

    free_str_array(copy, n);
    free(copy);
}

int main() {
    int ukuran_data[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
    int total = 2000000;

    // --- Data Angka ---
    int *angka_data = malloc(sizeof(int) * total);
    if (read_integers("data_angka.txt", angka_data, total) < 0) return 1;
  
    for (int i = 0; i < sizeof(ukuran_data)/sizeof(ukuran_data[0]); i++) {
        int n = ukuran_data[i];
        printf("=== PENGUJIAN DATA ANGKA ===\n");
        printf("| %-10s | %12s | %13s | %11s |\n", "Algoritma", "Jumlah Data", "Waktu (detik)", "Memori (KB)");
        printf("|------------|--------------|---------------|-------------|\n");  
        test_int_sort(bubble_sort_int,     "Bubble",    angka_data, n);
        test_int_sort(selection_sort_int,  "Selection", angka_data, n);
        test_int_sort(insertion_sort_int,  "Insertion", angka_data, n);
        test_int_sort(merge_sort_int_wrapper, "Merge", angka_data, n);
        test_int_sort(quick_sort_int_wrapper,  "Quick",     angka_data, n);        
        test_int_sort(shell_sort_int,      "Shell",     angka_data, n);
        printf("\n");
    }
    free(angka_data);

    // --- Data Kata ---
    char **kata_data = malloc(sizeof(char*) * total);
    if (read_strings("data_kata.txt", kata_data, total) < 0) return 1;
   
    for (int i = 0; i < sizeof(ukuran_data)/sizeof(ukuran_data[0]); i++) {
        int n = ukuran_data[i];
        printf("=== PENGUJIAN DATA KATA ===\n");
        printf("| %-10s | %12s | %13s | %11s |\n", "Algoritma", "Jumlah Data", "Waktu (detik)", "Memori (KB)");
        printf("|------------|--------------|---------------|-------------|\n"); 
        test_str_sort(bubble_sort_str,     "Bubble",    kata_data, n);
        test_str_sort(selection_sort_str,  "Selection", kata_data, n);
        test_str_sort(insertion_sort_str,  "Insertion", kata_data, n);
        test_str_sort(merge_sort_str_wrapper,  "Merge",     kata_data, n);
        test_str_sort(quick_sort_str_wrapper,  "Quick",     kata_data, n);        
        test_str_sort(shell_sort_str,      "Shell",     kata_data, n);
        printf("\n");
    }

    free_str_array(kata_data, total);
    free(kata_data);

    return 0;
}
