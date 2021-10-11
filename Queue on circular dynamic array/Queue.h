/// IMPLEMENTATION OF A QUEUE BASED ON A CIRCULAR DYNAMIC ARRAY

#pragma once

#include <vector>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

class Queue {
private:
    int m_elementsNumber;
    int m_capacity;
    int m_nextElementIndex;
    int m_lastElementIndex;
    TElem* m_collection;

public:
    // constructor
    Queue();

    // pushes an element to the end of the queue
    void push(TElem newElement);

    // returns the element from the front of the queue
    // throws exception if the queue is empty
    TElem top() const;

    // removes and returns the element from the front of the queue
    // throws exception if the queue is empty
    TElem pop();

    // checks if the queue is empty
    bool isEmpty() const;

    // destructor
    ~Queue();
};
