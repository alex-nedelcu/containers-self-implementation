#pragma once

#include "MultiMap.h"

class MultiMap;

class MultiMapIterator {
    friend class MultiMap;

private:
    const MultiMap& m_map;
    Node* m_currentNode;
    int m_currentValueIndex;
    int m_currentTablePosition;
    std::pair<int, Node*>* m_parsedNodesInfo;
    int m_parsedNodesIndex;

    explicit MultiMapIterator(const MultiMap& map);

    void invalidate();

public:
    ~MultiMapIterator();

    TElem getCurrent() const;

    bool valid() const;

    void next();

    void previous();

    void first();
};

