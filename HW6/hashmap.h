//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// DATE: Fall 2021
// DESC: Implements our hash map
//---------------------------------------------------------------------------

#ifndef HASHMAP_H
#define HASHMAP_H

#include <functional>
#include "map.h"
#include "arrayseq.h"

template<typename K, typename V>
class HashMap : public Map<K,V>
{
public:

  // default constructor
  HashMap();

  // copy constructor
  HashMap(const HashMap& rhs);

  // move constructor
  HashMap(HashMap&& rhs);

  // copy assignment
  HashMap<K,V>& operator=(const HashMap<K,V>& rhs);

  // move assignment
  HashMap<K,V>& operator=(HashMap<K,V>&& rhs);  

  // destructor
  ~HashMap();
  
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

  // Returns true if the key is in the collection, and false otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns the keys in the collection in ascending sorted order
  ArraySeq<K> sorted_keys() const;  

  // statistics functions for the hash table implementation
  int min_chain_length() const;
  int max_chain_length() const;
  double avg_chain_length() const;
  
private:

  // node for linked-list separate chaining
  struct Node {
    K key;
    V value;
    Node* next;
  };

  // number of key-value pairs in map
  int count = 0;

  // max size of the (array) table
  int capacity = 16;

  // threshold for resize and rehash
  const double load_factor_threshold = 0.75;
  
  // array of linked lists
  Node** table = new Node*[capacity];

  // the hash function
  int hash(const K& key) const;

  // resize and rehash the table
  void resize_and_rehash();

  // initialize the table to all nullptr
  void init_table();
  
  // clean up the table and reset member variables
  void make_empty();
};



// TODO: implement the public and private HashMap functions below.

// default constructor
template<typename K, typename V>
HashMap<K,V>::HashMap()
{
  init_table();
}

// copy constructor
template<typename K, typename V>
HashMap<K,V>::HashMap(const HashMap& rhs)
{
  init_table();
  *this = rhs;
}

// move constructor
template<typename K, typename V>
HashMap<K,V>::HashMap(HashMap&& rhs)
{
  init_table();
  *this = std::move(rhs);
}

// copy assignment
template<typename K, typename V>
HashMap<K,V>& HashMap<K,V>::operator=(const HashMap<K,V>& rhs)
{
  if(this != &rhs)
  {
    make_empty();
    capacity = rhs.capacity;
    count = rhs.count;
    table = new Node*[capacity];
    init_table();

    // copy nodes from rhs to lhs
    for(int i = 0; i < capacity; i++)
    {
      Node* rhs_tmp = rhs.table[i];
    
      while(rhs_tmp != nullptr)
      {
        Node* new_node = new Node;
        // transfer values into new node
        new_node->key = rhs_tmp->key;
        new_node->value = rhs_tmp->value;
        // link new node to lhs table
        new_node->next = table[i];
        table[i] = new_node;

        rhs_tmp = rhs_tmp->next;
      }
    }
  }
  return *this;
}

// move assignment
template<typename K, typename V>
HashMap<K,V>& HashMap<K,V>::operator=(HashMap<K,V>&& rhs)
{
  if(this != &rhs)
  {
    make_empty();
    capacity = rhs.capacity;
    count = rhs.count;
    table = rhs.table;
    // zero out rhs and initialize to empty table
    rhs.capacity = 16;
    rhs.count = 0;
    rhs.table = new Node*[rhs.capacity];
    rhs.init_table();
  }
  return *this;
}

// destructor
template<typename K, typename V>
HashMap<K,V>::~HashMap()
{
  make_empty();
}

// Returns the number of key-value pairs in the map
template<typename K, typename V>
int HashMap<K,V>::size() const
{
  return count;
}

// Tests if the map is empty
template<typename K, typename V>
bool HashMap<K,V>::empty() const
{
  return size() == 0;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& HashMap<K,V>::operator[](const K& key)
{ 
  if(contains(key) == false)
  {
    throw std::out_of_range("HashMap<K,V>::operator[](const K&)");
  }
  int index = hash(key);
  if(table[index]->key == key)
  {
    return table[index]->value;
  }
  else
  {
    Node* tmp = table[index];
    while(tmp != nullptr)
    {
      // if given key is in our map
      if(tmp->key == key)
        return tmp->value;
      tmp = tmp->next;
    }
  }

 /*
  for(int i = 0; i < capacity; i++)
  {
    Node* tmp = table[i];
    
    while(tmp != nullptr)
    {
      // if given key is in our map
      if(tmp->key == key)
        return tmp->value;
      tmp = tmp->next;
    }
  }
  throw std::out_of_range("HashMap<K,V>::operator[](const K&)");
  */
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection. 
template<typename K, typename V>
const V& HashMap<K,V>::operator[](const K& key) const
{
  
  if(contains(key) == false)
  {
    throw std::out_of_range("HashMap<K,V>::operator[](const K&)");
  }
  int index = hash(key);
  if(table[index]->key == key)
  {
    return table[index]->value;
  }
  else
  {
    Node* tmp = table[index];
    while(tmp != nullptr)
    {
      // if given key is in our map
      if(tmp->key == key)
        return tmp->value;
      tmp = tmp->next;
    }
  }
  
  /*
  for(int i = 0; i < capacity; i++)
  {
    Node* tmp = table[i];
    
    while(tmp != nullptr)
    {
      // if given key is in our map
      if(tmp->key == key)
        return tmp->value;
      tmp = tmp->next;
    }
  }
  throw std::out_of_range("HashMap<K,V>::operator[](const K&)");
  */
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template<typename K, typename V>
void HashMap<K,V>::insert(const K& key, const V& value)
{
  double lft = (count * 1.0) / capacity;

  if(lft > load_factor_threshold)
    resize_and_rehash();

  int index = hash(key);
  
  Node* new_node = new Node;
  new_node->key = key;
  new_node->value = value;

  new_node->next = table[index];
  table[index] = new_node;
  count++;
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void HashMap<K,V>::erase(const K& key)
{
  if(contains(key) == false)
    throw std::out_of_range("HashMap<K,V>::erase(const K&)");
  
  int index = hash(key);
  Node* cur = table[index];

  // if head node has our key
  if(table[index]->key == key)
  {
    Node* new_head = cur->next;
    delete cur;
    table[index] = new_head;
    count--;
  } 
  // search through the linked chain
  else
  {
    Node* item = cur->next;
    while(item != nullptr)
    {
      if(item->key == key)
      {
        cur->next = item->next;
        delete item;
        count--;
      }
    }
  }
}

// Returns true if the key is in the collection, and false otherwise.
template<typename K, typename V>
bool HashMap<K,V>::contains(const K& key) const
{
  for(int i = 0; i < capacity; i++)
  {
    if(table[i] != nullptr && table[i]->key == key)
      return true;
  }
  return false;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> HashMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  ArraySeq<K> tmp;
  
  for(int i = 0; i < capacity; i++)
  {
    Node* cur = table[i];
    while(cur != nullptr)
    {
      // found a key in our range
      if(cur->key >= k1 && cur->key <= k2)
      {
        tmp.insert(cur->key, tmp.size());
      }
      cur = cur->next;
    }
  }
  return tmp;
}

// Returns the keys in the collection in ascending sorted order
template<typename K, typename V>
ArraySeq<K> HashMap<K,V>::sorted_keys() const
{
  ArraySeq<K> tmp;

  for(int i = 0; i < capacity; i++)
  {
    Node* cur = table[i];
    while(cur != nullptr)
    {
      tmp.insert(cur->key, tmp.size());
      cur = cur->next;
    }
  }
  tmp.sort();
  return tmp;
}

// statistics functions for the hash table implementation
template<typename K, typename V>
int HashMap<K,V>::min_chain_length() const
{
  int min_len = 0;
  int node_counter = 0;

  for(int i = 0; i < capacity; i++)
  {
    Node* cur = table[i];
    while(cur != nullptr)
    {
      node_counter += 1;
      cur = cur->next;
    }
    if(i == 0)
    {
      min_len = node_counter;
    }
    else if (node_counter < min_len)
    {
      min_len = node_counter;
    }
  }

  return min_len;
}

template<typename K, typename V>
int HashMap<K,V>::max_chain_length() const
{
  int max_len = 0;
  int node_counter = 0;

  for(int i = 0; i < capacity; i++)
  {
    Node* cur = table[i];
    while(cur != nullptr)
    {
      node_counter += 1;
      cur = cur->next;
    }
    if(i == 0)
    {
      max_len = node_counter;
    }
    else if (node_counter > max_len)
    {
      max_len = node_counter;
    }
  }

  return max_len;
}

template<typename K, typename V>
double HashMap<K,V>::avg_chain_length() const
{
  int sum_len = 0;
  double avg_len = 0.0;

  for(int i = 0; i < capacity - 1; i++)
  {
    Node* cur = table[i];
    while(cur != nullptr)
    {
      sum_len += 1;
      cur = cur->next;
    }
  }
  avg_len = (sum_len * 1.0) / count;

  return avg_len;
}

// the hash function
template<typename K, typename V>
int HashMap<K,V>::hash(const K& key) const
{
  std::hash<K> hash_fun;
  int value = hash_fun(key);
  int index = value % capacity;

  return index;
}

// resize and rehash the table
template<typename K, typename V>
void HashMap<K,V>::resize_and_rehash()
{
  int index = 0;
  capacity = capacity * 2;
  int new_capacity = capacity;
  Node** resized_table = new Node*[capacity];
  for(int i = 0; i < capacity; i++)
  {
   resized_table[i] = nullptr;
  }

  for(int i = 0; i < capacity / 2; i++)
  {
    Node* cur = table[i];
    while(cur != nullptr)
    {
      index = hash(cur->key);
      Node* new_node = new Node;
      new_node->key = cur->key;
      new_node->value = cur->value;

      new_node->next = resized_table[index];
      resized_table[index] = new_node;

      cur = cur->next;
    } 
  }
  capacity = capacity / 2;
  int new_count = count;
  make_empty();
  table = resized_table;
  capacity = new_capacity;
  count = new_count;
}

// initialize the table to all nullptr
template<typename K, typename V>
void HashMap<K,V>::init_table()
{
  for(int i = 0; i < capacity; i++)
  {
    table[i] = nullptr;
  }
}

// clean up the table and reset member variables
template<typename K, typename V>
void HashMap<K,V>::make_empty()
{
  // loop through to delete every node
  for(int i = 0; i < capacity; i++)
  {
    Node* cur = table[i];
    Node* tmp = cur;
    while(cur != nullptr)
    {
      tmp = cur->next;
      delete cur;
      cur = tmp;
    }
  }

  delete [] table;
  table = nullptr;
  capacity = 0;
  count = 0;
}

#endif