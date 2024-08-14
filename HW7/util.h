//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: util.h
// DATE: Fall 2021
// DESC: Helper functions for running performance tests.
//---------------------------------------------------------------------------

#ifndef UTIL_H
#define UTIL_H

#include "sequence.h"

//----------------------------------------------------------------------
// Performs a given number of "faro" shuffles for the given
// sequence. Faro shuffles are useful for our performance tests since
// they are deterministic. Assumes the sequence is loaded with data to
// shuffle.
//
// Inputs:
//   s        -- the sequence to shuffle
//   shuffles -- the number of times to shuffle the array
//
// Outputs:
//   s        -- the sequence is shuffled
//----------------------------------------------------------------------
void faro_shuffle(Sequence<int>& s, int shuffles);


//----------------------------------------------------------------------
// Initialize the sequence with shuffled data. Assumes the sequence is
// empty.
//
// Inputs:
//   s        -- the sequence to add shuffled data to
//   n        -- insert n items into s
//   shuffles -- the number of shuffles to use
//
// Outputs:
//   s        -- the sequence is loaded with shuffled data
//----------------------------------------------------------------------
void load_shuffled(Sequence<int>& s, int n, int shuffles);


//----------------------------------------------------------------------
// Initialize the sequence with the values 1 to n. Assumes the
// sequence is empty.
//
// Inputs:
//   s -- the sequence to add data to
//   n -- the number of elements to add to the sequence
//
// Outputs:
//   s -- the sequence is loaded with data (values from 1 to n)
//----------------------------------------------------------------------
void load_in_order(Sequence<int>& s, int n);


//----------------------------------------------------------------------
// Initialize the sequence with the values n to 1. Assumes the
// sequence is empty.
//
// Inputs:
//   s -- the sequence to add data to
//   n -- the number of elements to add to the sequence
//
// Outputs:
//   s -- the sequence is loaded with data (values from n to 1)
//----------------------------------------------------------------------
void load_reverse_order(Sequence<int>& s, int n);

//----------------------------------------------------------------------
// Reset the sequence with the values 1 to n. Assumes the sequence is
// already loaded (just resetting the values).
//
// Inputs:
//   s -- the sequence to reset values for
//
// Outputs:
//   s -- the sequence values are reset
//----------------------------------------------------------------------
void reset_ordered(Sequence<int>& s);

//----------------------------------------------------------------------
// Reset the sequence with the values n to 1. Assumes the sequence is
// already loaded (just resetting the values).
//
// Inputs:
//   s -- the sequence to reset values for
//
// Outputs:
//   s -- the sequence values are reset
//----------------------------------------------------------------------
void reset_reversed(Sequence<int>& s);


//----------------------------------------------------------------------
// Reset the sequence with the shuffled values.  Assumes the sequence
// is already loaded (just resetting the values).
//
// Inputs:
//   s -- the sequence to reset values for
//
// Outputs:
//   s -- the sequence values are reset
//----------------------------------------------------------------------
void reset_shuffled(Sequence<int>& s, int shuffles);

#endif
