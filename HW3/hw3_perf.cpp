//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// FILE: hw3_perf.cpp
// DATE: Fall 2021
// DESC: Simple performance test driver for HW-3. To run from the
//       command line use:
//          ./hw3_perf 
//       which will print out the corresponding HW-3 timing data.To
//       save this data to a file, run the command:
//          ./hw3_perf > output.dat
//       This file can then be used by the plotting script to generate
//       the corresponding performance graphs.
//---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <functional>
#include <vector>
#include "arrayseq.h"

#include <cassert>

using namespace std;
using namespace std::chrono;

// insert calls
double timed_array_seq_insert_front(ArraySeq<int>& seq);
double timed_vector_insert_front(vector<int>& seq);
double timed_array_seq_insert_middle(ArraySeq<int>& seq);
double timed_vector_insert_middle(vector<int>& seq);
double timed_array_seq_insert_end(ArraySeq<int>& seq);
double timed_vector_insert_end(vector<int>& seq);
// update calls
double timed_array_seq_update_front(ArraySeq<int>& seq);
double timed_vector_update_front(vector<int>& seq);
double timed_array_seq_update_middle(ArraySeq<int>& seq);
double timed_vector_update_middle(vector<int>& seq);
double timed_array_seq_update_end(ArraySeq<int>& seq);
double timed_vector_update_end(vector<int>& seq);
// erase calls
double timed_array_seq_erase_front(ArraySeq<int>& seq);
double timed_vector_erase_front(vector<int>& seq);
double timed_array_seq_erase_middle(ArraySeq<int>& seq);
double timed_vector_erase_middle(vector<int>& seq);
double timed_array_seq_erase_end(ArraySeq<int>& seq);
double timed_vector_erase_end(vector<int>& seq);
// print output
void run_and_output(ArraySeq<int>& seq1, vector<int>& seq2);


// test parameters
const int start = 0;
const int step = 1000000; // 1,000,000
const int stop = 12000000; // 1,200,000
const int runs = 5;


// TODO: fix update axis in plot script


int main(int argc, char* argv[])
{
  // configure output
  cout << fixed << showpoint;
  cout << setprecision(2);

  // output data header
  cout << "# All times in milliseconds (msec)" << endl;
  cout << "# Column 1 = input data size" << endl;
  cout << "# Column 2 = avg time array-seq insert front" << endl;
  cout << "# Column 3 = avg time vector insert front" << endl;
  cout << "# Column 4 = avg time array-seq insert middle" << endl;
  cout << "# Column 5 = avg time vector insert middle" << endl;
  cout << "# Column 6 = avg time array-seq insert end" << endl;
  cout << "# Column 7 = avg time vector insert end" << endl;
  cout << "# Column 8 = avg time array-seq update front" << endl;
  cout << "# Column 9 = avg time vector update front" << endl;
  cout << "# Column 10 = avg time array-seq update middle" << endl;
  cout << "# Column 11 = avg time vector update middle" << endl;
  cout << "# Column 12 = avg time array-seq update end" << endl;
  cout << "# Column 13 = avg time vector update end" << endl;
  cout << "# Column 14 = avg time array-seq erase front" << endl;
  cout << "# Column 15 = avg time vector erase front" << endl;

  // build up the test case sizes including resize events
  vector<int> test_cases;
  int last_seen_p2 = 0;
  for (int n = start; n <= stop; n += step) {
    // get largest power of 2 less than size
    int p2_size = pow(2, (int)floor(log2(n)));
    if (p2_size > last_seen_p2) {
      test_cases.push_back(p2_size);
      last_seen_p2 = p2_size;
    }
    test_cases.push_back(n);
  }
  
  // run tests and print test results
  for (int size : test_cases) {
    ArraySeq<int>* seq = new ArraySeq<int>;
    vector<int>* vec = new vector<int>(0);
    // build up array seq
    for (int i = 0; i < size; ++i) {
      seq->insert(i+1, i);
      vec->push_back(i+1);
    }
    run_and_output(*seq, *vec);
    delete seq;
    delete vec;
  }

}


void run_and_output(ArraySeq<int>& seq, vector<int>& vec)
{
  ArraySeq<int> s1(seq);
  ArraySeq<int> s2(seq);  
  ArraySeq<int> s3(seq);  
  vector<int> v1(vec);
  vector<int> v2(vec);
  vector<int> v3(vec);
  
  double c2 = timed_array_seq_insert_front(s1);
  double c3 = timed_vector_insert_front(v1);

  double c4 = timed_array_seq_insert_middle(s2);
  double c5 = timed_vector_insert_middle(v2);
  
  double c6 = timed_array_seq_insert_end(s3);
  double c7 = timed_vector_insert_end(v3);
  
  double c8 = timed_array_seq_update_front(seq);
  double c9 = timed_vector_update_front(vec);
  
  double c10 = timed_array_seq_update_middle(seq);
  double c11 = timed_vector_update_middle(vec);
  
  double c12 = timed_array_seq_update_end(seq);
  double c13 = timed_vector_update_end(vec);
  
  double c14 = timed_array_seq_erase_front(s1);
  double c15 = timed_vector_erase_front(v1);

  double c16 = timed_array_seq_erase_middle(s2);
  double c17 = timed_vector_erase_middle(v2);

  double c18 = timed_array_seq_erase_end(s3);
  double c19 = timed_vector_erase_end(v3);

  int size = seq.size();
  cout << size << " " << c2 << " " << c3 << " " << c4 << " "
       << c5 << " " << c6 << " " << c7  << " " << c8 << " "
       << c9 << " " << c10 << " " << c11 << " " << c12 << " "
       << c13 << " " << c14 << " " << c15 << " " << c16 << " "
       << c17 << " " << c18 << " " << c19 << endl;
}


// timing functions

double timed_array_seq_insert_front(ArraySeq<int>& seq)
{
  double total = 0;
  int n = seq.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    seq.insert(n+1, 0);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_vector_insert_front(vector<int>& seq)
{
  double total = 0;
  int n = seq.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    seq.insert(seq.begin() + 0, 0);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_array_seq_insert_middle(ArraySeq<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    seq.insert(seq.size()+1, seq.size()/2);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_vector_insert_middle(vector<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    seq.insert(seq.begin() + (seq.size()/2), seq.size()/2);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_array_seq_insert_end(ArraySeq<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    seq.insert(seq.size()+1, seq.size());
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_vector_insert_end(vector<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    seq.push_back(seq.size()+1);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_array_seq_update_front(ArraySeq<int>& seq)
{
  double total = 0;
  int n = seq.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    if (seq.size() > 0)
      seq[0] = seq.size()+1;
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_vector_update_front(vector<int>& seq)
{
  double total = 0;
  int n = seq.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    if (seq.size() > 0)
      seq[0] = seq.size()+1;
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_array_seq_update_middle(ArraySeq<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    if (seq.size() > 0)
      seq[seq.size()/2] = seq.size() + 1;
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_vector_update_middle(vector<int>& seq)
{
  double total = 0;
  int n = seq.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    if (seq.size() > 0)
      seq[seq.size()/2] = seq.size() + 1;
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_array_seq_update_end(ArraySeq<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    if (seq.size() > 0)
      seq[seq.size()-1] = seq.size() + 1;
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_vector_update_end(vector<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    if (seq.size() > 0)
      seq[seq.size()-1] = seq.size() + 1;
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_array_seq_erase_front(ArraySeq<int>& seq)
{
  double total = 0;
  int n = seq.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    if (seq.size() > 0)
      seq.erase(0);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_vector_erase_front(vector<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    seq.erase(seq.begin() + 0);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_array_seq_erase_middle(ArraySeq<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    if (seq.size() > 0)
      seq.erase(seq.size()/2);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_vector_erase_middle(vector<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    if (seq.size() > 0)
      seq.erase(seq.begin() + (seq.size()/2));
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_array_seq_erase_end(ArraySeq<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    if (seq.size() > 0)
      seq.erase(seq.size() - 1);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_vector_erase_end(vector<int>& seq)
{
  double total = 0;
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    seq.pop_back();
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

