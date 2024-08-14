//---------------------------------------------------------------------------
// NAME: Colleen Lemak
// FILE: sequence.h
// DATE: Fall 2021
// DESC: An abstract class for representing generic sequences of
//       elements. A sequence is an ordered collection where
//       duplicates are allowed. 
//---------------------------------------------------------------------------

#ifndef SEQUENCE_H
#define SEQUENCE_H

template<typename T>
class Sequence
{
public:

  // For concrete subclasses
  virtual ~Sequence() {}

  // Returns the number of elements in the sequence
  virtual int size() const = 0;

  // Tests if the sequence is empty
  virtual bool empty() const = 0;

  // Returns a reference to the element at the index in the
  // sequence. Used for lvalues (assignments into the
  // sequence). Throws out_of_range if index is invalid (less than 0
  // or greater than or equal to size()).
  virtual T& operator[](int index) = 0;

  // Returns a constant address to the element at the index in the
  // sequence. Used for rvalues (evaluating to the value at the
  // index). Throws out_of_range if index is invalid (less than 0 or
  // greater than or equal to size()).
  virtual const T& operator[](int index) const = 0;

  // Extends (grows) the sequence by inserting the element at the
  // given index (shifting existing elements to the "right" in the
  // sequence).  Throws out_of_range if the index is invalid (less
  // than 0 or greater than size()).
  virtual void insert(const T& elem, int index) = 0;

  // Shrinks the sequence by removing the element at the index in the
  // sequence (shifing elements to the "left" in the sequence). Throws
  // out_of_range if index is invalid.
  virtual void erase(int index) = 0;

  // Returns true if the element is in the sequence, and false
  // otherwise.
  virtual bool contains(const T& elem) const = 0;

  // Sorts the elements in the sequence using less than equal (<=)
  // operator.
  virtual void sort() = 0; 
  
};


#endif
