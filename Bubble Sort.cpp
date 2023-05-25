#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void bubble_sort_sequential(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void bubble_sort_parallel(vector<int>& arr) {
    int n = arr.size();
    int phase, start;

    #pragma omp parallel shared(arr, n) private(phase, start)
    {
        for (phase = 0; phase < n; phase++) {
            if (phase % 2 == 0) {  // Even phase
                #pragma omp for schedule(static)
                for (start = 0; start < n; start += 2) {
                    if (arr[start] > arr[start + 1]) {
                        swap(arr[start], arr[start + 1]);
                    }
                }
            } else {  // Odd phase
                #pragma omp for schedule(static)
                for (start = 1; start < n - 1; start += 2) {
                    if (arr[start] > arr[start + 1]) {
                        swap(arr[start], arr[start + 1]);
                    }
                }
            }

            #pragma omp barrier

            #pragma omp master
            {
                cout << "Phase " << phase << ": ";
                for (int num : arr) {
                    cout << num << " ";
                }
                cout << endl;
            }
        }
    }
}

void print_array(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {9, 5, 7, 1, 3, 2, 8, 6, 4};
    int n = arr.size();

    cout << "Original Array: ";
    print_array(arr);

    vector<int> arr_seq = arr;
    double start_time_seq = omp_get_wtime();
    bubble_sort_sequential(arr_seq);
    double end_time_seq = omp_get_wtime();

    cout << "Sorted Array (Sequential): ";
    print_array(arr_seq);
    cout << "Time Taken (Sequential): " << end_time_seq - start_time_seq << " seconds" << endl;

    vector<int> arr_par = arr;
    double start_time_par = omp_get_wtime();
    bubble_sort_parallel(arr_par);
    double end_time_par = omp_get_wtime();

    cout << "Sorted Array (Parallel): ";
    print_array(arr_par);
    cout << "Time Taken (Parallel): " << end_time_par - start_time_par << " seconds" << endl;

    return 0;
}
