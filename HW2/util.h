//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: util.h
// DATE: Fall 2021
// DESC: Helper functions for running performance tests.
//---------------------------------------------------------------------------

#ifndef UTIL_H
#define UTIL_H


//----------------------------------------------------------------------
// Performs a given number of "faro" shuffles for the given
// array. Faro shuffles are useful for our performance tests since
// they are deterministic.
//
// Inputs:
//   array    -- the array to shuffle
//   n        -- the number of elements in the array to shuffle
//   shuffles -- the number of times to shuffle the array
//
// Outputs:
//   array    -- the array is shuffled
//----------------------------------------------------------------------
void faro_shuffle(int array[], int n, int shuffles);


// ----------------------------------------------------------------------
// Initialize the array with shuffled data. Assumes the array is
// already created and at least of length n.
//
// Inputs:
//   array    -- the array to add shuffled data to
//   n        -- the number of elements to add to the array
//   shuffles -- the number of shuffles to use
//
// Outputs:
//   array    -- the array is loaded with shuffled datashuffled
//----------------------------------------------------------------------
void load_shuffled(int array[], int n, int shuffles);


// ----------------------------------------------------------------------
// Initialize the array with the values 1 to n. Assumes the array is
// already created and at least of length n.
//
// Inputs:
//   array    -- the array to add data to
//   n        -- the number of elements to add to the array
//
// Outputs:
//   array    -- the array is loaded with data (values from 1 to n)
//----------------------------------------------------------------------
void load_in_order(int array[], int n);


// ----------------------------------------------------------------------
// Initialize the array with the values n to 1. Assumes the array is
// already created and at least of length n.
//
// Inputs:
//   array    -- the array to add data to
//   n        -- the number of elements to add to the array
//
// Outputs:
//   array    -- the array is loaded with data (values from n to 1)
//----------------------------------------------------------------------
void load_reverse_order(int array[], int n);


// ----------------------------------------------------------------------
// Pretty prints the array to standard out. 
//
// Inputs:
//   array    -- the array to print
//   n        -- the number of elements to add to the array
//----------------------------------------------------------------------
void print_array(const int array[], int n);


#endif
