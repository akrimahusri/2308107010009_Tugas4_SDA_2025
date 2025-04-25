#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <string.h>
#include <stdlib.h> // ← Tambahan untuk malloc dan free

void quick_sort_int_wrapper(int *arr, int n);
void merge_sort_int_wrapper(int *arr, int n);
void quick_sort_str_wrapper(char **arr, int n);
void merge_sort_str_wrapper(char **arr, int n);

/* 
 * Bubble Sort: Membandingkan elemen bersebelahan dan menukar jika tidak urut.
 */
void bubble_sort_int(int arr[], int n);
void bubble_sort_str(char *arr[], int n);

/* 
 * Selection Sort: Memilih elemen terkecil dan menempatkannya di posisi awal.
 */
void selection_sort_int(int arr[], int n);
void selection_sort_str(char *arr[], int n);

/* 
 * Insertion Sort: Menyisipkan elemen ke posisi yang tepat di bagian yang sudah terurut.
 */
void insertion_sort_int(int arr[], int n);
void insertion_sort_str(char *arr[], int n);

/*
 * Merge Sort: Membagi array dan menggabungkannya kembali dengan cara terurut.
 */
void merge_sort_int(int arr[], int l, int r);
void merge_sort_str(char *arr[], int l, int r);

/*
 * Quick Sort: Memilih pivot, lalu membagi array menjadi dua bagian dan rekursif.
 */
void quick_sort_int(int arr[], int low, int high);
void quick_sort_str(char *arr[], int low, int high);

/*
 * Shell Sort: Versi Insertion Sort dengan gap yang mengecil.
 */
void shell_sort_int(int arr[], int n);
void shell_sort_str(char *arr[], int n);

// =============================
// WRAPPER UNTUK QUICK & MERGE
// =============================

// Integer
void quick_sort_int_wrapper(int *arr, int n) {
    quick_sort_int(arr, 0, n - 1);
}

void merge_sort_int_wrapper(int *arr, int n) {
    merge_sort_int(arr, 0, n - 1);
}

// String
void quick_sort_str_wrapper(char **arr, int n) {
    quick_sort_str(arr, 0, n - 1);
}

void merge_sort_str_wrapper(char **arr, int n) {
    merge_sort_str(arr, 0, n - 1);
}

// =====================================
// IMPLEMENTASI

void bubble_sort_int(int arr[], int n) {
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int temp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = temp;
            }
}

void bubble_sort_str(char *arr[], int n) {
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(strcmp(arr[j], arr[j+1]) > 0) {
                char* temp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = temp;
            }
}

void selection_sort_int(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        int min = i;
        for(int j = i+1; j < n; j++)
            if(arr[j] < arr[min]) min = j;
        int temp = arr[i]; arr[i] = arr[min]; arr[min] = temp;
    }
}

void selection_sort_str(char *arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        int min = i;
        for(int j = i+1; j < n; j++)
            if(strcmp(arr[j], arr[min]) < 0) min = j;
        char *temp = arr[i]; arr[i] = arr[min]; arr[min] = temp;
    }
}

void insertion_sort_int(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j]; j--;
        }
        arr[j+1] = key;
    }
}

void insertion_sort_str(char *arr[], int n) {
    for(int i = 1; i < n; i++) {
        char* key = arr[i]; int j = i - 1;
        while(j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j+1] = arr[j]; j--;
        }
        arr[j+1] = key;
    }
}

void merge_int(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for(int i = 0; i < n1; i++) L[i] = arr[l+i];
    for(int i = 0; i < n2; i++) R[i] = arr[m+1+i];
    int i=0, j=0, k=l;
    while(i<n1 && j<n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while(i<n1) arr[k++] = L[i++];
    while(j<n2) arr[k++] = R[j++];
    free(L); free(R);
}

void merge_sort_int(int arr[], int l, int r) {
    if(l < r) {
        int m = l+(r-l)/2;
        merge_sort_int(arr, l, m);
        merge_sort_int(arr, m+1, r);
        merge_int(arr, l, m, r);
    }
}

void merge_str(char *arr[], int l, int m, int r) {
    int n1 = m-l+1, n2 = r-m;
    char **L = (char **)malloc(n1 * sizeof(char *));
    char **R = (char **)malloc(n2 * sizeof(char *));
    for(int i=0; i<n1; i++) L[i] = arr[l+i];
    for(int i=0; i<n2; i++) R[i] = arr[m+1+i];
    int i=0, j=0, k=l;
    while(i<n1 && j<n2) arr[k++] = (strcmp(L[i], R[j]) <= 0) ? L[i++] : R[j++];
    while(i<n1) arr[k++] = L[i++];
    while(j<n2) arr[k++] = R[j++];
    free(L); free(R);
}

void merge_sort_str(char *arr[], int l, int r) {
    if(l < r) {
        int m = l+(r-l)/2;
        merge_sort_str(arr, l, m);
        merge_sort_str(arr, m+1, r);
        merge_str(arr, l, m, r);
    }
}

int partition_int(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for(int j = low; j < high; j++)
        if(arr[j] <= pivot) {
            i++; int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    int temp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = temp;
    return i+1;
}

void quick_sort_int(int arr[], int low, int high) {
    if(low < high) {
        int pi = partition_int(arr, low, high);
        quick_sort_int(arr, low, pi-1);
        quick_sort_int(arr, pi+1, high);
    }
}

int partition_str(char *arr[], int low, int high) {
    char *pivot = arr[high]; int i = low - 1;
    for(int j = low; j < high; j++)
        if(strcmp(arr[j], pivot) <= 0) {
            i++; char *temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    char *temp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = temp;
    return i+1;
}

void quick_sort_str(char *arr[], int low, int high) {
    if(low < high) {
        int pi = partition_str(arr, low, high);
        quick_sort_str(arr, low, pi-1);
        quick_sort_str(arr, pi+1, high);
    }
}

void shell_sort_int(int arr[], int n) {
    for(int gap=n/2; gap>0; gap/=2)
        for(int i=gap; i<n; i++) {
            int temp = arr[i], j;
            for(j=i; j>=gap && arr[j-gap] > temp; j-=gap)
                arr[j] = arr[j-gap];
            arr[j] = temp;
        }
}

void shell_sort_str(char *arr[], int n) {
    for(int gap=n/2; gap>0; gap/=2)
        for(int i=gap; i<n; i++) {
            char *temp = arr[i]; int j;
            for(j=i; j>=gap && strcmp(arr[j-gap], temp) > 0; j-=gap)
                arr[j] = arr[j-gap];
            arr[j] = temp;
        }
}

#endif
