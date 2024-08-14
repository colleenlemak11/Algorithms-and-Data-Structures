//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// DATE: Fall 2021
// DESC: Implements binary search map
//---------------------------------------------------------------------------

#ifndef BINSEARCHMAP_H
#define BINSEARCHMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class BinSearchMap : public Map<K,V>
{
public:

  // Returns the number of key-value pairs in the map
  int size() const;

  // Tests if the map is empty
  bool empty() const;

  // Allows values associated with a key to be updated. Throws
  // out_of_range if the given key is not in the collection.
  V& operator[](const K& key);

  // Returns the value for a given key. Throws out_of_range if the
  // given key is not in the collection. 
  const V& operator[](const K& key) const;

  // Extends the collection by adding the given key-value
  // pair. Assumes the key being added is not present in the
  // collection. Insert does not check if the key is present.
  void insert(const K& key, const V& value);

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
  void erase(const K& key);

  // Returns true if the key is in the collection, and false
  // otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns the keys in the collection in ascending sorted order.
  ArraySeq<K> sorted_keys() const;  

private:

  // If the key is in the collection, bin_search returns true and
  // provides the key's index within the array sequence (via the index
  // output parameter). If the key is not in the collection,
  // bin_search returns false and provides the last index checked by
  // the binary search algorithm. 
  bool bin_search(const K& key, int& index) const;
  
  // implemented as a resizable array of (key-value) pairs
  ArraySeq<std::pair<K,V>> seq;

};


// TODO: Implement the BinSearchMap functions below. Note that you do
//       not need to implement a default constructor, destructor, copy
//       constructor, copy assignment operator, move constructor, and
//       move assignment operator for this version of Map. Instead,
//       the default C++ implementations are sufficient.


// Returns the number of key-value pairs in the map
template<typename K, typename V>
int BinSearchMap<K,V>::size() const
{
  return seq.size();
}

// Tests if the map is empty
template<typename K, typename V>
bool BinSearchMap<K,V>::empty() const
{
  return (size() == 0);
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& BinSearchMap<K,V>::operator[](const K& key)
{
  int key_idx = -1;
  bool result = false;
  result = bin_search(key, key_idx);
  if(result == false)
    throw std::out_of_range("BinSearchMap<K,V>::operator[](const K&)");
  else
    return seq[key_idx].second;
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection. 
template<typename K, typename V>
const V& BinSearchMap<K,V>::operator[](const K& key) const
{
  int key_idx = -1;
  bool result = false;
  result = bin_search(key, key_idx);
  if(result == false)
    throw std::out_of_range("BinSearchMap<K,V>::operator[](const K&)");
  else
    return seq[key_idx].second;
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template<typename K, typename V>
void BinSearchMap<K,V>::insert(const K& key, const V& value)
{
  std::pair<K,V> p = {key, value};
  int key_idx = -1;

  bin_search(key, key_idx);
  if(seq.size() == 0)
    seq.insert(p, 0);
  else if(seq[key_idx].first < key)
    seq.insert(p, key_idx + 1);
  else
    seq.insert(p, key_idx);
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void BinSearchMap<K,V>::erase(const K& key)
{
  int key_idx = -1;
  bool result = false;
  result = bin_search(key, key_idx);
  if(result == true)
    seq.erase(key_idx);
  else
  {

    throw std::out_of_range("BinSearchMap<K,V>::erase(const K&)");
  }
}

// Returns true if the key is in the collection, and false
// otherwise.
template<typename K, typename V>
bool BinSearchMap<K,V>::contains(const K& key) const
{
  int key_idx = -1;
  bool result = false;
  result = bin_search(key, key_idx);
  return result;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> BinSearchMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  ArraySeq<K> tmp;
  int k1_idx = -1;
  int k2_idx = -1;
  bool k1_result = false;
  bool k2_result = false;

  k1_result = bin_search(k1, k1_idx);
  k2_result = bin_search(k2, k2_idx);

  if(k2_result == false && k2_idx == seq.size())
    k2_idx--;

  for(int i = k1_idx; i <= k2_idx; i++)
  {
    std::pair<K,V> p = seq[i];
    tmp.insert(p.first, tmp.size());
  }
  return tmp;
}

// Returns the keys in the collection in ascending sorted order.
template<typename K, typename V>
ArraySeq<K> BinSearchMap<K,V>::sorted_keys() const
{
  ArraySeq<K> tmp;
  for(int i = 0; i < seq.size(); i++)
  {
    std::pair<K,V> p = seq[i];
    tmp.insert(p.first, tmp.size());
  }
  tmp.sort();
  return tmp;
}

// If the key is in the collection, bin_search returns true and
// provides the key's index within the array sequence (via the index
// output parameter). If the key is not in the collection,
// bin_search returns false and provides the last index checked by
// the binary search algorithm. 
template<typename K, typename V>
bool BinSearchMap<K,V>::bin_search(const K& key, int& index) const
{
  int start = 0;
  int end = seq.size() - 1;
  index = 0;

  // check if key is in collection
  while(start <= end)
  {
    index = (start + end) / 2;
    if(seq[index].first == key)
    {
      return true;
    }
    // search left half
    if(seq[index].first > key)
    {
      end = index - 1;
    }
    // search right half
    else
    {
      start = index + 1;
    }
  }
  return false;
}


#endif
