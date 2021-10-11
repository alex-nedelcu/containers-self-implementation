#pragma once

#include "SortedBag.h"

class SortedBag;

class SortedBagIterator {
private:
    const SortedBag& m_bag;
    int m_currentNodePosition;

    explicit SortedBagIterator(const SortedBag& bag);

    friend class SortedBag;

public:
    TComp getCurrent();

    bool valid() const;

    void next();

    void first();
};

