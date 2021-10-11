#pragma once

typedef int TComp;

typedef bool(* TRelation)(TComp, TComp);

#define NULL_TCOMP -11111;

class SortedBagIterator;

struct BSTNode {
    TComp info;
    int left;
    int right;
};

struct BinarySearchTree {
    int root;
};

class SortedBag {
private:
    BinarySearchTree* m_BST;
    int m_capacity;
    int m_size;
    int* m_infoArray;
    int* m_leftArray;
    int* m_rightArray;
    int* m_nextEmptyArray;
    int m_firstEmpty;
    TRelation m_relation;

    friend class SortedBagIterator;

    int findParentPosition(int nodePosition) const;

    int findSuccessorPosition(int nodePosition) const;

public:
    // constructor
    explicit SortedBag(TRelation relation);

    // adds an element to the sorted bag
    void add(TComp element);

    // removes one occurrence of an element from the sorted bag
    // returns true if the element was removed, false otherwise (if the element is not part of the sorted bag)
    bool remove(TComp element);

    // checks if an element exists in the sorted bag
    bool search(TComp element) const;

    // returns the number of occurrences for an element in the sorted bag
    int nrOccurrences(TComp element) const;

    // returns the number of elements in the sorted bag
    int size() const;

    // checks if the sorted bag is empty
    bool isEmpty() const;

    // returns an iterator for the sorted bag
    SortedBagIterator iterator() const;

    // returns the difference between the maximum and the minimum elements in the sorted bag
    int getRange() const;

    // destructor
    ~SortedBag();
};