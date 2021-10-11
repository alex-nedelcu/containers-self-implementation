#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>

using namespace std;

#include <exception>

SortedIteratedList::SortedIteratedList(Relation relation) {
    m_SSLL = new SSLL; // m_SSLL is a pointer to the data structure SSLL on which the ADT list is based
    m_SSLL->head = NULL; // each node is actually its starting address, so considering that there is no head, head = NULL
    m_SSLL->elementsNumber = 0;
    m_relation = relation;
} // theta(1)

int SortedIteratedList::size() const {
    SSLLNode* currentNode = m_SSLL->head;
    int elementsNumber = 0;

    while (currentNode != NULL) {
        elementsNumber++;
        currentNode = currentNode->next;
    }

    return elementsNumber;

    //    return m_SSLL->elementsNumber;
} // theta(n) or theta(1) using the elementsNumber attribute of the m_SSLL

bool SortedIteratedList::isEmpty() const {
    return m_SSLL->head == NULL;
} // theta(1)

ListIterator SortedIteratedList::first() const {
    ListIterator iterator = ListIterator(*this);
    iterator.first();
    return iterator;
} // theta(1)

TComp SortedIteratedList::getElement(ListIterator position) const {
    if (!position.valid())
        throw std::exception();

    return position.getCurrent();
} // theta(1)

TComp SortedIteratedList::remove(ListIterator& position) {
    if (!position.valid())
        throw std::exception();

    if (position.m_currentElement == m_SSLL->head) {
        // we need to remove the head
        TComp removedData = m_SSLL->head->data;
        SSLLNode* removedNode = m_SSLL->head;
        position.next();
        m_SSLL->head = position.m_currentElement;
        delete removedNode;
        return removedData;
    } else {
        ListIterator it = first();
        SSLLNode* previousNode;

        while (it.valid() && it.m_currentElement != position.m_currentElement) {
            previousNode = it.m_currentElement;
            it.next();
        }

        previousNode->next = position.m_currentElement->next;
        TComp removedData = position.getCurrent();
        SSLLNode* removedNode = position.m_currentElement;
        position.next();
        delete removedNode;
        return removedData;
    }
}
// BC: theta(1) - when the node which needs to be removed is the head
// WC: theta(n) - when the node which needs to be removed is the last one
// AC: theta(n)
// Total complexity: O(n)

ListIterator SortedIteratedList::search(TComp searchedData) const {
    ListIterator it = first();
    while (it.valid() && it.getCurrent() != searchedData && m_relation(it.getCurrent(), searchedData))
        it.next();

    // the searched element is not in the SSLL, so we need to make the iterator invalid
    if (it.valid() && it.getCurrent() != searchedData)
        it.invalidate();

    return it;

    /*
     METHOD 2:
    SSLLNode* currentNode = m_SSLL->head;
    @search for the node whose data is searchedData
    ListIterator it(*this);
    it.m_currentElement = currentNode;
    return it;
     */
}
// BC: theta(1) - when the searched element is the first one or when the condition regarding the relation between
//                the first element and the searched element is false from the beginning
// WC: theta(n) - when the searched element is not in the SSLL, and the while cannot be exited due to the fact that the
//                searched element could appear until the end of the list, i.e. it is "greater" than all the other elements
// AC: theta(n)
// Total complexity: O(n)

void SortedIteratedList::add(TComp newData) {
    SSLLNode* newNode = new SSLLNode;
    newNode->data = newData;
    newNode->next = NULL;

    if (m_SSLL->elementsNumber == 0) {
        // there is no node in the SSLL, so the new node will also be the head
        m_SSLL->head = newNode;
        m_SSLL->elementsNumber++;
    } else if (m_relation(newData, m_SSLL->head->data)) {
        // the new node must be added before the head
        newNode->next = m_SSLL->head;
        m_SSLL->head = newNode;
    } else {
        // the new node must be added after the head
        SSLLNode* currentNode = m_SSLL->head;
        while (currentNode->next != NULL && m_relation(currentNode->next->data, newData))
            currentNode = currentNode->next;
        // when we exit the while loop, the new node must be added after the current node
        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }
}
// BC: theta(1) - when the new node must be added as a head, or before the head
// WC: theta(n) - when the new node must be added on the last position
// AC: theta(n)
// Total complexity: O(n)

SortedIteratedList::~SortedIteratedList() {
    SSLLNode* currentNode = m_SSLL->head;
    SSLLNode* nextNode;

    while (currentNode != NULL) {
        nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }

    delete m_SSLL;
} // theta(n)

void SortedIteratedList::filter(Condition condition) {
    SSLLNode* currentNode = m_SSLL->head;
    SSLLNode* previousNode = m_SSLL->head;
    SSLLNode* nodeToRemove;

    while (currentNode != NULL)
        if (!condition(currentNode->data)) {
            // the current node must be removed
            if (currentNode == m_SSLL->head) {
                // the current node is also the head of the list
                m_SSLL->head = currentNode->next;
                nodeToRemove = currentNode;
                currentNode = m_SSLL->head;
                previousNode = m_SSLL->head;
                delete nodeToRemove;
            } else {
                // the current node is inside the list
                previousNode->next = currentNode->next;
                nodeToRemove = currentNode;
                currentNode = currentNode->next;
                delete nodeToRemove;
            }
        } else {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }

} // theta(n)


