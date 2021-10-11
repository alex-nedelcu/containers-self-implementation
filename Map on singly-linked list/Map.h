#pragma once

#include <utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TKEY (-111111)
#define NULL_TVALUE (-111111)
#define NULL_TELEM std::pair<TKey, TValue>(NULL_TKEY, NULL_TVALUE)

class MapIterator;

struct SLLA {
    int head;
    int firstEmpty;
    int size;
    int capacity;
};

class Map {
private:
    SLLA* m_SLLA;
    TElem* m_collection;
    int* m_next;

    friend class MapIterator;

public:
    // implicit constructor
    Map();

    // adds a pair (key,value) to the map
    // if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
    // if the key does not exist, a new pair is added and the value null is returned
    TValue add(TKey key, TValue value);

    // searches for the key and returns the value associated with the key if the map contains the key or NULL_TVALUE otherwise
    TValue search(TKey key) const;

    // removes a key from the map and returns the value associated with the key if the key exists or NULL_TVALUE otherwise
    TValue remove(TKey key);

    // returns the number of pairs (key,value) from the map
    int size() const;

    // checks whether the map is empty or not
    bool isEmpty() const;

    // returns an iterator for the map
    MapIterator iterator() const;

    // destructor
    ~Map();
};



