#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>
#include <random>
#include <chrono>

using namespace std;

void min_reduction(vector<int>& arr) {
  int min_value = INT_MAX;
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] < min_value) {
      min_value = arr[i];
    }
  }
  cout << "Minimum value: " << min_value << endl;
}

void max_reduction(vector<int>& arr) {
  int max_value = INT_MIN;
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];
    }
  }
  cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(vector<int>& arr) {
  int sum = 0;
   #pragma omp parallel for reduction(+: sum)
   for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  cout << "Sum: " << sum << endl;
}

void average_reduction(vector<int>& arr) {
  int sum = 0;
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  cout << "Average: " << (double)sum / arr.size() << endl;
}

int main() {
  const int size = 10000;
  vector<int> arr(size);

  // Generate random input
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dist(1, 100);

  for (int i = 0; i < size; ++i) {
    arr[i] = dist(gen);
  }

  // Perform operations and measure time
  auto start = chrono::high_resolution_clock::now();
  min_reduction(arr);
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> duration = end - start;
  cout << "Minimum reduction took " << duration.count() << " seconds." << endl;

  start = chrono::high_resolution_clock::now();
  max_reduction(arr);
  end = chrono::high_resolution_clock::now();
  duration = end - start;
  cout << "Maximum reduction took " << duration.count() << " seconds." << endl;

  start = chrono::high_resolution_clock::now();
  sum_reduction(arr);
  end = chrono::high_resolution_clock::now();
  duration = end - start;
  cout << "Sum reduction took " << duration.count() << " seconds." << endl;

  start = chrono::high_resolution_clock::now();
  average_reduction(arr);
  end = chrono::high_resolution_clock::now();
  duration = end - start;
  cout << "Average reduction took " << duration.count() << " seconds." << endl;

  return 0;
}
