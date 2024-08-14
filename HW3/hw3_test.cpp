//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// FILE: hw3_test.cpp
// DATE: Fall 2021
// DESC: 
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "sequence.h"
#include "arrayseq.h"

using namespace std;


//----------------------------------------------------------------------
// Empty sequence tests
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, EmptySeqSize)
{
  ArraySeq<int> seq;
  ASSERT_EQ(true, seq.empty());
  ASSERT_EQ(0, seq.size());
}

TEST(BasicArraySeqTests, EmptySeqContains)
{
  ArraySeq<int> seq;
  ASSERT_EQ(false, seq.contains(10));
}

TEST(BasicArraySeqTests, EmptySeqMemberAccess)
{
  ArraySeq<int> seq1;
  EXPECT_THROW(seq1.erase(0), std::out_of_range);
  EXPECT_THROW(seq1[0] = 10, std::out_of_range);
  const ArraySeq<int> seq2;
  EXPECT_THROW(auto x = seq2[0], std::out_of_range);
}

//----------------------------------------------------------------------
// Tests for adding elements
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, AddAndCheckSize)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(false, seq.empty());
  seq.insert(20, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(false, seq.empty());
  seq.insert(30, 2);
  ASSERT_EQ(3, seq.size());
  ASSERT_EQ(false, seq.empty());
  seq.insert(5, 0);
  ASSERT_EQ(4, seq.size());
  ASSERT_EQ(false, seq.empty());
  seq.insert(15, 2);
  ASSERT_EQ(5, seq.size());
  ASSERT_EQ(false, seq.empty());
}

TEST(BasicArraySeqTests, AddAndCheckContains)
{
  ArraySeq<char> seq;
  seq.insert('b', 0);
  seq.insert('d', 1);
  seq.insert('c', 1);
  seq.insert('a', 0);
  seq.insert('f', 4);
  seq.insert('e', 4);
  ASSERT_EQ(true, seq.contains('a'));
  ASSERT_EQ(true, seq.contains('b'));
  ASSERT_EQ(true, seq.contains('c'));
  ASSERT_EQ(true, seq.contains('d'));
  ASSERT_EQ(true, seq.contains('e'));
  ASSERT_EQ(true, seq.contains('f'));
  ASSERT_EQ(false, seq.contains('g'));
}

TEST(BasicArraySeqTests, OutOfBoundsInsertIndexes)
{
  ArraySeq<double> seq;
  seq.insert(4.4, 0);
  seq.insert(3.3, 0);
  seq.insert(2.2, 0);
  EXPECT_THROW(seq.insert(1.1, -1), std::out_of_range);
  EXPECT_THROW(seq.insert(6.6, 4), std::out_of_range);  
}

//----------------------------------------------------------------------
// Tests for removing elements
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, EraseAndCheckSize)
{
  ArraySeq<string> seq;
  seq.insert("A", 0);
  seq.insert("B", 1);
  seq.insert("C", 2);
  seq.insert("D", 3);
  ASSERT_EQ(4, seq.size());
  ASSERT_EQ(false, seq.empty());
  // remove internal
  seq.erase(2);
  ASSERT_EQ(3, seq.size());
  ASSERT_EQ(false, seq.contains("C"));
  // remove head
  seq.erase(0);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(false, seq.contains("A"));
  // remove tail
  seq.erase(1);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(false, seq.contains("D"));
  // remove last elem
  seq.erase(0);
  ASSERT_EQ(0, seq.size());
  ASSERT_EQ(true, seq.empty());
  ASSERT_EQ(false, seq.contains("B"));
}

TEST(BasicArraySeqTests, EraseAndCheckContains)
{
  ArraySeq<char> seq;
  seq.insert('b', 0);
  seq.insert('d', 1);
  seq.insert('c', 1);
  seq.insert('a', 0);
  seq.insert('f', 4);
  seq.insert('e', 4);
  // erase 'c'
  ASSERT_EQ(true, seq.contains('c'));  
  seq.erase(2);
  ASSERT_EQ(false, seq.contains('c'));
  // erase 'f'
  ASSERT_EQ(true, seq.contains('f'));
  seq.erase(4);
  ASSERT_EQ(false, seq.contains('f'));
  // erase 'a'
  ASSERT_EQ(true, seq.contains('a'));
  seq.erase(0);
  ASSERT_EQ(false, seq.contains('a'));
  // erase 'd'
  ASSERT_EQ(true, seq.contains('d'));
  seq.erase(1);
  ASSERT_EQ(false, seq.contains('d'));
  // erase 'b'
  ASSERT_EQ(true, seq.contains('b'));
  seq.erase(0);
  ASSERT_EQ(false, seq.contains('b'));
  // erase 'e'
  ASSERT_EQ(true, seq.contains('e'));
  seq.erase(0);
  ASSERT_EQ(false, seq.contains('e'));
  // ensure empty
  ASSERT_EQ(true, seq.empty());
}

TEST(BasicArraySeqTests, OutOfBoundsEraseIndexes)
{
  ArraySeq<double> seq;
  seq.insert(3.2, 0);
  seq.insert(2.4, 0);
  seq.insert(1.6, 0);
  EXPECT_THROW(seq.erase(-1), std::out_of_range);
  EXPECT_THROW(seq.erase(3), std::out_of_range);  
  EXPECT_NO_THROW(seq.erase(2));
  EXPECT_NO_THROW(seq.erase(1));
  EXPECT_NO_THROW(seq.erase(0));  
}


//----------------------------------------------------------------------
// Destructor, constructors, assignment operators
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, DestructorNoThrowChecksWithNew)
{
  Sequence<char>* seq = new ArraySeq<char>;
  EXPECT_NO_THROW(delete seq);
  seq = new ArraySeq<char>;
  seq->insert('a', 0);
  EXPECT_NO_THROW(delete seq);
  seq = new ArraySeq<char>;
  seq->insert('a', 0);
  seq->insert('b', 1);
  EXPECT_NO_THROW(delete seq);
}

TEST(BasicArraySeqTests, CopyConstructorChecks)
{
  // copy empty seq
  ArraySeq<int> seq1;
  ArraySeq<int> seq2(seq1);
  ASSERT_EQ(seq1.size(), seq2.size());
  // copy one-element seq
  seq1.insert(10, 0);
  ASSERT_NE(seq1.size(), seq2.size());
  seq2.insert(10, 0);
  seq2.insert(20, 0);
  seq2.insert(30, 0);
  ArraySeq<int> seq3(seq2);
  ASSERT_EQ(seq2.size(), seq3.size());
  // remove item and check two seqs are different
  seq3.erase(1);
  ASSERT_NE(seq2.size(), seq3.size());
  ASSERT_EQ(true, seq2.contains(20));
  ASSERT_EQ(false, seq3.contains(20));
}

TEST(BasicArraySeqTests, MoveConstructorChecks)
{
  // move empty seq
  ArraySeq<int> seq1;
  ArraySeq<int> seq2(move(seq1));
  ASSERT_EQ(0, seq1.size());
  ASSERT_EQ(0, seq2.size());
  // move one-element seq
  ArraySeq<char> seq3;
  seq3.insert('a', 0);
  ASSERT_EQ(1, seq3.size());
  ASSERT_EQ(true, seq3.contains('a'));
  ArraySeq<char> seq4(move(seq3));
  ASSERT_EQ(0, seq3.size());
  ASSERT_EQ(1, seq4.size());
  ASSERT_EQ(true, seq4.contains('a'));
  // add item to new seq (to ensure correct move)
  seq4.insert('b', 1);
  ASSERT_EQ(0, seq3.size());
  ASSERT_EQ(2, seq4.size());
  ASSERT_EQ(true, seq4.contains('a') and seq4.contains('b'));
}

TEST(BasicArraySeqTests, CopyAssignmentOpChecks)
{
  ArraySeq<char> seq1;
  ArraySeq<char> seq2;
  // both empty
  seq2 = seq1;                
  ASSERT_EQ(0, seq1.size());
  ASSERT_EQ(0, seq2.size());
  // add to seq1 (shouldn't change seq2)
  seq1.insert('a', 0);
  seq1.insert('b', 1);
  ASSERT_EQ(2, seq1.size());
  ASSERT_EQ(0, seq2.size());
  ASSERT_EQ(true, seq1.contains('a') and seq1.contains('b'));
  // assign seq 1 to itself (shouldn't change anything)
  seq1 = seq1;
  ASSERT_EQ(2, seq1.size());
  ASSERT_EQ(true, seq1.contains('a') and seq1.contains('b'));
  // add items to seq 2 and assign seq2 to seq
  seq2.insert('c', 0);
  seq2.insert('d', 1);
  seq2.insert('e', 2);
  seq1 = seq2;
  ASSERT_EQ(3, seq2.size());
  ASSERT_EQ(3, seq1.size());
  ASSERT_EQ(true, seq1.contains('c') and seq2.contains('c'));
  ASSERT_EQ(true, seq1.contains('d') and seq2.contains('d'));
  ASSERT_EQ(true, seq1.contains('e') and seq2.contains('e'));
  // add to seq1 (shouldn't change seq2)
  seq1.insert('f', 3);
  ASSERT_EQ(4, seq1.size());
  ASSERT_EQ(3, seq2.size());
  ASSERT_EQ(true, not seq2.contains('f') and seq1.contains('f'));
}


//----------------------------------------------------------------------
// Test operator[](int)
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, CheckRValueAccess)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  seq.insert(30, 2);
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
  ASSERT_EQ(30, seq[2]);
}

TEST(BasicArraySeqTests, CheckLValueAccess)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  seq.insert(30, 2);
  seq[0] = 15;
  seq[1] = 25;
  seq[2] = 35;
  ASSERT_EQ(15, seq[0]);
  ASSERT_EQ(25, seq[1]);
  ASSERT_EQ(35, seq[2]);
}

TEST(BasicArraySeqTests, OutOfBoundsLValueAccess)
{
  ArraySeq<char> seq;
  seq.insert('b', 0);
  seq.insert('c', 1);
  seq.insert('d', 2);
  EXPECT_THROW(seq[-1] = 'a', std::out_of_range);
  EXPECT_THROW(seq[3] = 'e', std::out_of_range);
}

TEST(BasicArraySeqTests, OutOfBoundsRValueAccess)
{
  ArraySeq<char> seq;
  seq.insert('b', 0);
  seq.insert('c', 1);
  seq.insert('d', 2);
  char tmp = ' ';
  EXPECT_THROW(tmp = seq[-1], std::out_of_range);
  EXPECT_THROW(tmp = seq[3], std::out_of_range);
}


//----------------------------------------------------------------------
// Test operator<<
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, StringInsertionChecks)
{
  ArraySeq<int> seq;
  stringstream strstrm1;
  // check empty seq
  strstrm1 << seq;
  ASSERT_EQ("", strstrm1.str());
  // check one-item seq
  seq.insert(10, 0);
  stringstream strstrm2;
  strstrm2 << seq;
  ASSERT_EQ("10", strstrm2.str());
  // check two-item seq
  seq.insert(20, 1);
  stringstream strstrm3;
  strstrm3 << seq;
  ASSERT_EQ("10, 20", strstrm3.str());
  // check three-item seq
  seq.insert(30, 2);
  stringstream strstrm4;
  strstrm4 << seq;
  ASSERT_EQ("10, 20, 30", strstrm4.str());
  stringstream strstrm5;
  strstrm5 << seq << endl;
  ASSERT_EQ("10, 20, 30\n", strstrm5.str());
  stringstream strstrm6;
  strstrm6 << seq << "; " << seq;
  ASSERT_EQ("10, 20, 30; 10, 20, 30", strstrm6.str());
}


//----------------------------------------------------------------------
// Test resize()
//----------------------------------------------------------------------
TEST(BasicArraySeqTests, ResizeCheck)
{
  ArraySeq<int> seq;
  int size = 513;
  // force resizes
  for (int i = 0; i < size; ++i)
    seq.insert(i*2, i);
  ASSERT_EQ(size, seq.size());
  // check values
  for (int i = 0; i < size-1; ++i)
    ASSERT_LE(seq[i], seq[i+1]);
}


//----------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
