#include "MultiMapIterator.h"
#include "MultiMap.h"

MultiMapIterator::MultiMapIterator(const MultiMap& map) : m_map(map) {
    if (m_map.m_hashTable->m_firstNonEmptyPosition == -1) {
        // the map is empty
        invalidate();
    } else {
        m_currentNode = m_map.m_hashTable->m_array[m_map.m_hashTable->m_firstNonEmptyPosition];
        m_currentValueIndex = 0;
        m_currentTablePosition = m_map.m_hashTable->m_firstNonEmptyPosition;

        m_parsedNodesInfo = new std::pair<int, Node*>[m_map.m_hashTable->m_numberOfNodes];
        m_parsedNodesIndex = 0;
        std::pair<int, Node*> firstNodeInfo;
        firstNodeInfo.first = m_currentTablePosition;
        firstNodeInfo.second = m_currentNode;
        m_parsedNodesInfo[m_parsedNodesIndex++] = firstNodeInfo;
    }
} // theta(1)

TElem MultiMapIterator::getCurrent() const {
    if (m_currentNode == NULL)
        throw std::exception();

    TElem currentElement;
    currentElement.first = m_currentNode->data.key;
    currentElement.second = m_currentNode->data.values[m_currentValueIndex];
    return currentElement;
} // theta(1)

bool MultiMapIterator::valid() const {
    if (m_currentNode != NULL)
        return true;
    else
        return false;
} // theta(1)

void MultiMapIterator::next() {
    if (m_currentNode == NULL)
        throw std::exception();

    if (m_currentValueIndex < m_currentNode->data.size - 1) {
        // the iterator stays in the same node
        m_currentValueIndex += 1;
    } else {
        // the iterator must go to the next node, which can be inside the same chain or in another chain
        if (m_currentNode->next != NULL) {
            // same chain
            m_currentNode = m_currentNode->next;
            m_currentValueIndex = 0;

            std::pair<int, Node*> newCurrentNodeInfo;
            newCurrentNodeInfo.first = m_currentTablePosition;
            newCurrentNodeInfo.second = m_currentNode;
            m_parsedNodesInfo[m_parsedNodesIndex++] = newCurrentNodeInfo;
        } else {
            // another chain, which we must find first
            int i = m_currentTablePosition + 1;
            while (i != m_map.m_hashTable->m_positions)
                if (m_map.m_hashTable->m_array[i] != NULL) {
                    m_currentNode = m_map.m_hashTable->m_array[i];
                    m_currentValueIndex = 0;
                    m_currentTablePosition = i;

                    std::pair<int, Node*> newCurrentNodeInfo;
                    newCurrentNodeInfo.first = m_currentTablePosition;
                    newCurrentNodeInfo.second = m_currentNode;
                    m_parsedNodesInfo[m_parsedNodesIndex++] = newCurrentNodeInfo;
                    break;
                } else i++;

            // if there is no other chain
            if (i == m_map.m_hashTable->m_positions)
                invalidate();
        }
    }
}
// BC: theta(1) - when the next element is part of the same chain or has the same key as the current one
// WC: theta(number of positions of the hash table - current position of the iterator)
// AC: theta(number of positions of the hash table - current position of the iterator)
// Total complexity: O(total number of positions of the map - current position of the iterator)

void MultiMapIterator::previous() {
    if (m_currentNode == NULL)
        throw std::exception();

    if (m_currentValueIndex > 0) {
        // the iterator stays in the same node
        m_currentValueIndex -= 1;
    } else {
        // the iterator must move to the previous node
        if (m_parsedNodesIndex == 0) {
            // there is no previous node
            invalidate();
        } else {
            if (m_parsedNodesIndex == m_map.m_hashTable->m_numberOfNodes)
                m_parsedNodesIndex -= 1;

            // we find the previous node in the array
            m_parsedNodesIndex -= 1; // we go back a position
            m_currentTablePosition = m_parsedNodesInfo[m_parsedNodesIndex].first;
            m_currentNode = m_parsedNodesInfo[m_parsedNodesIndex].second;
            m_currentValueIndex =
                    m_currentNode->data.size - 1; // we place the iterator on the last value associated with the key of the node
        }
    }
} // theta(1)

void MultiMapIterator::first() {
    if (m_map.m_hashTable->m_firstNonEmptyPosition == -1) {
        invalidate();
    } else {
        m_currentNode = m_map.m_hashTable->m_array[m_map.m_hashTable->m_firstNonEmptyPosition];
        m_currentValueIndex = 0;
        m_currentTablePosition = m_map.m_hashTable->m_firstNonEmptyPosition;

        if (m_parsedNodesInfo != NULL)
            delete[] m_parsedNodesInfo;

        m_parsedNodesInfo = new std::pair<int, Node*>[m_map.m_hashTable->m_numberOfNodes];
        m_parsedNodesIndex = 0;
        std::pair<int, Node*> firstNodeInfo;
        firstNodeInfo.first = m_map.m_hashTable->m_firstNonEmptyPosition;
        firstNodeInfo.second = m_currentNode;
        m_parsedNodesInfo[m_parsedNodesIndex++] = firstNodeInfo;
    }
} // theta(1)

void MultiMapIterator::invalidate() {
    m_currentNode = NULL;
    m_parsedNodesInfo = NULL;
    m_currentValueIndex = -1;
    m_currentTablePosition = -1;
    m_parsedNodesIndex = -1;
} // theta(1)

MultiMapIterator::~MultiMapIterator() {
    if (m_parsedNodesInfo != NULL)
        delete[] m_parsedNodesInfo;
} // theta(1)
