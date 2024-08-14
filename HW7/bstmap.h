//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// DATE: Fall 2021
// DESC: This file implements a binary search tree map.
//---------------------------------------------------------------------------

#ifndef BSTMAP_H
#define BSTMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class BSTMap : public Map<K,V>
{
public:

  // default constructor
  BSTMap();

  // copy constructor
  BSTMap(const BSTMap& rhs);

  // move constructor
  BSTMap(BSTMap&& rhs);

  // copy assignment
  BSTMap& operator=(const BSTMap& rhs);

  // move assignment
  BSTMap& operator=(BSTMap&& rhs);  

  // destructor
  ~BSTMap();
  
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

  // Returns the height of the binary search tree
  int height() const;
  
private:

  // node for linked-list separate chaining
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
  };

  // number of key-value pairs in map
  int count = 0;

  // array of linked lists
  Node* root = nullptr;

  // clean up the tree and reset count to zero given subtree root
  void make_empty(Node* st_root);

  // copy assignment helper
  Node* copy(const Node* rhs_st_root) const;
  
  // erase helper
  Node* erase(const K& key, Node* st_root);

  // find_keys helper
  void find_keys(const K& k1, const K& k2, const Node* st_root,
                 ArraySeq<K>& keys) const;

  // sorted_keys helper
  void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

  // height helper
  int height(const Node* st_root) const;
  
};

// TODO: Implement the above functions per the directions in HW-7

// default constructor
template<typename K, typename V>
BSTMap<K,V>::BSTMap()
{
}

// copy constructor
template<typename K, typename V>
BSTMap<K,V>::BSTMap(const BSTMap& rhs)
{
  *this = rhs;
}

// move constructor
template<typename K, typename V>
BSTMap<K,V>::BSTMap(BSTMap&& rhs)
{
  *this = std::move(rhs);
}

// copy assignment
template<typename K, typename V>
BSTMap<K,V>& BSTMap<K,V>::operator=(const BSTMap<K,V>& rhs)
{
  if(this != &rhs)
  {
    make_empty(root);
    root = copy(rhs.root);
    count = rhs.count;
  }
  return *this;
}

// move assignment
template<typename K, typename V>
BSTMap<K,V>& BSTMap<K,V>::operator=(BSTMap<K,V>&& rhs)
{
  if(this != &rhs)
  {
    make_empty(root);
    root = rhs.root;
    rhs.root = nullptr;
    count = rhs.count;
    rhs.count = 0;
  }
  return *this;
}

// destructor
template<typename K, typename V>
BSTMap<K,V>::~BSTMap()
{
  make_empty(root);
}

// Returns the number of key-value pairs in the map
template<typename K, typename V>
int BSTMap<K,V>::size() const
{
  return count;
}

// Tests if the map is empty
template<typename K, typename V>
bool BSTMap<K,V>::empty() const
{
  return size() == 0;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& BSTMap<K,V>::operator[](const K& key)
{
  if(!contains(key))
    throw std::out_of_range("BSTMap<K,V>::operator[](const key");
  else
  {
    Node* tmp = root;
    while(tmp)
    {
      if(tmp->key == key)
      {
        return tmp->value;
      }
      else if(key < tmp->key)
      {
        tmp = tmp->left;
      }
      else
      {
        tmp = tmp->right;
      }
    }
  }
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection. 
template<typename K, typename V>
const V& BSTMap<K,V>::operator[](const K& key) const
{
  if(!contains(key))
    throw std::out_of_range("BSTMap<K,V>::operator[](const key");
  else
  {
    Node* tmp = root;
    while(tmp)
    {
      if(tmp->key == key)
      {
        return tmp->value;
      }
      else if(key < tmp->key)
      {
        tmp = tmp->left;
      }
      else
      {
        tmp = tmp->right;
      }
    }
  }
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template<typename K, typename V>
void BSTMap<K,V>::insert(const K& key, const V& value)
{
  Node* tmp = root;
  Node* new_node = new Node;

  new_node->key = key;
  new_node->value = value;
  new_node->left = nullptr;
  new_node->right = nullptr;

  // case when root is nullptr
  if(tmp == nullptr)
  {
    root = new_node;
    root->left = nullptr;
    root->right = nullptr;
    count++;
    return;
  }

  Node* parent = nullptr;

  while(tmp)
  {
    parent = tmp;
    if(key < tmp->key)
    {
      tmp = tmp->left;
    }
    else
    {
      tmp = tmp->right;
    }
  }

  if(key < parent->key)
  {
    parent->left = new_node;
    count++;
  }
  else
  {
    parent->right = new_node;
    count++;
  }
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void BSTMap<K,V>::erase(const K& key)
{
  if(!contains(key))
    throw std::out_of_range("BSTMap<K,V>::erase(const key");
  root = erase(key, root);
}

// Returns true if the key is in the collection, and false otherwise.
template<typename K, typename V>
bool BSTMap<K,V>::contains(const K& key) const
{
  Node* tmp = root;

  while(tmp)
  {
    if(key == tmp->key)
    {
      return true;
    }
    else if(key < tmp->key)
    {
      tmp = tmp->left;
    }
    else if(key > tmp->key)
    {
      tmp = tmp->right;
    }
  }
  return false;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> BSTMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  ArraySeq<K> tmp;
  find_keys(k1, k2, root, tmp);
  return tmp;
}

// Returns the keys in the collection in ascending sorted order
template<typename K, typename V>
ArraySeq<K> BSTMap<K,V>::sorted_keys() const
{
  ArraySeq<K> tmp;
  sorted_keys(root, tmp);

  return tmp;
}

// Returns the height of the binary search tree
template<typename K, typename V>
int BSTMap<K,V>::height() const
{
  return height(root);
}

// clean up the tree and reset count to zero given subtree root
template<typename K, typename V>
void BSTMap<K,V>::make_empty(Node* st_root)
{
  if(st_root == nullptr)
    return;
  
  make_empty(st_root->left);
  make_empty(st_root->right);

  delete st_root;
  count--;
}

// copy assignment helper
template<typename K, typename V>
typename BSTMap<K,V>::Node* BSTMap<K,V>::copy(const Node* rhs_st_root) const
{
  if(rhs_st_root == nullptr)
    return nullptr;
  
  Node* copied_node = new Node;
  copied_node->key = rhs_st_root->key;
  copied_node->value = rhs_st_root->value;

  copied_node->left = copy(rhs_st_root->left);
  copied_node->right = copy(rhs_st_root->right);

  return copied_node;
}

// erase helper
template<typename K, typename V>
typename BSTMap<K,V>::Node* BSTMap<K,V>::erase(const K& key, Node* st_root)
{
  // loop left or right to get to our node
  if(key < st_root->key)
  {
    st_root->left = erase(key, st_root->left);
  }
  else if(key > st_root->key)
  {
    st_root->right = erase(key, st_root->right);
  }
  else if(key == st_root->key)
  {
    Node* cur = st_root;
    // case 1: one child with no left
    if(cur->left == nullptr)
    {
      st_root = st_root->right;
      delete cur;
      count--;
    }
    // case 2: one child with no right
    else if(cur->right == nullptr)
    {
      st_root = st_root->left;
      delete cur;
      count--;
    }
    // case 3: two children
    else
    {
      Node* prev = st_root->right;
      Node* cur = prev->left;

      if(cur != nullptr)
      {
        while(cur->left != nullptr)
        {
          prev = cur;
          cur = cur->left;
        }
        st_root->key = cur->key;
        st_root->value = cur->value;

        prev->left = cur->right;
        delete cur;
        count--;
      }
      else if(cur == nullptr)
      {
        prev = st_root;
        cur = prev->right;

        st_root->key = cur->key;
        st_root->value = cur->value;

        prev->right = cur->right;

        delete cur;
        count--;
      }
    }
  }
  return st_root;
}

// find_keys helper
template<typename K, typename V>
void BSTMap<K,V>::find_keys(const K& k1, const K& k2, const Node* st_root,
                 ArraySeq<K>& keys) const
{
  if(!st_root)
    return;
  
  if(st_root->key < k1)
    find_keys(k1, k2, st_root->right, keys);
  
  if(st_root->key >= k1 && st_root->key <= k2)
  {
    find_keys(k1, k2, st_root->left, keys);
    keys.insert(st_root->key, keys.size());
    find_keys(k1, k2, st_root->right, keys);
  }

  if(st_root->key > k2)
    find_keys(k1, k2, st_root->left, keys);
}

// sorted_keys helper
template<typename K, typename V>
void BSTMap<K,V>::sorted_keys(const Node* st_root, ArraySeq<K>& keys) const
{
  if(!st_root)
    return;

  sorted_keys(st_root->left, keys);
  keys.insert(st_root->key, keys.size());
  sorted_keys(st_root->right, keys);
 }

// height helper
template<typename K, typename V>
int BSTMap<K,V>::height(const Node* st_root) const
{
  if(st_root == nullptr)
    return 0;
  else
  {
    return 1 + std::max(height(st_root->left), height(st_root->right));
  }
}


#endif
