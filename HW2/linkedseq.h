
//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// FILE: linkedlist.h
// DATE: Fall 2021
// DESC: this file calls various functions through LinkedSeq by using templating
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


template<typename T>
LinkedSeq<T>::LinkedSeq()
{
  head = nullptr;
  tail = nullptr;
  node_count = 0;
}


template<typename T>
LinkedSeq<T>::LinkedSeq(const LinkedSeq<T>& rhs)
{
  *this = rhs;
}


template<typename T>
LinkedSeq<T>::LinkedSeq(LinkedSeq&& rhs)
{
  *this = std::move(rhs);
}


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






/*
  if(this != &rhs && rhs.node_count > 0)
  {
    Node* rhs_tmp;
    Node* lhs_list;
    
    node_count = rhs.node_count;
    head = new Node;
    lhs_list = head;
    rhs_tmp = rhs.head;
    
    while(rhs_tmp->next != nullptr)
    {
      lhs_list->value = rhs_tmp->value;
      rhs_tmp = rhs_tmp->next;
      lhs_list->next = new Node;
      lhs_list = lhs_list->next;
    }
    tail = lhs_list;
    lhs_list->value = rhs_tmp->value;
  }
*/

  return *this;
}


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
 
  
template<typename T>
LinkedSeq<T>::~LinkedSeq()
{
  make_empty();
}


template<typename T>
int LinkedSeq<T>::size() const
{
  return node_count;
}


template<typename T>
bool LinkedSeq<T>::empty() const
{
  return node_count == 0;
}


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


// valgrind ./hw2_test


template<typename T>
void LinkedSeq<T>::sort()
{
  // TODO: saved for a future assignment
}


#endif
