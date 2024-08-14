
//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// FILE: linkedlist.h
// DATE: Fall 2021
// DESC: This file calls various functions through LinkedSeq by using templating.
//----------------------------------------------------------------------


#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <ostream>
#include "sequence.h"


template<typename T>
class LinkedSeq : public Sequence<T>
{
public:

  // implements merge sort over current sequence
  void merge_sort();

  // implements quick sort over current sequence
  void quick_sort();

  // Default constructor
  LinkedSeq();

  // Copy constructor
  LinkedSeq(const LinkedSeq& rhs);

  // Move constructor
  LinkedSeq(LinkedSeq&& rhs);

  // Copy assignment operator
  LinkedSeq& operator=(const LinkedSeq& rhs);

  // Move assignment operator
  LinkedSeq& operator=(LinkedSeq&& rhs);
  
  // Destructor
  ~LinkedSeq();
  
  // Returns the number of elements in the sequence
  int size() const override;

  // Tests if the sequence is empty
  bool empty() const override;

  // Returns a reference to the element at the index in the
  // sequence. Used for lvalues (assignments into the
  // sequence). Throws out_of_range if index is invalid (less than 0
  // or greater than or equal to size()).
  T& operator[](int index) override;

  // Returns a constant address to the element at the index in the
  // sequence. Used for rvalues (evaluating to the value at the
  // index). Throws out_of_range if index is invalid (less than 0 or
  // greater than or equal to size()).
  const T& operator[](int index) const override;

  // Extends (grows) the sequence by inserting the element at the
  // given index (shifting existing elements to the "right" in the
  // sequence).  Throws out_of_range if the index is invalid (less
  // than 0 or greater than size()).
  void insert(const T& elem, int index) override;

  // Shrinks the sequence by removing the element at the index in the
  // sequence (shifing elements to the "left" in the sequence). Throws
  // out_of_range if index is invalid.
  void erase(int index) override;

  // Returns true if the element is in the sequence, and false
  // otherwise.
  bool contains(const T& elem) const override;

  // Sorts the elements in the sequence using less than equal (<=)
  // operator. (Not implemented in HW-2)
  void sort() override; 
  
private:

  // linked list node
  struct Node {
    T value;
    Node* next = nullptr;
  };

  // helper functions for merge sort and quick sort
  Node* merge_sort(Node* left, int len);

  Node* quick_sort(Node* start, int len);

  // head pointer
  Node* head = nullptr;

  // tail pointer
  Node* tail = nullptr;

  // size of list
  int node_count = 0;

  // helper to delete all the nodes in the list (called by destructor
  // and copy assignment operator)
  void make_empty();
};


// LinkedSeq merge_sort()
template<typename T>
void LinkedSeq<T>::merge_sort()
{
  head = merge_sort(head, node_count);
  tail = head;
  for(int i = 0; i < node_count - 1; i++)
    tail = tail->next;
}

// LinkedSeq quick_sort()
template<typename T>
void LinkedSeq<T>::quick_sort()
{
  head = quick_sort(head, node_count);
  tail = head;
  for(int i = 0; i < node_count - 1; i++)
    tail = tail->next;
}

// LinkedSeq merge_sort() helper
template<typename T>
typename LinkedSeq<T>::Node* LinkedSeq<T>::merge_sort(Node* left, int len)
{
  if(len <= 1)
    return left;
  
  int mid = len / 2;

  Node* rightPtr = left;
  Node* leftPtr = left;
  Node* tmp = left;

  // loop to find first node on right
  for(int i = 0; i < mid - 1; i++)
    tmp = tmp->next;

  rightPtr = tmp->next;
  tmp->next = nullptr;

  leftPtr = merge_sort(left, mid);
  rightPtr = merge_sort(rightPtr, len - mid);

  Node* curr = new Node;
  Node* curr_head = curr;
  
  // splice back together
  while(leftPtr != nullptr && rightPtr != nullptr)
  {
    if(leftPtr->value < rightPtr->value)
    {
      curr->next = leftPtr;
      curr = curr->next;
      leftPtr = leftPtr->next;
    }
    else
    {
      curr->next = rightPtr;
      curr = curr->next;
      rightPtr = rightPtr->next;
    }
  }

  // case if right partition finished before left
  while(leftPtr != nullptr)
  {
    curr->next = leftPtr;
    curr = curr->next;
    leftPtr = leftPtr->next;
  }
  // case if left partition finished before right
  while(rightPtr != nullptr)
  {
    curr->next = rightPtr;
    curr = curr->next;
    rightPtr = rightPtr->next;
  }
  
  rightPtr = curr_head->next;
  delete curr_head;

  return rightPtr;
}

// LinkedSeq quick_sort() helper
template<typename T>
typename LinkedSeq<T>::Node* LinkedSeq<T>::quick_sort(Node* start, int len)
{
  if(len <= 1)
    return start;
  
  // cut connection from pivot to rest of list
  Node* pivot = start;
  Node* cur = pivot->next;
  pivot->next = nullptr;

  Node* smaller = nullptr;
  Node* smaller_cur = nullptr; // head of smaller
  Node* larger = nullptr;
  Node* larger_cur = nullptr; // head of larger

  int smaller_len = 0;
  int larger_len = 0;

  // run through len times
  for(int i = 0; i < len - 1; i++)
  {
    Node* cur_next_value = cur->next;

    if(cur->value <= pivot->value)
    {
      // first node added in smaller
      if(smaller_cur == nullptr)
      {
        smaller = cur;
        smaller_cur = smaller;
      }
      else
      {
        smaller->next = cur;
        smaller = smaller->next;
      }
      smaller_len++;
    }
    else
    {
      // first node in larger
      if(larger_cur == nullptr)
      {
        larger = cur;
        larger_cur = larger;
      }
      else
      {
        larger->next = cur;
        larger = larger->next;
      }
      larger_len++;
    }
    cur->next = nullptr;
    cur = cur_next_value;
  }

  // recursive calls
  smaller_cur = quick_sort(smaller_cur, smaller_len);
  larger_cur = quick_sort(larger_cur, larger_len);

  smaller = smaller_cur;

  // navigate to end of smaller
  for(int i = 0; i < smaller_len - 1; ++i)
    smaller = smaller->next;

  // nodes exist in smaller
  if(smaller_len != 0)
    smaller->next = pivot;

  // link pivot to larger list
  pivot->next = larger_cur;

  // no nodes exist in smaller
  if(smaller_len == 0)
    return pivot;

  return smaller_cur;
}


template<typename T>
void LinkedSeq<T>::make_empty()
{
  Node* cur = head;
  Node* tmp = nullptr;
  while(cur != nullptr)
  {
    tmp = cur->next;
    delete cur;
    cur = tmp;
  }
  head = tail = nullptr;
  node_count = 0;
}

// String insertion operator
template<typename T>
std::ostream& operator<<(std::ostream& stream, const LinkedSeq<T>& seq)
{
  for(int i = 0; i < seq.size(); ++i)
  {
    stream << seq[i];
    if(i != seq.size() - 1)
      stream << ", ";
  }
  return stream;
}

// Default constructor
template<typename T>
LinkedSeq<T>::LinkedSeq()
{
  head = nullptr;
  tail = nullptr;
  node_count = 0;
}

// Copy constructor
template<typename T>
LinkedSeq<T>::LinkedSeq(const LinkedSeq<T>& rhs)
{
  *this = rhs;
}

// Move constructor
template<typename T>
LinkedSeq<T>::LinkedSeq(LinkedSeq&& rhs)
{
  *this = std::move(rhs);
}

// Copy assignment operator
template<typename T>
LinkedSeq<T>& LinkedSeq<T>::operator=(const LinkedSeq<T>& rhs)
{
  // both empty
  if((rhs.head == nullptr) && (this->head == nullptr))
    return * this;
  
  if(this != &rhs)
  {
    this->make_empty();
    Node* tmp = new Node;
    tmp->value = rhs.head->value;
    this->head = tmp;
    Node* rhsPt = rhs.head;
    rhsPt = rhsPt->next;

    for(int i = 1; i < rhs.size() - 1; ++i)
    {
      Node* tmp2 = new Node;
      tmp->next = tmp2;
      tmp2->value = rhsPt->value;
      rhsPt = rhsPt->next;
      tmp = tmp->next;
    }

    Node* tmp2 = new Node;
    tmp->next = tmp2;
    tmp2->value = rhsPt->value;
    this->tail = tmp2;
    this->node_count = rhs.size();
  }
  return *this;
}

// Move assignment operator
template<typename T>
LinkedSeq<T>& LinkedSeq<T>::operator=(LinkedSeq<T>&& rhs)
{
  if(this != &rhs)
  {
    make_empty();
    head = rhs.head;
    tail = rhs.tail;
    node_count = rhs.node_count;
    // zero out rhs
    rhs.tail = rhs.head = nullptr;
    rhs.node_count = 0;
  }

  return *this;
}
 
// Destructor
template<typename T>
LinkedSeq<T>::~LinkedSeq()
{
  make_empty();
}

// Size function
template<typename T>
int LinkedSeq<T>::size() const
{
  return node_count;
}

// Empty function
template<typename T>
bool LinkedSeq<T>::empty() const
{
  return node_count == 0;
}

// Indexing operator 1
template<typename T>
T& LinkedSeq<T>::operator[](int index)
{
  if(index >= node_count || index < 0)
    throw std::out_of_range("LinkedSeq<T>::operator[](int)");
    
  if(index == node_count - 1)
    return tail->value;

  Node* tmp = head;
  
  for(int i = 0; i < index; ++i)
    tmp = tmp->next;
    
  return tmp->value;
}

// Indexing operator 2
template<typename T>
const T& LinkedSeq<T>::operator[](int index) const
{
  if(index >= node_count || index < 0)
    throw std::out_of_range("LinkedSeq<T>::operator[](int)const");
   
  if(index == node_count - 1)
    return tail->value;

  Node* tmp = head;
  
  for(int i = 0; i < index; ++i)
    tmp = tmp->next;
    
  return tmp->value;   
}

// Insert function
template<typename T>
void LinkedSeq<T>::insert(const T& elem, int index)
{
  if(index > node_count || index < 0)
    throw std::out_of_range("LinkedSeq<T>::insert(const T&, int)");
    
  Node* new_node = new Node;
  new_node->value = elem;
  
  // empty list insert or head position insert
  if(index == 0)
  {
    new_node->next = head;
    head = new_node;
    if(node_count == 0)
      tail = new_node;
  }
  // tail position insert
  else if(index == node_count)
  {
    new_node->next = nullptr;
    tail->next = new_node;
    tail = new_node;
  }
  else
  {
    Node* tmp = head;
    // traverse through list
    for(int i = 0; i < index - 1; ++i)
    {
      tmp = tmp->next;
    }
    new_node->next = tmp->next;
    tmp->next = new_node;
  }
  node_count++;
}

// Erase function
template<typename T>
void LinkedSeq<T>::erase(int index) 
{
  if(index >= node_count || index < 0)
    throw std::out_of_range("LinkedSeq<T>::erase(int)");
  else if(index == 0) // head
  {
    Node* tmp = head;
    head = head->next;
    delete tmp;
    tmp = nullptr;
    node_count--;
  }
  else if(index == node_count - 1) // tail
  {
    Node* tmp = head;
    for(int i = 0; i < node_count - 1; ++i)
      tmp = tmp->next;
    tail = tmp;
    delete tmp->next;
    tmp->next = nullptr;
    node_count--;
  }
  else
  {
    Node* tmp = head;
    for(int i = 0; i < index - 1; ++i)
      tmp = tmp->next;
    Node* const item = tmp->next;
    tmp->next = item->next;
    delete item;
    node_count--;
  }
}

// Contains function
template<typename T>
bool LinkedSeq<T>::contains(const T& elem) const 
{
  Node* tmp = head;
  
  for(int i = 0; i < node_count; ++i)
  {
    if(tmp->value == elem)
      return true;
    tmp = tmp->next;
  }
  return false;
}

// Sort function
template<typename T>
void LinkedSeq<T>::sort()
{
  // TODO: saved for a future assignment
}


#endif