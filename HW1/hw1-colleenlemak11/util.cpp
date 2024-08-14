//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: util.cpp
// DATE: Fall 2021
// DESC: Implementation of various helper (utility) functions for
//       carrying out performance tests.
//---------------------------------------------------------------------------

#include <iostream>
#include "util.h"


void faro_shuffle(int array[], int n, int shuffles)
{
  int* tmp_array = new int[n];
  bool out_shuffle = true;
  
  for (int s = 0; s < shuffles; ++s) {
    for (int i = 0; i < n/2; ++i) {    
      int j = n/2 + i;
      int index = 2*i;
      tmp_array[index] = out_shuffle ? array[i] : array[j];
      tmp_array[index + 1] = out_shuffle ? array[j] : array[i];
    }
    for (int i = 0; i < n; ++i)
      array[i] = tmp_array[i];
    out_shuffle = !out_shuffle;
  }
  delete [] tmp_array;
}


void load_shuffled(int array[], int n, int shuffles)
{
  load_in_order(array, n);
  faro_shuffle(array, n, shuffles);
}


void load_in_order(int array[], int n)
{
  for (int i = 0; i < n; ++i)
    array[i] = i + 1;
}


void load_reverse_order(int array[], int n)
{
  for (int i = 0; i < n; ++i)
    array[i] = n - i;
}


void print_array(const int array[], int n)
{
  for (int i = 0; i < n - 1; ++i)
    std::cout << array[i] << ", ";
  if (n > 0)
    std::cout << array[n-1] << std::endl;
}
