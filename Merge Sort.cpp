#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void merge_sort_parallel(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                merge_sort_parallel(arr, left, mid);
            }

            #pragma omp section
            {
                merge_sort_parallel(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);

        #pragma omp master
        {
            cout << "Phase: ";
            for (int i = left; i <= right; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
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
    merge_sort_parallel(arr_seq, 0, n - 1);
    double end_time_seq = omp_get_wtime();

    cout << "Sorted Array (Sequential): ";
    print_array(arr_seq);
    cout << "Time Taken (Sequential): " << end_time_seq - start_time_seq << " seconds" << endl;

    vector<int> arr_par = arr;
    double start_time_par = omp_get_wtime();
    merge_sort_parallel(arr_par, 0, n - 1);
    double end_time_par = omp_get_wtime();

    cout << "Sorted Array (Parallel): ";
    print_array(arr_par);
    cout << "Time Taken (Parallel): " << end_time_par - start_time_par << " seconds" << endl;

    return 0;
}
