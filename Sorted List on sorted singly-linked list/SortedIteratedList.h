#pragma once

class ListIterator;

typedef int TComp;
typedef ListIterator TPosition;

typedef bool (* Relation)(TComp, TComp);

typedef bool (* Condition)(TComp);

#define NULL_TCOMP -11111

struct SSLLNode {
    TComp data;
    SSLLNode* next;
};

struct SSLL {
    SSLLNode* head;
    int elementsNumber;
};


class SortedIteratedList {
private:
    SSLL* m_SSLL;
    Relation m_relation;

    friend class ListIterator;

public:
    // constructor
    SortedIteratedList(Relation relation);

    // returns the number of elements from the list
    int size() const;

    // verifies if the list is empty
    bool isEmpty() const;

    // returns the first position from the list
    ListIterator first() const;

    // returns the element from the given position
    // throws an exception if the position is not valid
    TComp getElement(TPosition position) const;

    // adds a new element to the list
    void add(TComp newData);

    // removes the element from position position
    // returns the removed element
    // after removal position is positioned on the next element (the one after the removed one) or it is invalid if the last element was removed
    // throws an exception if the position is not valid
    TComp remove(TPosition& position);

    // searches for the first occurrence of an element
    // returns an iterator that points to the element, if it appear in the list, or an invalid iterator if the element is not in the list
    TPosition search(TComp searchedData) const;

    // keeps in the SortedList only the elements that respect the given condition
    void filter(Condition condition);

    // destructor
    ~SortedIteratedList();
};
