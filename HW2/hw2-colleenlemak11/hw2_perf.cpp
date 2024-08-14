//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: hw2_perf.cpp
// DATE: Fall 2021
// DESC: Simple performance test driver for HW-2. To run from the
//       command line use:
//          ./hw2_perf 
//       which will print out the corresponding HW-2 timing data.To
//       save this data to a file, run the command:
//          ./hw2_perf > output.dat
//       This file can then be used by the plotting script to generate
//       the corresponding performance graphs.
//---------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <list>
#include "util.h"
#include "linkedseq.h"

using namespace std;
using namespace std::chrono;

// insert calls
double timed_linked_list_insert_front(LinkedSeq<int>& list);
double timed_cpp_list_insert_front(std::list<int>& list);
double timed_linked_list_insert_middle(LinkedSeq<int>& list);
double timed_cpp_list_insert_middle(std::list<int>& list);
double timed_linked_list_insert_end(LinkedSeq<int>& list);
double timed_cpp_list_insert_end(std::list<int>& list);
// update calls
double timed_linked_list_update_front(LinkedSeq<int>& list);
double timed_cpp_list_update_front(std::list<int>& list);
double timed_linked_list_update_middle(LinkedSeq<int>& list);
double timed_cpp_list_update_middle(std::list<int>& list);
double timed_linked_list_update_end(LinkedSeq<int>& list);
double timed_cpp_list_update_end(std::list<int>& list);
// erase calls
double timed_linked_list_erase_front(LinkedSeq<int>& list);
double timed_cpp_list_erase_front(std::list<int>& list);
double timed_linked_list_erase_middle(LinkedSeq<int>& list);
double timed_cpp_list_erase_middle(std::list<int>& list);
double timed_linked_list_erase_end(LinkedSeq<int>& list);
double timed_cpp_list_erase_end(std::list<int>& list);


// test parameters
const int start = 0;
const int step = 10000; // 10,000
const int stop = 200000; // 100,000
const int runs = 9;
//const int shuffles = 5;


int main(int argc, char* argv[])
{
  // configure output
  cout << fixed << showpoint;
  cout << setprecision(2);

  // output data header
  cout << "# All times in milliseconds (msec)" << endl;
  cout << "# Column 1 = input data size" << endl;
  cout << "# Column 2 = avg time linked-list insert front" << endl;
  cout << "# Column 3 = avg time cpp-list insert front" << endl;
  cout << "# Column 4 = avg time linked-list insert middle" << endl;
  cout << "# Column 5 = avg time cpp-list insert middle" << endl;
  cout << "# Column 6 = avg time linked-list insert end" << endl;
  cout << "# Column 7 = avg time cpp-list insert end" << endl;
  cout << "# Column 8 = avg time linked-list update front" << endl;
  cout << "# Column 9 = avg time cpp-list update front" << endl;
  cout << "# Column 10 = avg time linked-list update middle" << endl;
  cout << "# Column 11 = avg time cpp-list update middle" << endl;
  cout << "# Column 12 = avg time linked-list update end" << endl;
  cout << "# Column 13 = avg time cpp-list update end" << endl;
  cout << "# Column 14 = avg time linked-list erase front" << endl;
  cout << "# Column 15 = avg time cpp-list erase front" << endl;
  cout << "# Column 16 = avg time linked-list erase middle" << endl;
  cout << "# Column 17 = avg time cpp-list erase middle" << endl;
  cout << "# Column 18 = avg time linked-list erase end" << endl;
  cout << "# Column 19 = avg time cpp-list erase end" << endl;
  
  // run tests and print test results
  for (int size = start; size <= stop; size += step) {
    LinkedSeq<int>* list1 = new LinkedSeq<int>;
    std::list<int>* list2 = new std::list<int>;
    // build up linked list
    for (int i = 0; i < size; ++i) {
      list1->insert(i+1, i);
      list2->push_back(i+1);
    }
    
    double c2 = timed_linked_list_insert_front(*list1);
    double c3 = timed_cpp_list_insert_front(*list2);
    double c4 = timed_linked_list_insert_middle(*list1);
    double c5 = timed_cpp_list_insert_middle(*list2);
    double c6 = timed_linked_list_insert_end(*list1);
    double c7 = timed_cpp_list_insert_end(*list2);
    double c8 = timed_linked_list_update_front(*list1);
    double c9 = timed_cpp_list_update_front(*list2);
    double c10 = timed_linked_list_update_middle(*list1);
    double c11 = timed_cpp_list_update_middle(*list2);
    double c12 = timed_linked_list_update_end(*list1);
    double c13 = timed_cpp_list_update_end(*list2);
    double c14 = timed_linked_list_erase_front(*list1);
    double c15 = timed_cpp_list_erase_front(*list2);
    double c16 = timed_linked_list_erase_middle(*list1);
    double c17 = timed_cpp_list_erase_middle(*list2);
    double c18 = timed_linked_list_erase_end(*list1);
    double c19 = timed_cpp_list_erase_end(*list2);
    
    cout << size << " " << c2 << " " << c3 << " " << c4 << " "
         << c5 << " " << c6 << " " << c7  << " " << c8 << " "
         << c9 << " " << c10 << " " << c11 << " " << c12 << " "
         << c13 << " " << c14 << " " << c15 << " " << c16 << " "
         << c17 << " " << c18 << " " << c19 << endl;

    delete list1;
    delete list2;
  }
}

// timing functions

double timed_linked_list_insert_front(LinkedSeq<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.insert(n+1, 0);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_cpp_list_insert_front(std::list<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.push_front(n+1);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_linked_list_insert_middle(LinkedSeq<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.insert(n+1, n/2);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_cpp_list_insert_middle(std::list<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    auto it = list.begin();
    std::advance(it, n/2);
    list.insert(it, n+1);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_linked_list_insert_end(LinkedSeq<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.insert(n+1, n+r);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_cpp_list_insert_end(std::list<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.push_back(n+1);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_linked_list_update_front(LinkedSeq<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list[0] = n+1;
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_cpp_list_update_front(std::list<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.front() = n+1;
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_linked_list_update_middle(LinkedSeq<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list[n/2] = n+1;
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_cpp_list_update_middle(std::list<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    // not "normal" for a list ... 
    auto it = list.begin();
    std::advance(it, n/2);
    list.erase(it);
    it = list.begin();
    std::advance(it, n/2);
    list.insert(it, n+1);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_linked_list_update_end(LinkedSeq<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list[n-1] = n+1;
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_cpp_list_update_end(std::list<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.back() = n+1;
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_linked_list_erase_front(LinkedSeq<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.erase(0);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_cpp_list_erase_front(std::list<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.pop_front();
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_linked_list_erase_middle(LinkedSeq<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.erase(n/2);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_cpp_list_erase_middle(std::list<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    auto it = list.begin();
    std::advance(it, n/2);
    list.erase(it);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_linked_list_erase_end(LinkedSeq<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.erase((n-1)-r);
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}

double timed_cpp_list_erase_end(std::list<int>& list)
{
  double total = 0;
  int n = list.size();
  for (int r = 0; r < runs; ++r) {
    auto t0 = high_resolution_clock::now();
    list.pop_back();
    auto t1 = high_resolution_clock::now();
    total += duration_cast<milliseconds>(t1 - t0).count();
  }
  return total / runs;
}
