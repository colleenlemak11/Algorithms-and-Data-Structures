//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// FILE: hw6_test.cpp
// DATE: Fall 2021
// DESC: Basic HashMap tests
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "arrayseq.h"
#include "hashmap.h"

using namespace std;

//----------------------------------------------------------------------
// Basic Tests for the HashMap implementation of Map
//----------------------------------------------------------------------

TEST(BasicHashMapTests, EmptyCheck)
{
  HashMap<char,int> m;
  ASSERT_EQ(true, m.empty());
  ASSERT_EQ(0, m.size());
}

TEST(BasicHashMapTests, InsertCheck)
{
  HashMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('c', 30);
  m.insert('d', 40);
  ASSERT_EQ(false, m.empty());
  ASSERT_EQ(4, m.size());
}

TEST(BasicHashMapTests, RValueAccessCheck)
{
  HashMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('c', 30);
  m.insert('d', 40);
  ASSERT_EQ(4, m.size());
  ASSERT_EQ(10, m['a']);
  ASSERT_EQ(20, m['b']);
  ASSERT_EQ(30, m['c']);
  ASSERT_EQ(40, m['d']);
}

TEST(BasicHashMapTests, LValueAccessCheck)
{
  HashMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('c', 30);
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

TEST(BasicHashMapTests, ContainsCheck)
{
  HashMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('c', 30);
  m.insert('d', 40);
  ASSERT_EQ(true, m.contains('a'));
  ASSERT_EQ(true, m.contains('b'));
  ASSERT_EQ(true, m.contains('c'));
  ASSERT_EQ(true, m.contains('d'));
  ASSERT_EQ(false, m.contains('e'));
}

TEST(BasicHashMapTests, EraseCheck)
{
  HashMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('c', 30);
  m.insert('d', 40);
  ASSERT_EQ(4, m.size());
  m.erase('a');
  ASSERT_EQ(3, m.size());
  ASSERT_EQ(false, m.contains('a'));
  m.erase('c');
  ASSERT_EQ(2, m.size());
  ASSERT_EQ(false, m.contains('c'));
  m.erase('d');
  ASSERT_EQ(1, m.size());
  ASSERT_EQ(false, m.contains('d'));
  m.erase('b');
  ASSERT_EQ(0, m.size());
  ASSERT_EQ(false, m.contains('b'));
}

TEST(BasicHashMapTests, KeyRangeCheck)
{
  HashMap<char,int> m;
  m.insert('b', 10);
  m.insert('c', 20);
  m.insert('d', 30);
  m.insert('e', 40);
  ArraySeq<char> k;
  k = m.find_keys('b', 'd');
  ASSERT_EQ(3, k.size());
  ASSERT_EQ(true, k.contains('b') and k.contains('c') and k.contains('d'));
  k = m.find_keys('a', 'c');
  ASSERT_EQ(2, k.size());
  ASSERT_EQ(true, k.contains('b') and k.contains('c'));
  k = m.find_keys('d', 'f');
  ASSERT_EQ(2, k.size());
  ASSERT_EQ(true, k.contains('d') and k.contains('e'));
}

TEST(BasicHashMapTests, SortedKeyCheck)
{
  HashMap<char,int> m;
  m.insert('e', 50);
  m.insert('a', 10);
  m.insert('c', 30);
  m.insert('b', 20);
  m.insert('d', 40);
  ArraySeq<char> k;
  k = m.sorted_keys();
  ASSERT_EQ(5, k.size());
  ASSERT_EQ('a', k[0]);
  ASSERT_EQ('b', k[1]);
  ASSERT_EQ('c', k[2]);  
  ASSERT_EQ('d', k[3]);  
  ASSERT_EQ('e', k[4]);  
}

TEST(BasicHashMapTests, InvalidKeyCheck)
{
  HashMap<char,int> m;
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

TEST(BasicHashMapTests, ResizeRehashCheck)
{
  HashMap<int,int> m;
  // should resize and rehash three times
  for (int i = 1; i <= 35; ++i)
    m.insert(i, i*10);
  ASSERT_EQ(35, m.size());
  for (int i = 1; i <= 35; ++i) {
    ASSERT_EQ(true, m.contains(i));
    ASSERT_EQ(i*10, m[i]);
  }
}

TEST(BasicHashMapTests, DestructorCheck)
{
  HashMap<char,int>* m = new HashMap<char,int>;
  EXPECT_NO_THROW(delete m);
  m = new HashMap<char,int>;
  m->insert('a', 1);
  EXPECT_NO_THROW(delete m);
  m = new HashMap<char,int>;
  for (char c = 'a'; c <= 'z'; ++c)
    m->insert(c, (int)(c - 'a'));
  EXPECT_NO_THROW(delete m);
}

TEST(BasicHashMapTests, CopyConstructorCheck)
{
  // copy empty seq
  HashMap<char,int> m1;
  HashMap<char,int> m2(m1);
  ASSERT_EQ(m1.size(), m2.size());
  // copy one-element seq
  m1.insert('a', 1);
  ASSERT_NE(m1.size(), m2.size());
  m2.insert('b', 2);
  m2.insert('c', 3);
  m2.insert('d', 4);
  HashMap<char,int> m3(m2);
  ASSERT_EQ(m2.size(), m3.size());
  // remove item and check two seqs are different
  m3.erase('c');
  ASSERT_NE(m2.size(), m3.size());
  ASSERT_EQ(true, m2.contains('c'));
  ASSERT_EQ(false, m3.contains('c'));
}

TEST(BasicHashMapTests, CopyAssignmentCheck)
{
  HashMap<char,int> m1;
  HashMap<char,int> m2;
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
  m2.insert('c', 0);
  m2.insert('d', 1);
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

TEST(BasicHashMapTests, MoveConstructorCheck)
{
  // move empty map
  HashMap<char,int> m1;
  HashMap<char,int> m2(std::move(m1));
  ASSERT_EQ(0, m1.size());
  ASSERT_EQ(0, m2.size());
  // move one-element ma[
  HashMap<char,int> m3;
  m3.insert('a', 1);
  ASSERT_EQ(1, m3.size());
  ASSERT_EQ(true, m3.contains('a'));
  HashMap<char,int> m4(std::move(m3));
  ASSERT_EQ(0, m3.size());
  ASSERT_EQ(1, m4.size());
  ASSERT_EQ(true, m4.contains('a'));
  // add item to new m (to ensure correct move)
  m4.insert('b', 2);
  ASSERT_EQ(0, m3.size());
  ASSERT_EQ(2, m4.size());
  ASSERT_EQ(true, m4.contains('a') and m4.contains('b'));
}

TEST(BasicHashMapTests, MoveAssignmentCheck)
{
  // create a map
  HashMap<char,int> m1;
  m1.insert('a', 1);
  m1.insert('b', 2);
  m1.insert('c', 3);
  ASSERT_EQ(3, m1.size());
  // and another
  HashMap<char,int> m2;
  m2.insert('d', 4);
  ASSERT_EQ(1, m2.size());
  // move first to second
  m2 = std::move(m1);
  ASSERT_EQ(0, m1.size());
  ASSERT_EQ(3, m2.size());
  ASSERT_EQ(true, m2.contains('a') && m2.contains('b') && m2.contains('c'));
  m1.insert('e', 5);
  m1.insert('f', 6);
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(true, m1.contains('e') && m1.contains('f'));
  ASSERT_EQ(false, m2.contains('e') || m2.contains('f'));
  // create an empty map
  HashMap<char,int> m3;
  ASSERT_EQ(0, m3.size());
  // move second to third
  m3 = std::move(m2);
  ASSERT_EQ(3, m3.size());
  ASSERT_EQ(0, m2.size());
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(true, m3.contains('a') && m3.contains('b') && m3.contains('c'));
}


//----------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
