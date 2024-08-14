//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: hw6_perf.cpp
// DATE: Fall 2021
// DESC: Simple performance test driver for HW-6. To run from the
//       command line use:
//          ./hw6_perf 
//       which will print out the corresponding HW-6 timing data.To
//       save this data to a file, run the command:
//          ./hw6_perf > output.dat
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


using namespace std;
using namespace std::chrono;

// NOTE: all data is "shuffled"

double timed_insert(Map<int,int>& m, int key);
double timed_erase(Map<int,int>& m, int key);
double timed_contains(const Map<int,int>& m, int key);
double timed_find_range(const Map<int,int>& m, int key1, int key2);
double timed_sorted_keys(const Map<int,int>& m);

// test parameters
const int start = 0;
const int step = 10000;
const int stop = 100000; 
const int runs = 3;


int main(int argc, char* argv[])
{
  // configure output
  cout << fixed << showpoint;
  cout << setprecision(2);

  // output data header
  cout << "# All times in milliseconds (msec)" << endl;
  cout << "# Column 1 = input data size" << endl;

  cout << "# Column 2 = binsearch map insert" << endl;
  cout << "# Column 3 = array map insert" << endl;
  cout << "# Column 4 = hash map insert" << endl;

  cout << "# Column 5 = binsearch map erase" << endl;
  cout << "# Column 6 = array map erase" << endl;
  cout << "# Column 7 = hash map erase" << endl;

  cout << "# Column 8 = binsearch contains" << endl;
  cout << "# Column 9 = array map contains" << endl;
  cout << "# Column 10 = hash map contains" << endl;

  cout << "# Column 11 = binsearch find range" << endl;
  cout << "# Column 12 = array map find range" << endl;
  cout << "# Column 13 = hash map find range" << endl;

  cout << "# Column 14 = binsearch sorted keys" << endl;
  cout << "# Column 15 = array map sorted keys" << endl;
  cout << "# Column 16 = hash map sorted keys" << endl;

  cout << "# Column 17 = min chain length" << endl;
  cout << "# Column 18 = max chain length" << endl;  
  cout << "# Column 19 = avg chain length" << endl;  

  // generate shuffled data
  ArraySeq<int> keys, vals;
  for (int i = 2; i <= stop*2; i += 2) {
    keys.insert(i, keys.size());
    vals.insert(i, vals.size());
  }
  faro_shuffle(keys, 5);
  faro_shuffle(vals, 4);

  // generate the timing data
  for (int n = start; n <= stop; n += step) {
    // load shuffled data
    BinSearchMap<int,int> m1;
    ArrayMap<int,int> m2;
    HashMap<int,int> m3;
    for (int i = 0; i < n; ++i) {
      m1.insert(keys[i], vals[i]);
      m2.insert(keys[i], vals[i]);
      m3.insert(keys[i], vals[i]);
    }

    int c17 = m3.min_chain_length();
    int c18 = m3.max_chain_length();
    double c19 = m3.avg_chain_length();
    
    int min = 2;
    int med = n;
    int max = n * 2;

    // insert and erase
    double c2_1 = timed_insert(m1, min - 1);
    double c5_1 = timed_erase(m1, min - 1);    
    double c2_2 = timed_insert(m1, med + 1);    
    double c5_2 = timed_erase(m1, med + 1);
    double c2_3 = timed_insert(m1, max + 1);
    double c5_3 = timed_erase(m1, max + 1);    
    double c2 = (c2_1 + c2_2 + c2_3) / 3;
    double c5 = (c5_1 + c5_2 + c5_3) / 3;
    double c3 = timed_insert(m2, med + 1);
    double c6 = timed_erase(m2, med + 1);
    double c4 = timed_insert(m3, med + 1);
    double c7 = timed_erase(m3, med + 1);

    assert(m1.size() == n);
    assert(m2.size() == n);
    assert(m3.size() == n);

    // contains end
    double c8 = timed_contains(m1, max + 1);
    double c9 = timed_contains(m2, max + 1);
    double c10 = timed_contains(m3, max + 1);


    // key range (1/20th of values)
    double c11 = timed_find_range(m1, med, med + (n/20));
    double c12 = timed_find_range(m2, med, med + (n/20));
    double c13 = timed_find_range(m3, med, med + (n/20));
    
    // sort
    double c14 = timed_sorted_keys(m1);
    double c15 = timed_sorted_keys(m2);
    double c16 = timed_sorted_keys(m3);
    
    cout << n
         << " " << c2 << " " << c3 << " " << c4
         << " " << c5 << " " << c6 << " " << c7 
         << " " << c8 << " " << c9 << " " << c10 
         << " " << c11 << " " << c12 << " " << c13
         << " " << c14 << " " << c15 << " " << c16
         << " " << c17 << " " << c18 << " " << c19
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



