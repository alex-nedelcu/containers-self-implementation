#pragma once

#include <vector>
#include <utility>
#include <cmath>
#include "Utils.h"

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;

struct Data {
    TKey key;
    TValue* values;
    int capacity;
    int size;
};

struct Node {
    Data data;
    Node* next;
};

struct HashTable {
    Node** m_array;
    int m_positions;
    int m_numberOfNodes;
    int m_firstNonEmptyPosition;
    double m_loadFactor;
};


class MultiMapIterator;

class MultiMap {
private:
    HashTable* m_hashTable;
    int m_numberOfElements;

    int hash(TKey key) const;

    void rehash();

    int findNewCapacity();

    friend class MultiMapIterator;

public:
    // constructor
    explicit MultiMap();

    // adds a key value pair to the multimap
    void add(TKey key, TValue value);

    // removes a key value pair from the multimap
    // returns true if the pair was removed (if it was in the multimap) and false otherwise
    bool remove(TKey key, TValue value);

    // returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
    std::vector<TValue> search(TKey key) const;

    // returns the number of pairs from the multimap
    int size() const;

    // checks whether the multimap is empty
    bool isEmpty() const;

    // returns an iterator for the multimap
    MultiMapIterator iterator() const;

    // destructor
    ~MultiMap();
};

