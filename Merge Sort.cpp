#include <iostream>
#include <chrono>
#include <omp.h>

void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSortSequential(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortSequential(arr, left, mid);
        mergeSortSequential(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSortParallel(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSortParallel(arr, left, mid);
            }
            #pragma omp section
            {
                mergeSortParallel(arr, mid + 1, right);
            }
        }
        merge(arr, left, mid, right);
    }
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    const int size = 10000;
    int arr[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }

    // Parallel Merge Sort
    auto start = std::chrono::high_resolution_clock::now();
    mergeSortParallel(arr, 0, size - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Parallel Merge Sort Time: " << duration.count() << " seconds" << std::endl;

    // Sequential Merge Sort
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    start = std::chrono::high_resolution_clock::now();
    mergeSortSequential(arr, 0, size - 1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Sequential Merge Sort Time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
