#pragma once

#include "Map.h"

class MapIterator {
private:
    const Map& m_map;
    int m_currentPosition;
    int m_previousPosition;

    explicit MapIterator(const Map& map);

    friend class Map;

public:
    void first();

    void next();

    TElem getCurrent();

    bool valid() const;

    // removes and returns the current pair from the iterator
    // after the operation the current pair from the iterator is the next element from the map, or,
    // if the removed element was the last one, the iterator is invalid
    // throws exception if the iterator is invalid
    TElem removeCurrent();
};


