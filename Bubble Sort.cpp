#include <iostream>
#include <chrono>
#include <omp.h>

void bubbleSortParallel(int* arr, int size) {
    #pragma omp parallel
    {
        for (int i = 0; i < size - 1; ++i) {
            #pragma omp for
            for (int j = 0; j < size - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

void bubbleSortSequential(int* arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
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

    // Parallel Bubble Sort
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSortParallel(arr, size);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Parallel Bubble Sort Time: " << duration.count() << " seconds" << std::endl;

    // Sequential Bubble Sort
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    start = std::chrono::high_resolution_clock::now();
    bubbleSortSequential(arr, size);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Sequential Bubble Sort Time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
