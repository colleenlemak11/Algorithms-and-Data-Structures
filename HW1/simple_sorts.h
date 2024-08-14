//---------------------------------------------------------------------------
// NAME: S. Bowers
// File: simple_sorts.h
// DATE: Fall 2021
// DESC: Simple header file for HW1. This file defines the signatures
//       for the three sorting functions (bubble, insertion, and
//       selection sort) along with a simple swap helper function.
//---------------------------------------------------------------------------

#ifndef SIMPLE_SORTS_H
#define SIMPLE_SORTS_H


//----------------------------------------------------------------------
// Swap the int values at the two addresses.
//
// Inputs:
//   x & y -- the two int values to swap
//
// Outputs:
//   x & y -- with x's and y's original values swapped
//----------------------------------------------------------------------
void swap(int& x, int& y);


//----------------------------------------------------------------------
// Implementation of the bubble sort algorithm over the given
// array. Assumes the array is at least of length n.
//
// Inputs:
//   array -- the array to sort
//   n     -- the length of the array (elements of array to sort)
//
// Outputs:
//   array -- elements 0 to n-1 are in sorted order
//----------------------------------------------------------------------
void bubble_sort(int array[], int n);


//----------------------------------------------------------------------
// Implementation of the insertion sort algorithm over the given
// array. Assumes the array is at least of length n.
//
// Inputs:
//   array -- the array to sort
//   n     -- the length of the array (elements of array to sort)
//
// Outputs:
//   array -- elements 0 to n-1 are in sorted order
//----------------------------------------------------------------------
void insertion_sort(int array[], int n);


//----------------------------------------------------------------------
// Implementation of the selection sort algorithm over the given
// array. Selects and places smallest remaining item on each
// pass. Assumes the array is at least of length n.
//
// Inputs:
//   array -- the array to sort
//   n     -- the length of the array (elements of array to sort)
//
// Outputs:
//   array -- elements 0 to n-1 are in sorted order
//----------------------------------------------------------------------
void selection_sort(int array[], int n);


#endif
