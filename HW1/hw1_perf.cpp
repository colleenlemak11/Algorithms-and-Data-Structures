//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: hw1_perf.cpp
// DATE: Fall 2021
// DESC: Simple performance test driver for HW-1. To run from the
//       command line use:
//          ./hw1_perf
//       which will print out timing data resulting from the
//       comparison of running bubble sort, insertion sort, and
//       selection sort over different sized sorted, reverse sorted,
//       and shuffled arrays. To save this data to a file, run the
//       command:
//          ./hw1_perf > output.dat
//       This file can then be used by the plotting script to generate
//       the corresponding performance graph.
//---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include "util.h"
#include "simple_sorts.h"

using namespace std;
using namespace std::chrono;

typedef function<void(int[],int)> sort_fn;

// helper functions
double timed_sort_sorted(int array[], int size, sort_fn f);
double timed_sort_reversed(int array[], int size, sort_fn f);
double timed_sort_shuffled(int array[], int size, sort_fn f);
void check_sorted(int array[], int size);

// test parameters
const int start = 0;
const int step = 1000; // 1,000
const int stop = 10000; // 10,000
const int runs = 5;
const int shuffles = 5;


int main(int argc, char* argv[])
{
  // configure output
  cout << fixed << showpoint;
  cout << setprecision(2);

  // output data header
  cout << "# All times in milliseconds (msec)" << endl;
  cout << "# Column 1 = input data size" << endl;
  cout << "# Column 2 = avg time bubble sort, sorted" << endl;
  cout << "# Column 3 = avg time bubble sort, reversed" << endl;
  cout << "# Column 4 = avg time bubble sort, shuffled" << endl;
  cout << "# Column 5 = avg time insertion sort, sorted" << endl;
  cout << "# Column 6 = avg time insertion sort, reversed" << endl;
  cout << "# Column 7 = avg time insertion sort, shuffled" << endl;
  cout << "# Column 8 = avg time selection sort, sorted" << endl;
  cout << "# Column 9 = avg time selection sort, reversed" << endl;
  cout << "# Column 10 = avg time selection sort, shuffled" << endl;
  
  // run tests and print test results
  for (int size = start; size <= stop; size += step) {
    int* array = new int[size];
    double c2 = timed_sort_sorted(array, size, bubble_sort);
    double c3 = timed_sort_reversed(array, size, bubble_sort);
    double c4 = timed_sort_shuffled(array, size, bubble_sort);
    double c5 = timed_sort_sorted(array, size, insertion_sort);
    double c6 = timed_sort_reversed(array, size, insertion_sort);
    double c7 = timed_sort_shuffled(array, size, insertion_sort);    
    double c8 = timed_sort_sorted(array, size, selection_sort);
    double c9 = timed_sort_reversed(array, size, selection_sort);
    double c10 = timed_sort_shuffled(array, size, selection_sort);    

    cout << size << " " << c2 << " " << c3 << " " << c4 << " "
         << c5 << " " << c6 << " " << c7 << " " << c8 << " "
         << c9 << " " << c10 << endl;
    delete [] array;
  }
  
}


double timed_sort_sorted(int array[], int size, sort_fn f)
{
  int total = 0;
  for (int r = 0; r < runs; ++r) {
    load_in_order(array, size);
    auto t0 = high_resolution_clock::now();
    f(array, size);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return (total * 1.0) / runs;
}


double timed_sort_reversed(int array[], int size, sort_fn f)
{
  int total = 0;
  for (int r = 0; r < runs; ++r) {
    load_reverse_order(array, size);
    auto t0 = high_resolution_clock::now();
    f(array, size);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return (total * 1.0) / runs;
}


double timed_sort_shuffled(int array[], int size, sort_fn f)
{
  int total = 0;
  for (int r = 0; r < runs; ++r) {
    load_shuffled(array, size, shuffles);
    auto t0 = high_resolution_clock::now();
    f(array, size);
    auto t1 = high_resolution_clock::now();    
    total += duration_cast<milliseconds>(t1 - t0).count();
    check_sorted(array, size);
  }
  return (total * 1.0) / runs;
}


void check_sorted(int array[], int size)
{
  for (int i = 0; i < size - 1; ++i) {
    if (array[i] > array[i+1]) {
      std::cerr << "Error: Array not sorted: array[" << i << "] = "
                << array[i] << " > " << "array[" << (i + 1) << "] = "
                << array[i+1] << endl;
      std::terminate();
    }
  }
}
