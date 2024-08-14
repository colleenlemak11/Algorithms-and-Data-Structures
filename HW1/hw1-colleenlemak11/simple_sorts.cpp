//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// FILE: simple_sorts.cpp
// DATE: Fall 2021
// DESC: HW 1 sorting functions (./hw1_test to execute)
//---------------------------------------------------------------------------

#include <iostream>
#include "simple_sorts.h"


void swap(int& x, int& y)
{
  int tmp = x;
  x = y;
  y = tmp;
}


void bubble_sort(int array[], int n)
{
  int i = 0;
  int j = 0;
  for(i = 0; i < (n - 1); ++i)
  {
    for(j = 0; j < (n - i - 1); ++j)
    {
      if(array[j] > array[j + 1])
        swap(array[j], array[j + 1]);
    }
  }
}


void insertion_sort(int array[], int n)
{
  int i = 0;
  int j = 0;
  int current_num = 0;
  for(i = 1; i < n; ++i)
  {
    current_num = array[i];
    j = i - 1;
    while(j >= 0 && array[j] > current_num)
    {
      array[j + 1] = array[j];
      j -= 1;
    }
    array[j + 1] = current_num;
  }
}


void selection_sort(int array[], int n)
{
  int i = 0;
  int j = 0;
  int min_idx = 0;
  for(i = 0; i < (n - 1); i++)
  {
    min_idx = i;
    for(j = i + 1; j < n; j++)
    {
      if(array[j] < array[min_idx])
        min_idx = j; 
    }
    swap(array[min_idx], array[i]); 
  }
}
