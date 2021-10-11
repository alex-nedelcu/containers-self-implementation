/// IMPLEMENTATION OF A QUEUE BASED ON A CIRCULAR DYNAMIC ARRAY

#include "Queue.h"
#include <exception>

using namespace std;


Queue::Queue() {
    m_elementsNumber = 0;
    m_capacity = 5;
    m_nextElementIndex = -1;
    m_lastElementIndex = -1;
    m_collection = new TElem[m_capacity];
}


void Queue::push(TElem newElement) {
    if (m_elementsNumber == m_capacity)
        if (m_nextElementIndex < m_lastElementIndex) {
            // resize case 1
            m_capacity *= 2;
            TElem* doubledCollection = new TElem[m_capacity];

            int copyIndex = 0;
            for (int i = m_nextElementIndex; i <= m_lastElementIndex; i++)
                doubledCollection[copyIndex++] = m_collection[i];

            delete[] m_collection;
            m_collection = doubledCollection;
            m_nextElementIndex = 0;
            m_lastElementIndex = m_elementsNumber - 1;
        } else if (m_nextElementIndex > m_lastElementIndex) {
            // resize case 2
            m_capacity *= 2;
            TElem* doubledCollection = new TElem[m_capacity];

            int copyIndex = 0;
            // copy first part (from the next element in the queue to the top)
            for (int i = m_nextElementIndex; i < m_elementsNumber; i++)
                doubledCollection[copyIndex++] = m_collection[i];

            // copy second part (from the beginning to the last element in the queue)
            for (int i = 0; i <= m_lastElementIndex; i++)
                doubledCollection[copyIndex++] = m_collection[i];

            // e.g.    |19|1| | | | | | | | |5|7|15|11|14|
            //         -->LAST             FIRST ---------

            delete[] m_collection;
            m_collection = doubledCollection;
            m_nextElementIndex = 0;
            m_lastElementIndex = m_elementsNumber - 1;
        }

    // adding the new element
    if (m_nextElementIndex == -1 && m_lastElementIndex == -1) {
        // the queue is empty
        m_collection[0] = newElement;
        m_lastElementIndex = 0;
        m_nextElementIndex = 0;
        m_elementsNumber++;
    } else if (m_lastElementIndex < m_capacity - 1) {
        // we can add the new element on the next position w.r.t. to the last element
        m_collection[m_lastElementIndex + 1] = newElement;
        m_lastElementIndex++;
        m_elementsNumber++;
    } else if (m_lastElementIndex == m_capacity - 1) {
        // we must add the new element at the beginning, because the ex-last element was already at the end of the dynamic array
        m_collection[0] = newElement;
        m_lastElementIndex = 0;
        m_elementsNumber++;
    }
} // theta(1) amortized


TElem Queue::pop() {
    if (m_elementsNumber == 0)
        throw exception();

    TElem poppedElement = m_collection[m_nextElementIndex];

    if (m_nextElementIndex < m_capacity - 1)
        m_nextElementIndex++;

    if (m_nextElementIndex == m_capacity - 1)
        m_nextElementIndex = 0;

    m_elementsNumber--;

    return poppedElement;
}


TElem Queue::top() const {
    if (m_elementsNumber == 0)
        throw exception();

    return m_collection[m_nextElementIndex];
}


bool Queue::isEmpty() const {
    if (m_elementsNumber == 0)
        return true;
    else
        return false;
}


Queue::~Queue() {
    delete[] m_collection;
}

