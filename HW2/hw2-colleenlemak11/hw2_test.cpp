//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// FILE: hw1_test.cpp
// DATE: Fall 2021
// DESC: this file implements a series of tests used on our linked list
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "sequence.h"
#include "linkedseq.h"

using namespace std;


//----------------------------------------------------------------------
// Empty linked list tests
//----------------------------------------------------------------------

TEST(BasicLinkedSeqTests, EmptyListSize)
{
  LinkedSeq<int> list;
  ASSERT_EQ(true, list.empty());
  ASSERT_EQ(0, list.size());
}

TEST(BasicLinkedSeqTests, EmptyListContains)
{
  LinkedSeq<int> list;
  ASSERT_EQ(false, list.contains(10));
}

TEST(BasicLinkedSeqTests, EmptyListMemberAccess)
{
  LinkedSeq<int> list1;
  EXPECT_THROW(list1.erase(0), std::out_of_range);
  EXPECT_THROW(list1[0] = 10, std::out_of_range);
  const LinkedSeq<int> list2;
  EXPECT_THROW(auto x = list2[0], std::out_of_range);
}


//----------------------------------------------------------------------
// Tests for adding elements
//----------------------------------------------------------------------

TEST(BasicLinkedSeqTests, AddAndCheckSize)
{
  LinkedSeq<int> list;
  list.insert(10, 0);
  ASSERT_EQ(1, list.size());
  ASSERT_EQ(false, list.empty());
  list.insert(20, 1);
  ASSERT_EQ(2, list.size());
  ASSERT_EQ(false, list.empty());
  list.insert(30, 2);
  ASSERT_EQ(3, list.size());
  ASSERT_EQ(false, list.empty());
  list.insert(5, 0);
  ASSERT_EQ(4, list.size());
  ASSERT_EQ(false, list.empty());
  list.insert(15, 2);
  ASSERT_EQ(5, list.size());
  ASSERT_EQ(false, list.empty());
}

TEST(BasicLinkedSeqTests, AddAndCheckContains)
{
  LinkedSeq<char> list;
  list.insert('b', 0);
  list.insert('d', 1);
  list.insert('c', 1);
  list.insert('a', 0);
  list.insert('f', 4);
  list.insert('e', 4);
  ASSERT_EQ(true, list.contains('a'));
  ASSERT_EQ(true, list.contains('b'));
  ASSERT_EQ(true, list.contains('c'));
  ASSERT_EQ(true, list.contains('d'));
  ASSERT_EQ(true, list.contains('e'));
  ASSERT_EQ(true, list.contains('f'));
  ASSERT_EQ(false, list.contains('g'));
}

TEST(BasicLinkedSeqTests, OutOfBoundsInsertIndexes)
{
  LinkedSeq<double> list;
  list.insert(4.4, 0);
  list.insert(3.3, 0);
  list.insert(2.2, 0);
  EXPECT_THROW(list.insert(1.1, -1), std::out_of_range);
  EXPECT_THROW(list.insert(6.6, 4), std::out_of_range);  
}

//----------------------------------------------------------------------
// Tests for removing elements
//----------------------------------------------------------------------

TEST(BasicLinkedSeqTests, EraseAndCheckSize)
{
  LinkedSeq<string> list;
  list.insert("A", 0);
  list.insert("B", 1);
  list.insert("C", 2);
  list.insert("D", 3);
  ASSERT_EQ(4, list.size());
  ASSERT_EQ(false, list.empty());
  // remove internal
  list.erase(2);
  ASSERT_EQ(3, list.size());
  ASSERT_EQ(false, list.contains("C"));
  // remove head
  list.erase(0);
  ASSERT_EQ(2, list.size());
  ASSERT_EQ(false, list.contains("A"));
  // remove tail
  list.erase(1);
  ASSERT_EQ(1, list.size());
  ASSERT_EQ(false, list.contains("D"));
  // remove last elem
  list.erase(0);
  ASSERT_EQ(0, list.size());
  ASSERT_EQ(true, list.empty());
  ASSERT_EQ(false, list.contains("B"));
}

TEST(BasicLinkedSeqTests, EraseAndCheckContains)
{
  LinkedSeq<char> list;
  list.insert('b', 0);
  list.insert('d', 1);
  list.insert('c', 1);
  list.insert('a', 0);
  list.insert('f', 4);
  list.insert('e', 4);
  // erase 'c'
  ASSERT_EQ(true, list.contains('c'));  
  list.erase(2);
  ASSERT_EQ(false, list.contains('c'));
  // erase 'f'
  ASSERT_EQ(true, list.contains('f'));
  list.erase(4);
  ASSERT_EQ(false, list.contains('f'));
  // erase 'a'
  ASSERT_EQ(true, list.contains('a'));
  list.erase(0);
  ASSERT_EQ(false, list.contains('a'));
  // erase 'd'
  ASSERT_EQ(true, list.contains('d'));
  list.erase(1);
  ASSERT_EQ(false, list.contains('d'));
  // erase 'b'
  ASSERT_EQ(true, list.contains('b'));
  list.erase(0);
  ASSERT_EQ(false, list.contains('b'));
  // erase 'e'
  ASSERT_EQ(true, list.contains('e'));
  list.erase(0);
  ASSERT_EQ(false, list.contains('e'));
  // ensure empty
  ASSERT_EQ(true, list.empty());
}

TEST(BasicLinkedSeqTests, OutOfBoundsEraseIndexes)
{
  LinkedSeq<double> list;
  list.insert(3.2, 0);
  list.insert(2.4, 0);
  list.insert(1.6, 0);
  EXPECT_THROW(list.erase(-1), std::out_of_range);
  EXPECT_THROW(list.erase(3), std::out_of_range);  
  EXPECT_NO_THROW(list.erase(2));
  EXPECT_NO_THROW(list.erase(1));
  EXPECT_NO_THROW(list.erase(0));  
}


//----------------------------------------------------------------------
// Destructor, constructors, assignment operators
//----------------------------------------------------------------------

TEST(BasicLinkedSeqTests, DestructorNoThrowChecksWithNew)
{
  Sequence<char>* list = new LinkedSeq<char>;
  EXPECT_NO_THROW(delete list);
  list = new LinkedSeq<char>;
  list->insert('a', 0);
  EXPECT_NO_THROW(delete list);
  list = new LinkedSeq<char>;
  list->insert('a', 0);
  list->insert('b', 1);
  EXPECT_NO_THROW(delete list);
}

TEST(BasicLinkedSeqTests, CopyConstructorChecks)
{
  // copy empty list
  LinkedSeq<int> list1;
  LinkedSeq<int> list2(list1);
  ASSERT_EQ(list1.size(), list2.size());
  // copy one-element list
  list1.insert(10, 0);
  ASSERT_NE(list1.size(), list2.size());
  list2.insert(10, 0);
  list2.insert(20, 0);
  list2.insert(30, 0);
  LinkedSeq<int> list3(list2);
  ASSERT_EQ(list2.size(), list3.size());
  // remove item and check two lists are different
  list3.erase(1);
  ASSERT_NE(list2.size(), list3.size());
  ASSERT_EQ(true, list2.contains(20));
  ASSERT_EQ(false, list3.contains(20));
}

TEST(BasicLinkedSeqTests, MoveConstructorChecks)
{
  // move empty list
  LinkedSeq<int> list1;
  LinkedSeq<int> list2(move(list1));
  ASSERT_EQ(0, list1.size());
  ASSERT_EQ(0, list2.size());
  // move one-element list
  LinkedSeq<char> list3;
  list3.insert('a', 0);
  ASSERT_EQ(1, list3.size());
  ASSERT_EQ(true, list3.contains('a'));
  LinkedSeq<char> list4(move(list3));
  ASSERT_EQ(0, list3.size());
  ASSERT_EQ(1, list4.size());
  ASSERT_EQ(true, list4.contains('a'));
  // add item to new list (to ensure correct move)
  list4.insert('b', 1);
  ASSERT_EQ(0, list3.size());
  ASSERT_EQ(2, list4.size());
  ASSERT_EQ(true, list4.contains('a') and list4.contains('b'));
}

TEST(BasicLinkedSeqTests, CopyAssignmentOpChecks)
{
  LinkedSeq<char> list1;
  LinkedSeq<char> list2;
  // both empty
  list2 = list1;                
  ASSERT_EQ(0, list1.size());
  ASSERT_EQ(0, list2.size());
  // add to list1 (shouldn't change list2)
  list1.insert('a', 0);
  list1.insert('b', 1);
  ASSERT_EQ(2, list1.size());
  ASSERT_EQ(0, list2.size());
  ASSERT_EQ(true, list1.contains('a') and list1.contains('b'));
  // assign list 1 to itself (shouldn't change anything)
  list1 = list1;
  ASSERT_EQ(2, list1.size());
  ASSERT_EQ(true, list1.contains('a') and list1.contains('b'));
  // add items to list 2 and assign list2 to list
  list2.insert('c', 0);
  list2.insert('d', 1);
  list2.insert('e', 2);
  list1 = list2;
  ASSERT_EQ(3, list2.size());
  ASSERT_EQ(3, list1.size());
  ASSERT_EQ(true, list1.contains('c') and list2.contains('c'));
  ASSERT_EQ(true, list1.contains('d') and list2.contains('d'));
  ASSERT_EQ(true, list1.contains('e') and list2.contains('e'));
  // add to list1 (shouldn't change list2)
  list1.insert('f', 3);
  ASSERT_EQ(4, list1.size());
  ASSERT_EQ(3, list2.size());
  ASSERT_EQ(true, not list2.contains('f') and list1.contains('f'));
}


//----------------------------------------------------------------------
// Test operator[](int)
//----------------------------------------------------------------------

TEST(BasicLinkedSeqTests, CheckRValueAccess)
{
  LinkedSeq<int> list;
  list.insert(10, 0);
  list.insert(20, 1);
  list.insert(30, 2);
  ASSERT_EQ(10, list[0]);
  ASSERT_EQ(20, list[1]);
  ASSERT_EQ(30, list[2]);
}

TEST(BasicLinkedSeqTests, CheckLValueAccess)
{
  LinkedSeq<int> list;
  list.insert(10, 0);
  list.insert(20, 1);
  list.insert(30, 2);
  list[0] = 15;
  list[1] = 25;
  list[2] = 35;
  ASSERT_EQ(15, list[0]);
  ASSERT_EQ(25, list[1]);
  ASSERT_EQ(35, list[2]);
}

TEST(BasicLinkedSeqTests, CheckConstRValueAccess)
{
  LinkedSeq<int> list1;
  list1.insert(10, 0);
  list1.insert(20, 1);
  list1.insert(30, 2);
  const LinkedSeq<int> list2 = list1;   // calls copy constructor
  ASSERT_EQ(10, list2[0]);
  ASSERT_EQ(20, list2[1]);
  ASSERT_EQ(30, list2[2]);
}

TEST(BasicLinkedSeqTests, OutOfBoundsLValueAccess)
{
  LinkedSeq<char> list;
  list.insert('b', 0);
  list.insert('c', 1);
  list.insert('d', 2);
  EXPECT_THROW(list[-1] = 'a', std::out_of_range);
  EXPECT_THROW(list[3] = 'e', std::out_of_range);
}

TEST(BasicLinkedSeqTests, OutOfBoundsRValueAccess)
{
  LinkedSeq<char> list;
  list.insert('b', 0);
  list.insert('c', 1);
  list.insert('d', 2);
  char tmp = ' ';
  EXPECT_THROW(tmp = list[-1], std::out_of_range);
  EXPECT_THROW(tmp = list[3], std::out_of_range);
}


//----------------------------------------------------------------------
// Test operator<<
//----------------------------------------------------------------------

TEST(BasicLinkedSeqTests, StringInsertionChecks)
{
  LinkedSeq<int> list;
  stringstream strstrm1;
  // check empty list
  strstrm1 << list;
  ASSERT_EQ("", strstrm1.str());
  // check one-item list
  list.insert(10, 0);
  stringstream strstrm2;
  strstrm2 << list;
  ASSERT_EQ("10", strstrm2.str());
  // check two-item list
  list.insert(20, 1);
  stringstream strstrm3;
  strstrm3 << list;
  ASSERT_EQ("10, 20", strstrm3.str());
  // check three-item list
  list.insert(30, 2);
  stringstream strstrm4;
  strstrm4 << list;
  ASSERT_EQ("10, 20, 30", strstrm4.str());
  stringstream strstrm5;
  strstrm5 << list << endl;
  ASSERT_EQ("10, 20, 30\n", strstrm5.str());
  stringstream strstrm6;
  strstrm6 << list << "; " << list;
  ASSERT_EQ("10, 20, 30; 10, 20, 30", strstrm6.str());
}


//----------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
