#include "DynamicArray.h"
#include <iostream>

using namespace std;


DynamicArray::DynamicArray() {
  size = 0; // current number of elements in the arra
  maxSize = 5;
  vals = new string[5];
}


string DynamicArray::removeFirst() {

  string firstItem = vals[0];
  for (size_t i = 0; i < size; i += 1) {
    vals[i] = vals[i+1];
  }
  size -= 1;
  
  return firstItem;
}

void DynamicArray::remove(string name) {
  bool isfound = false;
  for (size_t i = 0; i < size; i += 1) {
    if (vals[i] == name) {
      isfound = true;
    }
    if (isfound == true) {
      vals[i] = vals[i+1];
    }
  }
  size -= 1;
}

void DynamicArray::add(string val) {

  // vals is the current array of elements (in pointer form)
  // size is the index we want to add the new element to because the last element
  //   will be at index size - 1

  // array doubles in size if run out of room. creates a new array and swaps the pointer
  if (size == maxSize) {
    cout << "RESIZING ARRAY" << endl;
    maxSize *= 2;
    string* temp = new string[maxSize]; // declare a temporary pointer to an array

    // load in existing values in array
    for (size_t i = 0; i < size; i += 1) {
      temp[i] = vals[i];
    }

    swap(vals, temp); // swap() swaps vals and temp pointers
    delete[] temp;
    
  }

  vals[size] = val;
  size += 1;
  
}

void DynamicArray::print() {

  for (size_t i = 0; i < size; i += 1) {
    if (i < size - 1) {
      cout << vals[i] << ", ";
    }
    else {
      cout << vals[i];
    }
  }
  cout << endl;
  
}


string DynamicArray::get(int index) {
  return vals[index];
}

bool DynamicArray::contains(string val) {

  for (size_t i = 0; i < size; i += 1) {
    if (vals[i] == val) {
      return true;
    }
  }
  return false;
  
}