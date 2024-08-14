//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// FILE: hw6_test.cpp
// DATE: Fall 2021
// DESC: This is a test file for btsmap.h
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "arrayseq.h"
#include "bstmap.h"

using namespace std;


//----------------------------------------------------------------------
// Basic Tests for the BSTMap implementation of Map
//----------------------------------------------------------------------

TEST(BasicBSTMapTests, EmptyCheck)
{
  BSTMap<char,int> m;
  ASSERT_EQ(true, m.empty());
  ASSERT_EQ(0, m.size());
}

TEST(BasicBSTMapTests, InsertAndContainsCheck)
{
  BSTMap<char,int> m;
  m.insert('d', 40);
  m.insert('b', 20);
  m.insert('c', 30);
  m.insert('a', 10);
  m.insert('f', 60);
  m.insert('e', 50);
  m.insert('h', 80);
  m.insert('g', 70);

  ASSERT_EQ(false, m.empty());
  ASSERT_EQ(8, m.size());
  for (int i = 0; i < 8; ++i)
  {
    ASSERT_EQ(true, m.contains('a' + i));
  }
}

TEST(BasicBSTMapTests, RValueAccessCheck)
{
  BSTMap<char,int> m;
  m.insert('c', 30);
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('d', 40);
  ASSERT_EQ(4, m.size());
  ASSERT_EQ(10, m['a']);
  ASSERT_EQ(20, m['b']);
  ASSERT_EQ(30, m['c']);
  ASSERT_EQ(40, m['d']);
}

TEST(BasicBSTMapTests, LValueAccessCheck)
{
  BSTMap<char,int> m;
  m.insert('c', 30);
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('d', 40);
  m['a'] = 40;
  m['b'] = 30;
  m['c'] = 20;
  m['d'] = 10;
  ASSERT_EQ(40, m['a']);
  ASSERT_EQ(30, m['b']);
  ASSERT_EQ(20, m['c']);
  ASSERT_EQ(10, m['d']);
}

TEST(BasicBSTMapTests, EraseCheck)
{
  BSTMap<char,int> m;
  m.insert('h', 45);
  m.insert('d', 25);
  m.insert('b', 15);  
  m.insert('a', 10);
  m.insert('c', 20);
  m.insert('f', 35);
  m.insert('e', 30);
  m.insert('g', 40);
  m.insert('l', 65);
  m.insert('j', 55);
  m.insert('i', 50);
  m.insert('k', 60);
  m.insert('n', 75);
  m.insert('m', 70);
  m.insert('o', 80);
  ASSERT_EQ(15, m.size());
  m.erase('h');
  ASSERT_EQ(14, m.size());
  ASSERT_EQ(false, m.contains('h'));
  m.erase('i');
  ASSERT_EQ(13, m.size());
  ASSERT_EQ(false, m.contains('i'));
  m.erase('k');
  ASSERT_EQ(12, m.size());
  ASSERT_EQ(false, m.contains('k'));
  m.erase('j');
  ASSERT_EQ(11, m.size());
  ASSERT_EQ(false, m.contains('j'));
  m.erase('c');
  ASSERT_EQ(10, m.size());
  ASSERT_EQ(false, m.contains('c'));
  m.erase('b');
  ASSERT_EQ(9, m.size());
  ASSERT_EQ(false, m.contains('b'));
  m.erase('a');
  ASSERT_EQ(8, m.size());
  ASSERT_EQ(false, m.contains('a'));
  m.erase('d');
  ASSERT_EQ(7, m.size());
  ASSERT_EQ(false, m.contains('d'));
  m.erase('l');
  ASSERT_EQ(6, m.size());
  ASSERT_EQ(false, m.contains('l'));
  m.erase('m');
  ASSERT_EQ(5, m.size());
  ASSERT_EQ(false, m.contains('m'));
  m.erase('f');
  ASSERT_EQ(4, m.size());
  ASSERT_EQ(false, m.contains('f'));
  m.erase('n');
  ASSERT_EQ(3, m.size());
  ASSERT_EQ(false, m.contains('h'));
  m.erase('o');
  ASSERT_EQ(2, m.size());
  ASSERT_EQ(false, m.contains('o'));
  m.erase('e');
  ASSERT_EQ(1, m.size());
  ASSERT_EQ(false, m.contains('e'));
  m.erase('g');
  ASSERT_EQ(0, m.size());
  ASSERT_EQ(false, m.contains('g'));
}

TEST(BasicBSTMapTests, KeyRangeCheck)
{
  BSTMap<char,int> m;
  m.insert('e', 40);
  m.insert('c', 20);
  m.insert('b', 10);
  m.insert('d', 30);
  m.insert('g', 60);
  m.insert('f', 50);
  m.insert('h', 70);
  ASSERT_EQ(7, m.size());  
  ArraySeq<char> k;
  k = m.find_keys('c', 'g');
  ASSERT_EQ(5, k.size());
  for (int i = 0; i < 5; ++i)
    ASSERT_EQ('c' + i, k[i]);
  k = m.find_keys('d', 'f');
  ASSERT_EQ(3, k.size());
  for (int i = 0; i < 3; ++i)
    ASSERT_EQ('d' + i, k[i]);
  k = m.find_keys('a', 'd');
  ASSERT_EQ(3, k.size());
  for (int i = 0; i < 3; ++i)
    ASSERT_EQ('b' + i, k[i]);
  k = m.find_keys('f', 'i');
  ASSERT_EQ(3, k.size());
  for (int i = 0; i < 3; ++i)
    ASSERT_EQ('f' + i, k[i]);
  k = m.find_keys('a', 'i');
  ASSERT_EQ(7, k.size());
  for (int i = 0; i < 7; ++i)
    ASSERT_EQ('b' + i, k[i]);
  
}

TEST(BasicBSTMapTests, SortedKeyCheck)
{
  BSTMap<char,int> m;
  m.insert('e', 40);
  m.insert('c', 20);
  m.insert('b', 10);
  m.insert('d', 30);
  m.insert('g', 60);
  m.insert('f', 50);
  m.insert('h', 70);
  ASSERT_EQ(7, m.size());  
  ArraySeq<char> k;
  k = m.sorted_keys();
  ASSERT_EQ(7, k.size());  
  for (int i = 0; i < 7; ++i)
    ASSERT_EQ('b' + i, k[i]);
}

TEST(BasicBSTMapTests, InvalidKeyCheck)
{
  BSTMap<char,int> m;
  int x = 10;
  EXPECT_THROW(m['a'] = x, std::out_of_range);
  EXPECT_THROW(x = m['a'], std::out_of_range);
  EXPECT_THROW(m.erase('a'), std::out_of_range);
  m.insert('a', 10);
  m.insert('c', 30);
  EXPECT_THROW(m['b'] = x, std::out_of_range);
  EXPECT_THROW(x = m['b'], std::out_of_range);
  EXPECT_THROW(m.erase('b'), std::out_of_range);
}

TEST(BasicBSTMapTests, DestructorCheck)
{
  BSTMap<char,int>* m = new BSTMap<char,int>;
  EXPECT_NO_THROW(delete m);
  m = new BSTMap<char,int>;
  m->insert('a', 1);
  EXPECT_NO_THROW(delete m);
  m = new BSTMap<char,int>;
  for (char c = 'a'; c <= 'z'; ++c)
    m->insert(c, (int)(c - 'a'));
  EXPECT_NO_THROW(delete m);
  m = new BSTMap<char,int>;
  m->insert('e', 40);
  m->insert('c', 20);
  m->insert('b', 10);
  m->insert('d', 30);
  m->insert('g', 60);
  m->insert('f', 50);
  m->insert('h', 70);
  EXPECT_NO_THROW(delete m);  
}

TEST(BasicBSTMapTests, CopyConstructorCheck)
{
  // copy empty seq
  BSTMap<char,int> m1;
  BSTMap<char,int> m2(m1);
  ASSERT_EQ(m1.size(), m2.size());
  // copy one-element seq
  m1.insert('a', 1);
  ASSERT_NE(m1.size(), m2.size());
  m2.insert('c', 3);
  m2.insert('b', 2);
  m2.insert('d', 4);
  BSTMap<char,int> m3(m2);
  ASSERT_EQ(m2.size(), m3.size());
  // remove item and check two seqs are different
  m3.erase('c');
  ASSERT_NE(m2.size(), m3.size());
  ASSERT_EQ(true, m2.contains('c'));
  ASSERT_EQ(false, m3.contains('c'));
}

TEST(BasicBSTMapTests, CopyAssignmentCheck)
{
  BSTMap<char,int> m1;
  BSTMap<char,int> m2;
  // both empty
  m2 = m1;                
  ASSERT_EQ(0, m1.size());
  ASSERT_EQ(0, m2.size());
  // add to m1 (shouldn't change m2)
  m1.insert('a', 0);
  m1.insert('b', 1);
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(0, m2.size());
  ASSERT_EQ(true, m1.contains('a') and m1.contains('b'));
  // assign m 1 to itself (shouldn't change anything)
  m1 = m1;
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(true, m1.contains('a') and m1.contains('b'));
  // add items to m2 and assign m2 to m1
  m2.insert('d', 1);
  m2.insert('c', 0);
  m2.insert('e', 2);
  m1 = m2;
  ASSERT_EQ(3, m2.size());
  ASSERT_EQ(3, m1.size());
  ASSERT_EQ(true, m1.contains('c') and m2.contains('c'));
  ASSERT_EQ(true, m1.contains('d') and m2.contains('d'));
  ASSERT_EQ(true, m1.contains('e') and m2.contains('e'));
  // add to m1 (shouldn't change m2)
  m1.insert('f', 3);
  ASSERT_EQ(4, m1.size());
  ASSERT_EQ(3, m2.size());
  ASSERT_EQ(true, not m2.contains('f') and m1.contains('f'));
}

TEST(BasicBSTMapTests, MoveConstructorCheck)
{
  // move empty map
  BSTMap<char,int> m1;
  BSTMap<char,int> m2(std::move(m1));
  ASSERT_EQ(0, m1.size());
  ASSERT_EQ(0, m2.size());
  // move one-element ma[
  BSTMap<char,int> m3;
  m3.insert('a', 1);
  ASSERT_EQ(1, m3.size());
  ASSERT_EQ(true, m3.contains('a'));
  BSTMap<char,int> m4(std::move(m3));
  ASSERT_EQ(0, m3.size());
  ASSERT_EQ(1, m4.size());
  ASSERT_EQ(true, m4.contains('a'));
  // add item to new m (to ensure correct move)
  m4.insert('b', 2);
  ASSERT_EQ(0, m3.size());
  ASSERT_EQ(2, m4.size());
  ASSERT_EQ(true, m4.contains('a') and m4.contains('b'));
}

TEST(BasicBSTMapTests, MoveAssignmentCheck)
{
  // create a map
  BSTMap<char,int> m1;
  m1.insert('b', 2);
  m1.insert('a', 1);
  m1.insert('c', 3);
  ASSERT_EQ(3, m1.size());
  // and another
  BSTMap<char,int> m2;
  m2.insert('d', 4);
  ASSERT_EQ(1, m2.size());
  // move first to second
  m2 = std::move(m1);
  ASSERT_EQ(0, m1.size());
  ASSERT_EQ(3, m2.size());
  ASSERT_EQ(true, m2.contains('a') && m2.contains('b') && m2.contains('c'));
  m1.insert('f', 6);
  m1.insert('e', 5);
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(true, m1.contains('e') && m1.contains('f'));
  ASSERT_EQ(false, m2.contains('e') || m2.contains('f'));
  // create an empty map
  BSTMap<char,int> m3;
  ASSERT_EQ(0, m3.size());
  // move second to third
  m3 = std::move(m2);
  ASSERT_EQ(3, m3.size());
  ASSERT_EQ(0, m2.size());
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(true, m3.contains('a') && m3.contains('b') && m3.contains('c'));
}


TEST(BasicBSTMapTests, HeightCheck)
{
  // create a map
  BSTMap<char,int> m;
  m.insert('e', 40);
  ASSERT_EQ(1, m.height());
  m.insert('b', 10);
  ASSERT_EQ(2, m.height());            
  m.insert('g', 60);
  ASSERT_EQ(2, m.height());
  m.insert('d', 30);
  ASSERT_EQ(3, m.height());  
  m.insert('h', 70);
  ASSERT_EQ(3, m.height());  
  m.insert('c', 20);
  ASSERT_EQ(4, m.height());  
  m.insert('f', 50);
  ASSERT_EQ(4, m.height());  
}


//----------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}