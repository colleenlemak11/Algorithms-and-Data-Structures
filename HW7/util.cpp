//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: util.cpp
// DATE: Fall 2021
// DESC: Implementation of various helper (utility) functions for
//       carrying out performance tests.
//---------------------------------------------------------------------------

#include <iostream>
#include "util.h"


void faro_shuffle(Sequence<int>& seq, int shuffles)
{
  int n = seq.size();
  int* tmp_array = new int[n];
  bool out_shuffle = true;
  
  for (int s = 0; s < shuffles; ++s) {
    for (int i = 0; i < n/2; ++i) {    
      int j = n/2 + i;
      int index = 2*i;
      tmp_array[index] = out_shuffle ? seq[i] : seq[j];
      tmp_array[index + 1] = out_shuffle ? seq[j] : seq[i];
    }
    for (int i = 0; i < n; ++i)
      seq[i] = tmp_array[i];
    out_shuffle = !out_shuffle;
  }
  delete [] tmp_array;
}

void load_shuffled(Sequence<int>& s, int n, int shuffles)
{
  load_in_order(s, n);
  faro_shuffle(s, shuffles);
}

void load_in_order(Sequence<int>& s, int n)
{
  for (int i = 0; i < n; ++i)
    s.insert(i+1, i);
}

void load_reverse_order(Sequence<int>& s, int n)
{
  for (int i = 0; i < n; ++i)
    s.insert(n-i, i);
}

void reset_ordered(Sequence<int>& s)
{
  int n = s.size();
  for (int i = 0; i < n; ++i)
    s[i] = i + 1;
}

void reset_reversed(Sequence<int>& s)
{
  int n = s.size();
  for (int i = 0; i < n; ++i)
    s[i] = n - i;
}

void reset_shuffled(Sequence<int>& s, int shuffles)
{
  faro_shuffle(s, shuffles);
}


