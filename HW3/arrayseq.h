
//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// FILE: arrayseq.h
// DATE: Fall 2021
// DESC: 
//----------------------------------------------------------------------


#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdexcept>
#include <ostream>
#include "sequence.h"


template<typename T>
class ArraySeq : public Sequence<T>
{
public:

  // Default constructor
  ArraySeq();

  // Copy constructor
  ArraySeq(const ArraySeq& rhs);

  // Move constructor
  ArraySeq(ArraySeq&& rhs);

  // Copy assignment operator
  ArraySeq& operator=(const ArraySeq& rhs);

  // Move assignment operator
  ArraySeq& operator=(ArraySeq&& rhs);
  
  // Destructor
  ~ArraySeq();
  
  // Returns the number of elements in the sequence
  virtual int size() const;

  // Tests if the sequence is empty
  virtual bool empty() const;

  // Returns a reference to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual T& operator[](int index);

  // Returns a constant address to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual const T& operator[](int index) const;

  // Extends the sequence by inserting the element at the given
  // index. Throws out_of_range if the index is invalid.
  virtual void insert(const T& elem, int index);

  // Shrinks the sequence by removing the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual void erase(int index);

  // Returns true if the element is in the sequence, and false
  // otherwise.
  virtual bool contains(const T& elem) const;

  // Sorts the elements in the sequence using less than equal (<=)
  // operator. (Not implemented in HW-3)
  virtual void sort(); 
  
private:

  // resizable array
  T* array = nullptr;

  // size of list
  int count = 0;

  // max capacity of the array
  int capacity = 0;

  // helper to double the capacity of the array
  void resize();
  
  // helper to delete the array list (called by destructor and copy
  // constructor)
  void make_empty();

};


// Default constructor
template<typename T>
ArraySeq<T>::ArraySeq()
{}

// Copy constructor
template<typename T>
ArraySeq<T>::ArraySeq(const ArraySeq& rhs)
{
  *this = rhs;
  /*
  array = new T[rhs.capacity];
  for(int i = 0; i < rhs.capacity; ++i)
    array[i] = rhs[i];
  count = rhs.count;
  capacity = rhs.capacity;
  */
}

// Move constructor
template<typename T>
ArraySeq<T>::ArraySeq(ArraySeq&& rhs)
{
  *this = std::move(rhs);
}

// Copy assignment operator
template<typename T>
ArraySeq<T>& ArraySeq<T>::operator=(const ArraySeq<T>& rhs)
{
  /*
  array = new T[rhs.capacity];
  for(int i = 0; i < rhs.capacity; ++i)
    array[i] = rhs[i];
  count = rhs.count;
  capacity = rhs.capacity;
  */
  
  if(this != &rhs)
  {
    make_empty();
    count = rhs.count;
    capacity = rhs.capacity;
    array = new T[rhs.capacity];
    for(int i = 0; i < capacity; ++i)
    {
      array[i] = rhs.array[i];
    }
  }
  return *this;
}

// Move assignment operator
template<typename T>
ArraySeq<T>& ArraySeq<T>::operator=(ArraySeq<T>&& rhs)
{
  if(this != &rhs)
  {
    make_empty();
    count = rhs.count;
    capacity = rhs.capacity;
    rhs.count = 0;
    rhs.capacity = 0;
    array = rhs.array;
    rhs.array = nullptr;
  }
  return *this;
}

// Destructor
template<typename T>
ArraySeq<T>::~ArraySeq()
{
  make_empty();
}

// Stream insertion
template<typename T>
std::ostream& operator<<(std::ostream& stream, const ArraySeq<T>& seq)
{
  for(int i = 0; i < seq.size(); ++i)
  {
    stream << seq[i];
    if(i != seq.size() - 1)
      stream << ", ";
  }
  return stream;
}

// Returns the number of elements in the sequence
template<typename T>
int ArraySeq<T>::size() const
{
  return count;
}

// Tests if the sequence is empty
template<typename T>
bool ArraySeq<T>::empty() const
{
  return count == 0;
}

// Returns a reference to the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
T& ArraySeq<T>::operator[](int index)
{
  if(index >= count || index < 0)
    throw std::out_of_range("ArraySeq<T>::operator[](int)");
  
  return array[index];

}

// Returns a constant address to the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
const T& ArraySeq<T>::operator[](int index) const
{
  if(index >= count || index < 0)
    throw std::out_of_range("ArraySeq<T>::operator[](int) const");
  
  return array[index];
}

// Extends the sequence by inserting the element at the given
// index. Throws out_of_range if the index is invalid.
template<typename T>
void ArraySeq<T>::insert(const T& elem, int index)
{
  if(index > count || index < 0)
    throw std::out_of_range("ArraySeq<T>::insert(const T&, int)");
  
  if(count == 0)
  {
    capacity = 1;
    delete [] array;
    array = new T[capacity];
  }
  else if(count == capacity)
    resize();
  
  if(index == count)
  {
    array[index] = elem;
    count++;
    return;
  }

  /*
  for(int i = index; i < count; i++)
  {
    if(i == index)
    {
      auto tmp = array[index];
      array[i] == elem;
      array[i+1] = tmp;
    }
    else
      array[i+1] = array[i];
  }
  count++;
  */
  //std::cout<<"capacity:" << capacity << std::endl;

  for(int i = count - 1; i >= index; i--)
  {
    //std::cout << "array at pos" << array[i] << std::endl;
    array[i+1] = array[i];

    // if(i == index)
    // {
    //   array[i] == elem;
    //   count++;
    // }
    // else
    //array[i] = array[i-1];
  }
  array[index] = elem;
  count++;  // seg fault

}

// Shrinks the sequence by removing the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
void ArraySeq<T>::erase(int index)
{
  if(index >= count || index < 0)
    throw std::out_of_range("ArraySeq<T>::erase(int)");
  
  if(index == count - 1)
  {
    count--;
    return;
  }
  
  for(int i = index; i < count - 1; ++i)
    array[i] = array[i+1]; // mem leak
  count--;
  
}

// Returns true if the element is in the sequence, and false
// otherwise.
template<typename T>
bool ArraySeq<T>::contains(const T& elem) const
{
  for(int i = 0; i < count; ++i)
  {
    if(array[i] == elem)
      return true;
  }
  return false;
}

// helper to double the capacity of the array
template<typename T>
void ArraySeq<T>::resize()
{
  capacity = count * 2;
  /*
  if(capacity == 0)
    capacity = 10;
  */

  T* new_array = new T[capacity];

  for(int i = 0; i < count; ++i)
    new_array[i] = array[i];

  delete [] array;
  array = new_array;
}

// helper to delete the array list (called by destructor and copy
// constructor)
template<typename T>
void ArraySeq<T>::make_empty()
{
  count = 0;
  capacity = 0;
  delete [] array;
  array = nullptr;
}

// Saved for future assignment
template<typename T>
void ArraySeq<T>::sort()
{
}


#endif
