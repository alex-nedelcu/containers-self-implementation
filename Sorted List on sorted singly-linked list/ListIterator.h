#pragma once

#include "SortedIteratedList.h"

//DO NOT CHANGE THIS PART
class ListIterator {
private:
    const SortedIteratedList& m_list;
    SSLLNode* m_currentElement;

    ListIterator(const SortedIteratedList& list);

    friend class SortedIteratedList;

    void invalidate();

public:
    void first();

    void next();

    bool valid() const;

    TComp getCurrent() const;
};


