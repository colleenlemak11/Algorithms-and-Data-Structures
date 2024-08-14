//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// FILE: hw1_test.cpp
// DATE: Fall 2021
// DESC: HW 1 unit tests
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "simple_sorts.h"


//---------------------------------------------------------------------------
// Bubble Sort Tests
//---------------------------------------------------------------------------

// Test 1
TEST(BasicBubbleSortTest, EmptyArray)
{
  int array[] {};
  bubble_sort(array, 0);
}


// Test 2
TEST(BasicBubbleSortTest, ReverseOrder)
{
  int array[] {4, 3, 2, 1};
  bubble_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


// Test 3
TEST(BasicBubbleSortTest, InOrder)
{
  int array[] {1, 2, 3, 4};
  bubble_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


// Test 4
TEST(BasicBubbleSortTest, PartiallyUnorderedList)
{
  int array[] {2, 3, 1, 4};
  bubble_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


// Test 5
TEST(BasicBubbleSortTest, CompletelyUnorderedList)
{
  int array[] {3, 1, 4, 2};
  bubble_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


//---------------------------------------------------------------------------
// Insertion Sort Tests
//---------------------------------------------------------------------------

// Test 6
TEST(BasicInsertionSortTest, EmptyArray)
{
  int array[] {};
  insertion_sort(array, 0);
}


// Test 7
TEST(BasicInsertionSortTest, ReverseOrder)
{
  int array[] {4, 3, 2, 1};
  insertion_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


// Test 8
TEST(BasicInsertionSortTest, InOrder)
{
  int array[] {1, 2, 3, 4};
  insertion_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


// Test 9
TEST(BasicInsertionSortTest, PartiallyUnorderedList)
{
  int array[] {2, 3, 1, 4};
  insertion_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


// Test 10
TEST(BasicInsertionSortTest, CompletelyUnorderedList)
{
  int array[] {3, 1, 4, 2};
  insertion_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


//---------------------------------------------------------------------------
// Selection Sort Tests
//---------------------------------------------------------------------------

// Test 11
TEST(BasicSelectionSortTest, EmptyArray)
{
  int array[] {};
  selection_sort(array, 0);
}


// Test 12
TEST(BasicSelectionSortTest, ReverseOrder)
{
  int array[] {4, 3, 2, 1};
  selection_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


// Test 13
TEST(BasicSelectionSortTest, InOrder)
{
  int array[] {1, 2, 3, 4};
  selection_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


// Test 14
TEST(BasicSelectionSortTest, PartiallyUnorderedList)
{
  int array[] {2, 3, 1, 4};
  selection_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


// Test 15
TEST(BasicSelectionSortTest, CompletelyUnorderedList)
{
  int array[] {3, 1, 4, 2};
  selection_sort(array, 4);
  for (int i = 0; i < 3; ++i)
    ASSERT_LE(array[i], array[i+1]);
}


//---------------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
