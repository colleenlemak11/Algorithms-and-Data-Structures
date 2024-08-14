//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: hw7_perf.cpp
// DATE: Fall 2021
// DESC: Simple performance test driver for HW-7. To run from the
//       command line use:
//          ./hw7_perf 
//       which will print out the corresponding HW-7 timing data. To
//       save this data to a file, run the command:
//          ./hw7_perf > output.dat
//       This file can then be used by the plotting script to generate
//       the corresponding performance graphs.
//---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include "util.h"
#include "arrayseq.h"
#include "map.h"
#include "arraymap.h"
#include "binsearchmap.h"
#include "hashmap.h"
#include "bstmap.h"


using namespace std;
using namespace std::chrono;


double timed_insert(Map<int,int>& m, int key);
double timed_erase(Map<int,int>& m, int key);
double timed_contains(const Map<int,int>& m, int key);
double timed_find_range(const Map<int,int>& m, int key1, int key2);
double timed_sorted_keys(const Map<int,int>& m);

// test parameters
const int start = 0;
const int step = 15000;
const int stop = 150000; 
const int runs = 1;


int main(int argc, char* argv[])
{
  // configure output
  cout << fixed << showpoint;
  cout << setprecision(2);

  // output data header
  cout << "# All times in milliseconds (msec)" << endl;
  cout << "# Column 1 = input data size" << endl;

  cout << "# Column 2 = binsearch map insert shuffled" << endl;
  cout << "# Column 3 = array map insert shuffled" << endl;
  cout << "# Column 4 = hash map insert shuffled" << endl;
  cout << "# Column 5 = bst map insert shuffled" << endl;
  
  cout << "# Column 6 = binsearch map erase shuffled" << endl;
  cout << "# Column 7 = array map erase shuffled" << endl;
  cout << "# Column 8 = hash map erase shuffled" << endl;
  cout << "# Column 9 = bst map erase shuffled" << endl;  
  
  cout << "# Column 10 = binsearch contains shuffled" << endl;
  cout << "# Column 11 = array map contains shuffled" << endl;
  cout << "# Column 12 = hash map contains shuffled" << endl;
  cout << "# Column 13 = bst map contains shuffled" << endl;
  
  cout << "# Column 14 = binsearch find range shuffled" << endl;
  cout << "# Column 15 = array map find range shuffled" << endl;
  cout << "# Column 16 = hash map find range shuffled" << endl;
  cout << "# Column 17 = bst map find range shuffled" << endl;
  
  cout << "# Column 18 = binsearch sorted keys shuffled" << endl;
  cout << "# Column 19 = array map sorted keys shuffled" << endl;
  cout << "# Column 20 = hash map sorted keys shuffled" << endl;
  cout << "# Column 21 = bst map sorted keys shuffled" << endl;

  cout << "# Column 22 = bst map height shuffled" << endl;
  cout << "# Column 23 = log base 2 of input size" << endl;  

  // generate shuffled data
  ArraySeq<int> keys, vals;
  for (int i = 2; i <= stop*2; i += 2) {
    keys.insert(i, keys.size());
    vals.insert(i, vals.size());
  }
  faro_shuffle(keys, 7);
  // faro_shuffle(vals, 2);

  // generate the timing data
  for (int n = start; n <= stop; n += step) {
    // load shuffled data
    BinSearchMap<int,int> m1;
    ArrayMap<int,int> m2;
    HashMap<int,int> m3;
    BSTMap<int,int> m4;
    for (int i = 0; i < n; ++i) {
      m1.insert(keys[i], vals[i]);
      m2.insert(keys[i], vals[i]);
      m3.insert(keys[i], vals[i]);
      m4.insert(keys[i], vals[i]);
    }

    int c22 = m4.height();
    int c23 = (n == 0) ? 0 : ceil(log2(n));
    
    int min = 2;
    int med = n;
    int max = n * 2;

    // insert and erase (three cases for binsearch to be fair)
    double c2_1 = timed_insert(m1, min - 1);
    double c6_1 = timed_erase(m1, min - 1);    
    double c2_2 = timed_insert(m1, med + 1);    
    double c6_2 = timed_erase(m1, med + 1);
    double c2_3 = timed_insert(m1, max + 1);
    double c6_3 = timed_erase(m1, max + 1);    
    double c2 = (c2_1 + c2_2 + c2_3) / 3; 
    double c6 = (c6_1 + c6_2 + c6_3) / 3;
    double c3 = timed_insert(m2, med + 1);
    double c7 = timed_erase(m2, med + 1);
    double c4 = timed_insert(m3, med + 1);
    double c8 = timed_erase(m3, med + 1);
    double c5 = timed_insert(m4, med + 1);
    double c9 = timed_erase(m4, med + 1);
    
    assert(m1.size() == n);
    assert(m2.size() == n);
    assert(m3.size() == n);
    assert(m4.size() == n);
    
    // contains end
    double c10 = timed_contains(m1, max + 1);
    double c11 = timed_contains(m2, max + 1);
    double c12 = timed_contains(m3, max + 1);
    double c13 = timed_contains(m4, max + 1);

    // key range (1/20th of values)
    double c14 = timed_find_range(m1, med, med + (n/20));
    double c15 = timed_find_range(m2, med, med + (n/20));
    double c16 = timed_find_range(m3, med, med + (n/20));
    double c17 = timed_find_range(m4, med, med + (n/20));
    
    // sort
    double c18 = timed_sorted_keys(m1);
    double c19 = timed_sorted_keys(m2);
    double c20 = timed_sorted_keys(m3);
    double c21 = timed_sorted_keys(m4);

    cout << n
         << " " << c2 << " " << c3 << " " << c4
         << " " << c5 << " " << c6 << " " << c7 
         << " " << c8 << " " << c9 << " " << c10 
         << " " << c11 << " " << c12 << " " << c13
         << " " << c14 << " " << c15 << " " << c16
         << " " << c17 << " " << c18 << " " << c19
         << " " << c20 << " " << c21 << " " << c22
         << " " << c23 
         << endl;
  }
  
}


// assumes keys are multiples of 2 and key to insert is odd
double timed_insert(Map<int,int>& m, int key)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.insert(key + (r * 2), key + (r * 2));
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

// removes the odd values inserted from timed_insert
double timed_erase(Map<int,int>& m, int key)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.erase(key + (r * 2));
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

double timed_contains(const Map<int,int>& m, int key) 
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.contains(key);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

double timed_find_range(const Map<int,int>& m, int key1, int key2)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.find_keys(key1, key2);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}

double timed_sorted_keys(const Map<int,int>& m)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    m.sorted_keys();
    auto t1 = high_resolution_clock::now();
    total += duration_cast<microseconds>(t1 - t0).count();
  }
  return (total/1000) / runs;
}




