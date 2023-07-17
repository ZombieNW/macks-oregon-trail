#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdio.h>
#include <string>

using namespace std;

class DynamicArray {


  public:

    // declaration of default constructor
    DynamicArray();

    string removeFirst();

    void remove(string name);

    void add(string val);

    string get(int index);

    void print();

    bool contains(string val);

    string* vals; // pointer to values
    size_t size; // number of elements in array
    size_t maxSize; // number of elements current array is allocated for 
};



#endif // DYNAMICARRAY_H